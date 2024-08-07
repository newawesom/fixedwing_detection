#ifdef SET_HOMEPOINT_SIM
#define MY_HOME_POINT_ALT 47.3975171//The global latitude of home in Simulation
#define MY_HOME_POINT_LONG 8.5455938 //The global longtitude of home in Simulation
#endif
#ifdef SET_HOMEPOINT_NPU_STAR
#define MY_HOME_POINT_ALT 34.0327721 //The global latitude of home in School(NPU_Starfeild)
#define MY_HOME_POINT_LONG 108.7608450 //The global longtitude of home in School(NPU_Starfeild)
#endif
#ifdef SET_HOMEPOINT_NPU_CLOUD
#define MY_HOME_POINT_ALT 34.0370868 //The global latitude of home in School(NPU_Cloudfeild)
#define MY_HOME_POINT_LONG 108.7687547 //The global longtitude of home in School(NPU_Cloudfeild)
#endif
#ifdef SET_HOMEPOINT_CUADC_BLUE

#endif
#ifdef SET_HOMEPOINT_CUADC_RED

#endif
#ifndef __TEST_WAYPOINTS
#define __TEST_WAYPOINTS
#include<iostream>
#include<ros/ros.h>
#include<vector>
#include<string>
#include<mavros/mavros.h>
#include<mavros_msgs/CommandBool.h>
#include<mavros_msgs/SetMode.h>
#include<mavros_msgs/WaypointPush.h>
#include<mavros_msgs/Waypoint.h>
#include<mavros_msgs/WaypointPull.h>
#include<mavros_msgs/WaypointClear.h>
#include<mavros_msgs/State.h>
#include"global_ENU_tf.h"
#include"ENU_Pole_tf.h"
#ifndef DEBUG_MODE
#define MY_TARGET_RADIUS 220.0 //meter
#define MY_TARGET_THETA 0 //Rad
#endif
#ifdef DEBUG_MODE
//Debug 
#endif
/**
 * @brief 综合飞行管理类
 * @private 
 * @param _nh 传入句柄
 * @param armClient 解锁客户端
 * @param armcommand 解锁指令
 * @param setModeClient 飞行模式设置客户端
 * @param setmodecommand 飞行模式指令
 * @param wpPushClient 航点上传客户端
 * @param wppush 航点上传指令
 * @param wpPullClient 航点下载客户端
 * @param wppull 航点下载指令
 * @param wpClearClent 航点清除客户端
 * @param wpclear 航点清除指令
*/
class Modes
{
    public:
    /**
     * @brief 构造函数
     * @param nh 传入的句柄
    */
    Modes(ros::NodeHandle* nh);
    /**
     * @brief 飞机解锁
    */
    void setArm();
    /**
     * @brief 飞行模式设定 
     * @param mod 设定的模式
     * @arg AUTO.MISSION 航点任务执行
     * @arg AUTO.LOITER 盘旋模式
     * @arg OFFBOARD 板外模式（固定翼暂时不可用）
    */
    void setMode(std::string mod);
    /**
     * @brief 重置飞行模式至 
     * @arg AUTO.LOITER
    */
    void resetMode();
    /**
     * @brief 上传行点
     * @param wps 航点序列
    */
    void wpPush(std::vector<mavros_msgs::Waypoint> wps);
    /**
     * @brief 航点下载
    */
    void wpPull();
    /**
     * @brief 航点清零
    */
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
    /**
     * @brief 初始化函数
    */
    void Initialize();
};
/**
 * @brief 通用航点类
 * @param wp mavros航点
 * @param tf 经纬转换
 * @note mavros航点仅接受绝对经纬坐标，必须通过ENU坐标到经纬度转换才能传入相对ENU坐标
*/
class WayPointsCnt
{
    private:
    mavros_msgs::Waypoint wp;
    transf tf;
    public:
    /**
     * @brief 设置航点
     * @ref 参考mavros航点上传
     * @param fram 坐标系 
     * @arg 3/6 相对海拔经纬坐标 
     * @arg 2 任务坐标系 
     * @arg 4 相对HOME点的ENU坐标系
     * @param command 任务代码
     * @arg 21 起飞
     * @arg 16 航点
     * @arg 22 降落
     * @arg 19 盘旋（time）
     * @param is_current
     * @param autocontinue 是否自动飞往下一个行点
     * @param param1 参数1
     * @param param2 参数2
     * @param param3 参数3
     * @param param4 参数4
     * @param x_lat 纬度/x坐标
     * @param y_long 经度/y坐标
     * @param z_alt 相对海拔高度
    */
    mavros_msgs::Waypoint setWayPoints(int fram, int command, int is_current, int autocontinue, float param1, float param2, float param3, float param4, float x_lat, float y_long, float z_alt);
    WayPointsCnt();
};
/**
 * @brief 飞机飞行模式监控器
 * @private
 * @param _nh 传入句柄
 * @public
 * @param state_sub 状态订阅器
 * @param state 返回状态值
*/
class stateMoniter
{
    public:
    /**
     * @brief 默认构造函数
     * @param nh 传入ros句柄
    */
    stateMoniter(ros::NodeHandle* nh);
    ros::Subscriber state_sub;
    mavros_msgs::State state;
    private:
    ros::NodeHandle* _nh;
    /**
     * @brief 状态回调函数
     * @param msg 回传指针
    */
    void state_CB(const mavros_msgs::State::ConstPtr& msg);
    /**
     * @brief 初始化函数
    */
    void Initialize();
};
#endif