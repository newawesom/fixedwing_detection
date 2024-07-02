#ifndef TEST_WAYPOINTS
#define TEST_WAYPOINTS
#include<iostream>
#include<ros/ros.h>
#include<vector>
#include<std_msgs/String.h>
#include<mavros/mavros.h>
#include<mavros_msgs/CommandBool.h>
#include<mavros_msgs/SetMode.h>
#include<mavros_msgs/WaypointPush.h>
#include<mavros_msgs/Waypoint.h>
#include<mavros_msgs/WaypointPull.h>
#include<mavros_msgs/WaypointClear.h>
#include<mavros_msgs/State.h>

class Modes
{
    public:
    Modes(ros::NodeHandle* nh);
    void setArm();
    void setMode(std_msgs::String mod);
    void resetMode();
    void wpPush(std::vector<mavros_msgs::Waypoint> wps);
    void wpPull();
    void wpClear();
    private:
    ros::NodeHandle* _nh;
    ros::ServiceClient armClient;
    mavros_msgs::CommandBool armcommand;
    ros::ServiceClient setModeClient;
    mavros_msgs::SetMode setmodecommand;
    ros::ServiceClient wpPushClient;
    mavros_msgs::WaypointPush wppush;
    ros::ServiceClient wpPullClient;
    mavros_msgs::WaypointPull wppull;
    ros::ServiceClient wpClearClient;
    mavros_msgs::WaypointClear wpclear;

    void Initialize();
};
class WayPointsCnt
{
    private:
    mavros_msgs::Waypoint wp;
    public:
    mavros_msgs::Waypoint setWayPoints(int fram, int command, int is_current, int autocontinue, float param1, float param2, float param3, float param4, float x_lat, float y_long, float z_alt);
};
class stateMoniter
{
    public:
    stateMoniter(ros::NodeHandle* nh);
    ros::Subscriber state_sub;
    mavros_msgs::State state;
    private:
    ros::NodeHandle* _nh;
    void state_CB(const mavros_msgs::State::ConstPtr& msg);
    void Initialize();
};
#endif