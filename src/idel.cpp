#include<iostream>
#include<ros/ros.h>
#include<vector>
#include "./WayPoint.cpp"
#ifndef TAKEOFF 0
#define TAKEOFF 0
#define IDEL 1
#define LAND 4
#endif
#ifndef FAIL 0
#define FAIL 0
#define SUCCESS 1
#endif

stateMoniter stateM;
Modes md;
ros::Rate rate(20);

void wpSet()
{
    WayPointCnt wayp;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp.setWayPoints(3,17,false,true,0.0,0.0,50,0.0,47.398621,8.547745,5));
    md.wpPush(wps);
    md.wpPull();
}

int event_Idel()
{
        

}