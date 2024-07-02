#include"../include/fixedwing/WayPoints.h"
#include<conio.h>
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
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wayp0.setWayPoints(3,17,false,true,0.0,0.0,25,NAN,47.3975323,8.5486766,20));
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
        while(stateM.state.mode != "AUTO.MISSION")
        {
            md.setMode("AUTO.MISSION");
            ros::spinOnce();
            rate.sleep();
        }
        if(_kbhit())//当键盘按下时返回true
        {
            int ch = _getche() - 96;//0->96,1->97;
            md.resetMode();
            if(ch)
            {
                return MY_SUCCESS;
            }
            else
            {
                return MY_FAIL;
            }
            break;
            
        }
        ros::spinOnce();
        rate.sleep();        
    }
}