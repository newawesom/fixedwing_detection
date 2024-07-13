#include"../include/fixedwing/Moniter.h"

My_Moniter::My_Moniter(ros::NodeHandle* _nh)
{
    My_Moniter::Init(_nh);
}
void My_Moniter::Init(ros::NodeHandle* _nh)
{
    My_Moniter::pose_sub = _nh->subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose",10,&My_Moniter::pose_Callback,this);
    My_Moniter::vel_sub = _nh->subscribe<geometry_msgs::TwistStamped>("/mavros/local_position/velocity_local",10,&My_Moniter::vel_Callback,this);
}
void My_Moniter::pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    My_Moniter::current_pose = *msg;
}
void My_Moniter::vel_Callback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    My_Moniter::current_vel = *msg;
}