#include"../include/fixedwing/WayPoints.h"
#include"../include/fixedwing/Moniter.h"
#include<thread>
#include<fstream>
void detec_setwp1(Modes* m);
void detec_setwp2(Modes* m);
void detect(double*,double*,My_Moniter*);
int event_Detect(ros::NodeHandle* nh,double* tar_x,double* tar_y)
{
    Modes md(nh);
    stateMoniter stateM(nh);
    My_Moniter myMon(nh);
    ros::Rate rate(20.0);
    detec_setwp1(&md);
    while(stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();   
    }
    //std::thread detect_thread(detect,tar_x,tar_y);//thread begin
    for(;;)
    {
        if(stateM.state.mode == "AUTO.LOITER")
        {
            //detect_thread.join();
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
            //detect_thread.join();
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
void detect(double* tar_x,double* tar_y,My_Moniter* myMon)
{
    ROS_WARN(">>>CAPTION>>>");
    std::vector<double> tar;
    std::ifstream inputFILE;
    while(!inputFILE.is_open())
    {
        inputFILE.open("coodinate.txt");
        if(inputFILE.is_open())
        {
            ros::spinOnce();
            tar.push_back(myMon->current_pose.pose.position.x);
            tar.push_back(myMon->current_pose.pose.position.y);
            //获取飞机的位置坐标，push_back到tar的前两行
            std::string line;
            while(std::getline(inputFILE,line))
            {
                tar.push_back(stod(line));
            }
            break;
        }
    }
    inputFILE.close();
    ROS_WARN(">>>Caption finished.>>>");
    //对数据进行处理！
}
