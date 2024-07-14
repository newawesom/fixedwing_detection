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
void task_wpSet(Modes*,double,double);
void calu(double*, double*);
void autotriger(double*,double*,ros::NodeHandle* _nh,ros::Rate*);
void Servo_do();
void pose_CB(const geometry_msgs::PoseStamped::ConstPtr&);
void vel_CB(const geometry_msgs::TwistStamped::ConstPtr&);
double compute_time();
bool is_time(double,double,double);
geometry_msgs::PoseStamped current_pose;
geometry_msgs::TwistStamped current_vel;
int event_Tasking(ros::NodeHandle* nh,double* tar_x, double* tar_y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    x_alt = *tar_x;
    y_long = *tar_y;
    double x_,y_;
    calu(&x_,&y_);
    task_wpSet(&md,x_,y_);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    std::thread bomb_thread(autotriger,tar_x,tar_y,nh,&rate);//thread begin
    for(;;)
    {
        if(stateM.state.mode == "AUTO.LOITER")
        {
            bomb_thread.join();//thread.join();
            return 1;
            break;
        }
        ros::spinOnce();
        rate.sleep();
    }
}
int event_Tasking(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    double x_,y_;
    calu(&x_,&y_);
    task_wpSet(&md,x_,y_);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    for(;;)
    {
        if(stateM.state.mode == "AUTO.LOITER")
        {
            return 1;
            break;
        }
        ros::spinOnce();
        rate.sleep();
    }
}
void task_wpSet(Modes* m,double x_, double y_)
{
    WayPointsCnt wp0;
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,280,0,20));
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,x_alt,y_long,20));
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0,0.0,NAN,x_,y_,20));
    m->wpPush(wps);
    m->wpPull();
}
void calu(double* x_,double* y_)
{
    *x_ = 2 * x_alt - 280;
    *y_ = 2 * y_long - 0;
}
void pose_CB(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    current_pose = *msg; 
}
void vel_CB(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    current_vel = *msg;
}
void autotriger(double* tar_x,double* tar_y, ros::NodeHandle* _nh,ros::Rate* _rate)
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
            break;
        }
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
    double dx = abs(current_pose.pose.position.x - tar_x);
    double dy = abs(current_pose.pose.position.y - tar_y);
    if(abs(abs(current_vel.twist.linear.x * t) - dx) < 3.0 && abs(abs(current_vel.twist.linear.y * t) - dy) < 3.0)
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