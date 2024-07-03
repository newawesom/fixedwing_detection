#include"../include/fixedwing/WayPoints.h"
#ifndef MY_TAKEOFF
#define MY_TAKEOFF 0
#define MY_IDEL 1
#define MY_LAND 4
#endif
#ifndef MY_FAIL
#define MY_FAIL 0
#define MY_SUCCESS 1
#endif


void idel_wpSet(Modes* m)
{
    WayPointsCnt wayp0;
    WayPointsCnt wayp1;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp1.setWayPoints(3,31,false,true,0.0,-50,0,NAN,MY_TARGET_POINT_ALT,MY_TARGET_POINT_LONG,30));
    wps.push_back(wayp0.setWayPoints(3,19,false,true,15,0,-50,NAN,MY_TARGET_POINT_ALT,MY_TARGET_POINT_LONG,30));
    m->wpPush(wps);
    m->wpPull();
}

int event_Idel(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    idel_wpSet(&md);
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
        else{
        ros::spinOnce();
        rate.sleep();
        }
    }
}