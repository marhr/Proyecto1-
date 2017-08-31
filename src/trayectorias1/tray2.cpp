#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <iostream>

#define RATE 10.0

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
	ros::Rate rate(RATE);

	double d,v;
        cout << "Ingrese distancia (mm): ";
        cin >> d;
        cout << "Ingrese velocidad: ";
        cin >> v;

        d = d/1000;
        double t = d/v;
        double ta = 0;
        double vaux=0;

	while(ros::ok()){
		ta += 1.0/RATE;
		geometry_msgs::Twist m;

		//ROS_INFO_STREAM( "posicion ="<<pose.x <<", ta="<< ta<<", t="<<t);

		if(ta<1){
			vaux += v/RATE;
			ROS_INFO_STREAM( "v ="<<vaux<<", ta="<< ta<<", t="<<t);

		}
		else if(ta>t){
			vaux =0;
			ROS_INFO_STREAM("Adios!");
			break;
		}
		else if(ta> t-1){
			vaux -= v/RATE;
			ROS_INFO_STREAM( "v ="<<vaux <<", ta="<< ta<<", t="<<t);
		}
		else{
			vaux = v;
			ROS_INFO_STREAM( "v ="<<vaux <<", ta="<< ta<<", t="<<t);
		}
		m.linear.x = vaux;
		pub.publish(m);


		ros::spinOnce();
		rate.sleep();
}

	return 0;
}