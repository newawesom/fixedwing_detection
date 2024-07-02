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

void land_wpSet(Modes* m)
{
    WayPointsCnt wp0;
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    WayPointsCnt wp3;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp0.setWayPoints(3,16,false,true,0.0,0.0,0.0,NAN,47.3975243,8.5494719,20));
    wps.push_back(wp1.setWayPoints(3,16,false,true,0.0,0.0,0.0,NAN,47.3975247,8.5479390,10));
    wps.push_back(wp2.setWayPoints(2,189,false,true,0,0,0,0,0,0,0));
    wps.push_back(wp3.setWayPoints(3,21,false,true,0,0,0,NAN,47.3975176,8.5465395,0));
    m->wpPush(wps);
    m->wpPull();
}
int event_Landing(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    land_wpSet(&md);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    for(;;)
    {
        if(!stateM.state.armed)
        {
            return MY_SUCCESS;
            break;
        }
        ros::spinOnce();
        rate.sleep();
    }
 
}