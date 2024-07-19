#include"../include/fixedwing/WayPoints.h"
#include"../include/fixedwing/Moniter.h"
#include<thread>
#include<fstream>
void detec_setwp1(Modes* m);
void detec_setwp2(Modes* m);
void detect(double*,double*,My_Moniter*,bool* f, bool* hault);
void test_detect(double*,double*,bool* f, bool* hault);
int event_Detect_1(ros::NodeHandle* nh,double* tar_x,double* tar_y)
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
    bool flag = false;
    bool hault = false;
    //std::thread detect_thread(detect,tar_x,tar_y);//thread begin
    std::thread test_thread(test_detect,tar_x,tar_y, &flag, &hault);
    for(;;)
    {

        if(stateM.state.mode == "AUTO.LOITER")
        {
            if(flag)
            {
                test_thread.join();
                return 1;
            }
            else
            {
                hault = true;
                test_thread.detach();
                return 0;
            }
        }
        ros::spinOnce();
        rate.sleep();
    }
}
int event_Detect_2(ros::NodeHandle* _nh, double* tar_x, double* tar_y)
{
    Modes md(_nh);
    stateMoniter stateM(_nh);
    My_Moniter myMon(_nh);
    ros::Rate rate(20.0);
    detec_setwp2(&md);
    while (stateM.state.mode != "AUTO.MISSION")
    {
        md.setMode("AUTO.MISSION");
        ros::spinOnce();
        rate.sleep();
    }
    bool flag = false;
    bool hault = false;
    //std::thread detect_thread(detect,tar_x,tar_y);//thread begin
    std::thread test_thread(test_detect,tar_x,tar_y, &flag, &hault);
    for(;;)
    {

        if(stateM.state.mode == "AUTO.LOITER")
        {
            if(flag)
            {
                test_thread.join();
                return 1;
            }
            else
            {
                hault = true;
                test_thread.detach();
                return 0;
            }
        }
        ros::spinOnce();
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
    //wps.push_back(wp1.setWayPoints(4,19,false,true,8,0.0,-25,NAN,120,25,30));
    //wps.push_back(wp.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,200,0,30));
    //wps.push_back(wp1.setWayPoints(4,19,false,true,7,0.0,-25,NAN,pole2enu_x(sqrt(0.25 * MY_TARGET_RADIUS * MY_TARGET_RADIUS + 25.0 * 25.0), MY_TARGET_THETA + atan(25.0 / (0.5 * MY_TARGET_RADIUS))),pole2enu_y(sqrt(0.25 * MY_TARGET_RADIUS * MY_TARGET_RADIUS + 25.0 * 25.0), MY_TARGET_THETA + atan(25.0 / (0.5 * MY_TARGET_RADIUS))),30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,pole2enu_x(MY_TARGET_RADIUS - 25, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS - 25, MY_TARGET_THETA),30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0.0,0.0,0.0,NAN,pole2enu_x(MY_TARGET_RADIUS,MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS,MY_TARGET_THETA),30));
    wps.push_back(wp1.setWayPoints(4,16,false,true,0.0,0.0,0.0,0,pole2enu_x(MY_TARGET_RADIUS + 50, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS + 50,MY_TARGET_THETA),30));
    wps.push_back(wp2.setWayPoints(4,
        19,
        false,
        true,
        9,//@param1 Time
        0,
        25,//@param3 Radius
        NAN,
        pole2enu_x(sqrt((MY_TARGET_RADIUS + 150.0) * (MY_TARGET_RADIUS + 150.0) + 25.0 * 25.0),MY_TARGET_THETA + atan(25.0 / (MY_TARGET_RADIUS + 150.0))),
        pole2enu_y(sqrt((MY_TARGET_RADIUS + 150.0) * (MY_TARGET_RADIUS + 150.0) + 25.0 * 25.0),MY_TARGET_THETA + atan(25.0 / (MY_TARGET_RADIUS + 150.0))),
        25));
    m->wpPush(wps);
    m->wpPull();
}
void detec_setwp2(Modes* m)
{
    WayPointsCnt wp;
    std::vector<mavros_msgs::Waypoint> wps;
    wps.push_back(wp.setWayPoints(4,16,false,true,0,0,0,NAN,pole2enu_x(MY_TARGET_RADIUS + 25, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS + 25, MY_TARGET_THETA), 30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0,0,0,NAN,pole2enu_x(MY_TARGET_RADIUS,MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS,MY_TARGET_THETA),30));
    wps.push_back(wp.setWayPoints(4,16,false,true,0,0,0,NAN,pole2enu_x(MY_TARGET_RADIUS - 50, MY_TARGET_THETA),pole2enu_y(MY_TARGET_RADIUS - 50, MY_TARGET_THETA),30));
    wps.push_back(wp.setWayPoints(
        4,
        19,
        false,
        true,
        9,
        0,
        25,
        NAN,
        pole2enu_x(sqrt((MY_TARGET_RADIUS - 150.0) * (MY_TARGET_RADIUS - 150.0) + 25.0 * 25.0), MY_TARGET_THETA - atan(25.0 / (MY_TARGET_RADIUS - 150.0))),
        pole2enu_y(sqrt((MY_TARGET_RADIUS - 150.0) * (MY_TARGET_RADIUS - 150.0) + 25.0 * 25.0), MY_TARGET_THETA - atan(25.0 / (MY_TARGET_RADIUS - 150.0))),
        25
    ));
    m->wpPush(wps);
    m->wpPull();
}
void detect(double* tar_x,double* tar_y,My_Moniter* myMon, bool* f, bool* hault)
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
        if(*hault)
        {
            return;
        }
    }
    inputFILE.close();
    ROS_WARN(">>>Caption finished.>>>");
    //对数据进行处理！

    *f = true;
}
void test_detect(double* tar_x, double* tar_y, bool* f, bool* hault)
{
    *tar_x = 243;//测试靶点x
    *tar_y =  1 ;//测试靶点y
    for(;;)
    {
        //Test
        //break;
        //
        if(*hault)
        {
            return;   
        }
    }
    *f = true;
}
