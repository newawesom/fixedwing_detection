#include"../include/fixedwing/WayPoints.h"
double x_alt = 240;
double y_long = 0;
void task_wpSet(Modes*,double,double);
void calu(double*, double*);
void Servo_do();
int event_Tasking(ros::NodeHandle* nh,double x, double y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    x_alt = x;
    y_long = y;
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