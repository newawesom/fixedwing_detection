#include "/home/nh/catkin_ws111/src/fixedwing/include/fixedwing/WayPoints.h"

Modes::Modes(ros::NodeHandle* nh)
{
    _nh = nh;
    Modes::Initialize();
}
void Modes::Initialize()
{
    ros::service::waitForService("/mavros/cmd/arming");
    ros::service::waitForService("/mavros/set_mode");
    ros::service::waitForService("/mavros/mission/push");
    ros::service::waitForService("/mavros/mission/pull");
    ros::service::waitForService("/mavros/mission/clear");
    armClient = _nh->serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    setModeClient = _nh->serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    wpPushClient = _nh->serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push",true);
    wpPullClient = _nh->serviceClient<mavros_msgs::WaypointPull>("/mavros/mission/pull",true);
    wpClearClient = _nh->serviceClient<mavros_msgs::WaypointClear>("/mavros/mission/clear",true);
}
void Modes::setArm()
{
    armcommand.request.value = true;
    armClient.call(armcommand);
    if(armcommand.response.success)
    {
        ROS_INFO(">>>>>>Armed>>>>>>");
    }
    else
    {
        ROS_ERROR("Cannot Arm!");
    }   
}
void Modes::setMode(std::string mod)
{
    setmodecommand.request.custom_mode = mod;
    setModeClient.call(setmodecommand);
    if(setmodecommand.response.mode_sent)
    {
        std::cout<<"<";
    }
    else
    {
        ROS_ERROR("Cannot set mode to %s!",mod.data());
    }
}
void Modes::resetMode()
{
    setmodecommand.request.custom_mode = "AUTO.HOLD";
    setModeClient.call(setmodecommand);
    if(!setmodecommand.response.mode_sent)
    {
        ROS_ERROR("Cannot reset mode!");
    }
}
void Modes::wpPush(std::vector<mavros_msgs::Waypoint> wps)
{
    wppush.request.waypoints = wps;
    wppush.request.start_index = 0;
    wpPushClient.call(wppush);
    if(wppush.response.success)
    {
        ROS_INFO(">>>WayPoints Pushed>>>");
    }
    else
    {
        ROS_ERROR("Cannot push waypoints!");
    }
}
void Modes::wpPull()
{
    wpPullClient.call(wppull);
    if(wppull.response.success)
    {
        ROS_INFO(">>>Waypoins Pulled>>>");
        ROS_INFO("%d",wppull.response.wp_received);
    }
    else
    {
        ROS_ERROR("Cannot pull waypoints!");
    }
}
void Modes::wpClear()
{
    wpClearClient.call(wpclear);
    if(wpclear.response.success)
    {
        ROS_INFO(">>>Waypoints Cleared>>>");
    }
    else
    {
        ROS_ERROR("Cannot clear waypoints!");
    }
}
mavros_msgs::Waypoint WayPointsCnt::setWayPoints(int fram,int command, int is_current, int autocontinue, float param1, float param2, float param3, float param4, float x_lat, float y_long, float z_alt)
{
    wp.frame = (fram == 4)?3:fram;
    wp.command = command;
    wp.is_current = is_current;
    wp.autocontinue = autocontinue;
    wp.param1 = param1;
    wp.param2 = param2;
    wp.param3 = param3;
    wp.param4 = param4;
    wp.x_lat = (fram == 4)?(tf.enu2world(point(x_lat,y_long)).x):x_lat;
    wp.y_long = (fram == 4)?(tf.enu2world(point(x_lat,y_long)).y):y_long;
    wp.z_alt = z_alt;

    return wp;
}
stateMoniter::stateMoniter(ros::NodeHandle* nh)
{
    _nh = nh;
    stateMoniter::Initialize();
}
void stateMoniter::state_CB(const mavros_msgs::State::ConstPtr& msg)
{
    stateMoniter::state = *msg;
}
void stateMoniter::Initialize()
{
    stateMoniter::state_sub = _nh->subscribe<mavros_msgs::State>("/mavros/state",20,&stateMoniter::state_CB,this);
}
WayPointsCnt::WayPointsCnt()
{
    tf = transf(MY_HOME_POINT_ALT,MY_HOME_POINT_LONG);
}