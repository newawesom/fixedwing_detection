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
    //wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,150,0,10));
    wps.push_back(wp0.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,pole2enu_x(0.5 * MY_TARGET_RADIUS, MY_TARGET_THETA),pole2enu_y(0.5 * MY_TARGET_RADIUS, MY_TARGET_THETA),10));
//    wps.push_back(wp1.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,100,0,10));
    wps.push_back(wp2.setWayPoints(2,189,false,true,0,0,0,0,0,0,0));
    //wps.push_back(wp3.setWayPoints(4,21,false,true,0,0,0,NAN,30,0,0));
    wps.push_back(wp3.setWayPoints(4,21,false,true,0,0,0,NAN,pole2enu_x(30,MY_TARGET_THETA),pole2enu_y(30,MY_TARGET_THETA),0));
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