#include "../include/fixedwing/WayPoints.h"

#ifndef MY_FAIL
#define MY_FAIL 0
#define MY_SUCCESS 1
#endif

void debugwp(Modes* m);
int event_Debug(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateMt(nh);
    ros::Rate rate(20.0);
    md.wpClear();
    debugwp(&md);
    while(!stateMt.state.armed)
    {
        md.setArm();
        ros::spinOnce();
        rate.sleep();
    }
    while(stateMt.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    if(stateMt.state.mode != "AUTO.MISSION" || !stateMt.state.armed)
    {
        return MY_FAIL;
    }
    for(;;)
    {
        if(!stateMt.state.armed)
        {
            return MY_SUCCESS;
            break;
        }
        else
        {
            ros::spinOnce();
            rate.sleep();
        }
    }
}
void debugwp(Modes* m)
{
    WayPointsCnt wayp0;
    WayPointsCnt wayp1;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp0.setWayPoints(4,22,true,true,0,0,0,NAN,50,0,15));
    wps.push_back(wayp0.setWayPoints(4,16,true,true,0,0,0,NAN,50,0,15));
    wps.push_back(wayp0.setWayPoints(4,16,false,true,0,0,0,NAN,50,90,15));
    wps.push_back(wayp0.setWayPoints(4,16,true,false,0,0,0,NAN,0,90,15));
    wps.push_back(wayp0.setWayPoints(4,21,false,true,0,0,0,NAN,0,0,0));
    m->wpPush(wps);
    m->wpPull();
}
