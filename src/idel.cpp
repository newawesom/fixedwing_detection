#include"../include/fixedwing/WayPoints.h"
#include<conio.h>
#ifndef TAKEOFF 0
#define TAKEOFF 0
#define IDEL 1
#define LAND 4
#endif
#ifndef FAIL 0
#define FAIL 0
#define SUCCESS 1
#endif


void idel_wpSet(Modes* m)
{
    WayPointsCnt wayp;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp.setWayPoints(3,17,false,true,0.0,0.0,50,0.0,47.397713,8.547745,10));
    m->wpPush(wps);
    m->wpPull();
}

int event_Idel(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    idel_wpSet(&md);
    for(;;)
    {
        if(stateM.state.mode != "AUTO.MISSION")
        {
            md.setMode("AUTO.MISSION");
        }
        if(_kbhit())//当键盘按下时返回true
        {
            int ch = _getche() - 96;//0->96,1->97;
            md.resetMode();
            if(ch)
            {
                return SUCCESS;
            }
            else
            {
                return FAIL;
            }
            break;
            
        }
        rate.sleep();        
    }
}