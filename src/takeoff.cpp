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
        if(stateMt.state.mode == "AUTO.LOITER")
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
//    wps.push_back(wayp0.setWayPoints(4,22,true,true,0.0,0.0,0.0,NAN,150,0,20));
//    wps.push_back(wayp1.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,150,0,20));
    //wps.push_back(wayp0.setWayPoints(4,22,true,true,0,0,0,NAN,100,0,10));
    //wps.push_back(wayp1.setWayPoints(4,16,false,true,0,0,0,NAN,100,0,10));
    wps.push_back(wayp0.setWayPoints(4,22,true,true,0,0,0,NAN,0.5 * pole2enu_x(MY_TARGET_RADIUS,MY_TARGET_THETA),0.5 * pole2enu_y(MY_TARGET_RADIUS,MY_TARGET_THETA),15));
    wps.push_back(wayp1.setWayPoints(4,16,false,true,0,0,0,NAN,0.5 * pole2enu_x(MY_TARGET_RADIUS,MY_TARGET_THETA),0.5 * pole2enu_y(MY_TARGET_RADIUS,MY_TARGET_THETA),20));
    m->wpPush(wps);
    m->wpPull();
}
