#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/PoseStamped.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace ros;

int x_button = 0;
double left_trigger = 0.0;
double right_trigger = 0.0;
int push_button_flag = 0;

void subscribeCallback_joy(const sensor_msgs::Joy::ConstPtr& msg)
{
    x_button = msg->buttons.at(0);
    left_trigger = msg->axes.at(2);
    right_trigger = msg->axes.at(5);

    if( (left_trigger == -1.0) && (right_trigger == -1.0) && (x_button == 1) ){
        push_button_flag = 1;
    }
}

int main(int argc, char** argv){
    //int debug_count = 0;
    ros::init(argc, argv, "pub_goal");
    ros::NodeHandle nh;

    ros::Subscriber listener_joy = nh.subscribe("joy", 1, subscribeCallback_joy, ros::TransportHints().tcpNoDelay());
    ros::Publisher goal_point_pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);

    geometry_msgs::PoseStamped msg_goal_point;

    msg_goal_point.header.stamp = ros::Time::now();
    msg_goal_point.header.frame_id = "map";
    msg_goal_point.pose.position.x = 4.71065235138;
    msg_goal_point.pose.position.y = 1.14784288406;
    msg_goal_point.pose.position.z = 0.0;

    msg_goal_point.pose.orientation.x = 0.0;
    msg_goal_point.pose.orientation.y = 0.0;
    msg_goal_point.pose.orientation.z = 0.000398186367589;
    msg_goal_point.pose.orientation.w = 0.999999920724;

    ros::Rate loop_rate(10);

    while(ros::ok()){
        
        ros::spinOnce();

        if( push_button_flag == 1 ){
            // debug_count ++;
            // ROS_INFO("test_ok %d", debug_count);
            ROS_INFO("goal_point_publish_ok");
            goal_point_pub.publish(msg_goal_point);
            push_button_flag = 0;
        }

        loop_rate.sleep();
    }

    return 0;
}