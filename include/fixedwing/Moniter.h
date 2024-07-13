#ifndef __MY_MONITER
#define __MY_MONITER
#include<iostream>
#include<ros/ros.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/TwistStamped.h>
/**
 * @brief 飞机状态监听机，可监控飞机的位置
 * @private
 * @param pose_sub 飞机位置订阅器
 * @param vel_sub 飞机速度订阅器
 * @public
 * @param current_pose 当前的位置信息
 * @param current_vel 当前的速度信息
*/
class My_Moniter
{
    private:
    ros::Subscriber pose_sub;
    ros::Subscriber vel_sub;
    private:
    /**
     * @brief 初始化函数
     * @param _nh 传入的ros句柄
    */
    void Init(ros::NodeHandle* _nh);
    public:
    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::TwistStamped current_vel;
    public:
    /**
     * @brief 位置信息的回调函数
     * @param ConstPrt 回传指针
    */
    void pose_Callback(const geometry_msgs::PoseStamped::ConstPtr&);
    /**
     * @brief 速度信息的回调函数
     * @param ConstPrt 回传指针
    */
    void vel_Callback(const geometry_msgs::TwistStamped::ConstPtr&);
    /**
     * @brief 构造函数
     * @param _nh 传入的ros句柄
    */
    My_Moniter(ros::NodeHandle* _nh);
};
#endif