#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <iostream>

using namespace std;
turtlesim::Pose pose;

void mensajeRecibido(const turtlesim::Pose& m){
	pose.x = m.x;
	pose.y = m.y;
	pose.theta = m.theta;

}

int  main(int argc, char  **argv)
{
	ros::init(argc, argv, "hello_ros");
	ros::NodeHandle nh;

	ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ros::Subscriber sub=nh.subscribe("turtle1/pose",1000, &mensajeRecibido);
	ros::Rate rate(10);

	double d,v;
        cout << "Ingrese distancia (mm): ";
        cin >> d;
        cout << "Ingrese velocidad: ";
        cin >> v;

        double t = d/v;
        double ta = 0;
	while(ros::ok()){
		ta += 1.0/10.0;
		geometry_msgs::Twist m;

		ROS_INFO_STREAM( "posicion ="<<pose.x <<", ta="<< ta<<", t="<<t);

		if(ta<t)
			m.linear.x = v;
		else
			m.linear.x = 0;

		pub.publish(m);

		ros::spinOnce();
}

	return 0;
}