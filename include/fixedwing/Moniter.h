#ifndef __MY_MONITER
#define __MY_MONITER
#include<iostream>
#include<ros/ros.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/TwistStamped.h>

class My_Moniter
{
    private:
    ros::Subscriber pose_sub;
    ros::Subscriber vel_sub;
    private:
    void Init(ros::NodeHandle* _nh);
    public:
    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::TwistStamped current_vel;
    public:
    void pose_Callback(const geometry_msgs::PoseStamped::ConstPtr&);
    void vel_Callback(const geometry_msgs::TwistStamped::ConstPtr&);
    My_Moniter(ros::NodeHandle* _nh);
};
#endif