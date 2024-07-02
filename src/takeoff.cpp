#include "../include/fixedwing/WayPoints.h"
#ifndef MY_TAKEOFF
#define MY_TAKEOFF 0
#define MY_IDEL 1
#define MY_LAND 4
#endif
#ifndef MY_FAIL 
#define MY_FAIL 0
#define MY_SUCCESS 1
#endif


void takeoffwp(Modes* m);
int event_Takeoff(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateMt(nh);
    ros::Rate rate(20.0);
    md.wpClear();
    takeoffwp(&md);
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
        if(stateMt.state.mode != "AUTO.MISSION")
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
void takeoffwp(Modes* m)
{
    WayPointsCnt wayp0;
    WayPointsCnt wayp1;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp0.setWayPoints(3,22,true,true,0.0,0.0,0.0,NAN,MY_HOME_POINT_ALT,MY_HOME_POINT_LONG + 0.0030992,20));
    wps.push_back(wayp1.setWayPoints(3,16,false,true,0.0,0.0,0.0,NAN,MY_HOME_POINT_ALT,MY_HOME_POINT_LONG + 0.0030992,20));
    m->wpPush(wps);
    m->wpPull();
}
