#include"../include/fixedwing/WayPoints.h"
void detec_setwp1(Modes* m);
void detec_setwp2(Modes* m);
void detect();
int event_Detect(ros::NodeHandle* nh)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    ros::Rate rate(20.0);
    detec_setwp1(&md);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();   
    }
    for(;;)
    {
        if(stateM.state.mode != "AUTO.MISSION")
        {
            detect();
            break;
        }
        ros::spinOnce();
        rate.sleep();
    }
    detec_setwp2(&md);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    for(;;)
    {
        ros::spinOnce();
        if(stateM.state.mode != "AUTO.MISSION")
        {
            return 1;
            break;
        }
        rate.sleep();
    }
    
}
void detec_setwp1(Modes* m)
{
    WayPointsCnt wp;
    WayPointsCnt wp2;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp2.setWayPoints(3,16,false,true,0.0,0.0,0.0,NAN,MY_TARGET_POINT_ALT,MY_HOME_POINT_LONG,30));
    wps.push_back(wp.setWayPoints(3,16,false,true,0.0,0.0,0.0,0.0,MY_TARGET_POINT_ALT,MY_TARGET_POINT_LONG - 0.001,30));
    m->wpPush(wps);
    m->wpPull();
}
void detec_setwp2(Modes* m)
{
    WayPointsCnt wp1;
    std::vector<mavros_msgs::Waypoint> wps1;
    wps1.push_back(wp1.setWayPoints(3,16,false,true,0.0,0.0,0.0,180,MY_TARGET_POINT_ALT,MY_TARGET_POINT_LONG + 0.002,20));
    m->wpPush(wps1);
    m->wpPull();
}
void detect()
{
    ROS_WARN(">>>CAPTION>>>");
}
