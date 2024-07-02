#include "../include/fixedwing/WayPoints.h"
#ifndef TAKEOFF
#define TAKEOFF 0
#define IDEL 1
#define LAND 4
#endif
#ifndef FAIL 0
#define FAIL 0
#define SUCCESS 1
#endif


void takeoffwp(Modes* m);
int event_Takeoff(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateMt(nh);
    ros::Rate rate(20.0);
    takeoffwp(&md);
    while(!stateMt.state.armed)
    {
        md.setArm();
        rate.sleep();
    }
    while(stateMt.state.mode != "AUTO.MISSION")
    {
        md.setMode();
        rate.sleep();
    }
    if(stateMt.state.mode == "AUTO.MISSION" && stateMt.state.armed)
    {
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}
void takeoffwp(Modes* m)
{
    WayPointsCnt wayp0;
    WayPointsCnt wayp1;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp0.setWayPoints(3,22,true,true,0.0,0.0,0.0,NAN,47.397713,8.547605,5));
    wps.push_back(wayp1.setWayPoints(3,16,false,true,0.0,0.0,0.0,NAN,47.398621,8.547745,10));
    m->wpPush(wps);
    m->wpPull();
}
