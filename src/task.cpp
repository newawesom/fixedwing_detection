#include"../include/fixedwing/WayPoints.h"

double x_alt = MY_TARGET_POINT_ALT;
double y_long = MY_TARGET_POINT_LONG;
double x_offset = 0;
double y_offset = 0.001;
void task_wpSet(Modes*);
void calu(double, double);
void Servo_do();

void event_Task(ros::NodeHandle* nh,double x, double y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    x_alt = x;
    y_long = y;
    double x_,y_;
    calu(x_,y_);
    task_wpSet(&md,x_,y_);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    for(;;)
    {
        
    }

}
void event_Task(ros::NodeHandle* nh)
{

}
void task_wpSet(Modes* m,double x_, double y_)
{
    WayPointsCnt wp0;
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp0.setWayPoints(3,16,false,true,0.0,0.1,0.0,NAN,MY_TARGET_POINT_ALT + x_offset,MY_TARGET_POINT_LONG + y_offset,30));
    wps.push_back(wp0.setWayPoints(3,16,false,true,0.0,0.1,0.0,NAN,x_alt,y_long,20));
    wps.push_back(wp0.setWayPoints(3,16,false,true,0.0,0.1,0.0,NAN,x_,y_,10));
}
void calu(double x_,double y_)
{
    x_ = 2 * x_alt - MY_TARGET_POINT_ALT - x_offset;
    y_ = 2 * y_long - MY_TARGET_POINT_LONG - y_offset;
}