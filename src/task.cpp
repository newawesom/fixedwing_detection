#include"../include/fixedwing/WayPoints.h"
#include"../include/fixedwing/my_serial.h"
#include<thread>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/TwistStamped.h>
//My_Serial mysp;
/**
*    @param x_alt 目标位置x坐标
*    @param y_long  目标位置y坐标
*/
double x_alt = 240;
double y_long = 0;
unsigned int channel = 0;
double pursle_width = 1500;
void task_wpSet_1(Modes*,double,double);
void task_wpSet_2(Modes*,double,double);
void calu(double*, double*,double,double);
void autotriger(double*,double*,ros::NodeHandle* _nh,ros::Rate*, bool* flag, bool* hault);
void Servo_do();
void pose_CB(const geometry_msgs::PoseStamped::ConstPtr&);
void vel_CB(const geometry_msgs::TwistStamped::ConstPtr&);
double compute_time();
bool is_time(double,double,double);
geometry_msgs::PoseStamped current_pose;
geometry_msgs::TwistStamped current_vel;
int event_Tasking_1(ros::NodeHandle* nh,double* tar_x, double* tar_y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    x_alt = *tar_x;
    y_long = *tar_y;
    double x_,y_;
    calu(&x_,&y_,pole2enu_x(1.5 * MY_TARGET_RADIUS, MY_TARGET_THETA),pole2enu_y(1.5 * MY_TARGET_RADIUS, MY_TARGET_THETA));
    task_wpSet_1(&md,x_,y_);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    bool flag = false;
    bool hault = false;
    std::thread bomb_thread(autotriger,tar_x,tar_y,nh,&rate, &flag, &hault);//thread begin
    for(;;)
    {
        if(stateM.state.mode == "AUTO.LOITER")
        {
            if(flag)
            {
                bomb_thread.join();
                return 1;
            }
            else
            {
                hault = true;
                bomb_thread.detach();
                return 0;
            }
        }
        ros::spinOnce();
        rate.sleep();
    }
}
int event_Tasking_2(ros::NodeHandle* nh, double* tar_x, double* tar_y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(40.0);
    x_alt = *tar_x;
    y_long = *tar_y;
    double x_,y_;
    calu(&x_,&y_,pole2enu_x(MY_TARGET_RADIUS - 100, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS - 100, MY_TARGET_THETA));
    task_wpSet_2(&md,x_,y_);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    bool flag = false;
    bool hault = false;
    std::thread bomb_thread(autotriger,tar_x,tar_y,nh,&rate,&flag,&hault);
    for(;;)
    {
        if(stateM.state.mode == "AUTO.LOITER")
        {
            if(flag)
            {
                bomb_thread.join();
                return 1;
            }
            else
            {
                hault = true;
                bomb_thread.detach();
                return 0;
            }
        }
        ros::spinOnce();
        rate.sleep();
    }
}
void task_wpSet_1(Modes* m,double x_, double y_)
{
    WayPointsCnt wp0;
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    std::vector<mavros_msgs::Waypoint> wps;
    //wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,280,0,20));
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,pole2enu_x(1.5 * MY_TARGET_RADIUS, MY_TARGET_THETA),pole2enu_y(1.5 * MY_TARGET_RADIUS, MY_TARGET_THETA),33));
    //wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,x_alt,y_long,15));
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,x_,y_,5));
    m->wpPush(wps);
    m->wpPull();
}
void task_wpSet_2(Modes* m, double x_, double y_)
{
    WayPointsCnt wp;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp.setWayPoints(4,16,false,true,0,0,0,NAN,pole2enu_x(MY_TARGET_RADIUS * 0.5, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS * 0.5, MY_TARGET_THETA),30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0,0,0,NAN,x_,y_,5));
}
void calu(double* x_,double* y_,double start_x, double start_y)
{
    //*x_ = 2 * x_alt - 280;
    *x_ = 2 * x_alt - start_x;
    //*y_ = 2 * y_long - 0;
    *y_ = 2 * y_long - start_y;
}
void pose_CB(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    current_pose = *msg; 
}
void vel_CB(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    current_vel = *msg;
}
void autotriger(double* tar_x,double* tar_y, ros::NodeHandle* _nh,ros::Rate* _rate, bool* flag, bool* hault)
{
    ros::Subscriber pose_sub = _nh->subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose",10,pose_CB);
    ros::Subscriber vel_sub = _nh->subscribe<geometry_msgs::TwistStamped>("/mavros/local_position/velocity_local",10,vel_CB);
    for(;;)
    {
        ros::spinOnce();
        if(is_time(compute_time(),*tar_x,*tar_y))
        {
            ROS_WARN("BOMB!");
            Servo_do();
            *flag = true;
            break;
        }
        if(*hault)
            break;
        _rate->sleep();
    }    
}
double compute_time()
{
    double vz = current_vel.twist.linear.z;
    double h = current_pose.pose.position.z;
    double t = (2.0 * vz + sqrt(4.0 * vz * vz + 8.0 * 9.8 * h))/(2.0 * 9.8);
    return t;
}
bool is_time(double t, double tar_x, double tar_y)
{
    double dx = tar_x - current_pose.pose.position.x;
    double dy = tar_y - current_pose.pose.position.y;
    if(abs(current_vel.twist.linear.x * t - dx) < 1.0 && abs(current_vel.twist.linear.y * t - dy) < 1.0)
    {
        return true;
    }
    else
        return false;
}
void Servo_do()
{
    ROS_WARN(">>>Servo>>>");
    //mysp.sendData();
}
