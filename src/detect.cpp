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
        if(stateM.state.mode == "AUTO.LOITER")
        {
            detect();//detect()做成并行线程
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
        if(stateM.state.mode == "AUTO.LOITER")
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
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    std::vector<mavros_msgs::Waypoint> wps;
//    wps.push_back(wp2.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,120,0,30));
    wps.push_back(wp1.setWayPoints(4,19,false,true,8,0.0,-25,NAN,120,25,30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,200,0,30));
    m->wpPush(wps);
    m->wpPull();
}
void detec_setwp2(Modes* m)
{
    WayPointsCnt wp1;
    WayPointsCnt wp2;
    WayPointsCnt wp3;
    std::vector<mavros_msgs::Waypoint> wps1;
    wps1.push_back(wp1.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,350,0,25));
    wps1.push_back(wp2.setWayPoints(4,19,false,true,10,0,25,NAN,400,25.0,20));
//    wps1.push_back(wp3.setWayPoints(4,19,false,true,15,0,25,NAN,400,25.0,20));
    m->wpPush(wps1);
    m->wpPull();
}
void detect()
{
    ROS_WARN(">>>CAPTION>>>");
}
