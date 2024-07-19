#include<iostream>
#include<vector>
#include<ros/ros.h>

#define MY_TAKEOFF 0
#define MY_DETEC_1 10
#define MY_DETEC_2 11
#define MY_TASK_1 20
#define MY_TASK_2 21
#define MY_LAND 3

#define MY_FAIL 0
#define MY_SUCCESS 1
/**
    @brief 状态机转换类
    @private 
    @param current 当前状态
    @param condition 输入
    @param next 下一状态
**/
class Transition
{
    private:
    int current;
    int condition;
    int next;
    public:
    /**
    @brief 创建一个状态机转换类
    @param int 初始状态
    @param int 初始输入
    @param int 初始次态
    **/
    Transition(int,int,int);
    Transition();
    /**
    @brief 获取当前状态
    **/
    int getcur();
    /**
    @brief 获取当前输入
    **/
    int getcond();
    /**
    @brief 获取当前次态
    **/
    int getnext();
    /**
    @brief 拷贝函数
    @param Transition 被拷贝的对象
    **/
    void copy(Transition tra);
    /**
    @brief 判断输入和当前状态是否满足此转换
    @param int 有限状态机的当前状态
    @param int 有限状态机的当前输入
    **/
    int is_match(int,int);
};
/**
    @breif 有限状态机类
    @private
    @param int 当前状态
    @param int 初始状态
    @param int 状态返回值
    @param ros::NodeHandle* ros句柄调用
    @param std::vector<Transition> 状态机转换容器，储存所有的转换
**/
class FSM
{
    private:
    int current_state;
    int start_state;
    int rc;
    ros::NodeHandle* _nh;
    std::vector<Transition> trans;

    public:
    /**
    @brief 获取当前状态
    **/
    int getState();
    /**
    @brief 设置当前状态
    @param int 需要设置的状态
    **/
    void setStart_State(int);
    /**
    @brief 设置转换
    @param Transition 需要设置的转换
    **/
    void setTrans(Transition);
    /**
    @brief 状态转换函数
    @param int 转换的输入
    **/
    void event_trans(int);
    /**
    @brief 当前状态所完成的任务
    @param double* 传入的目标指针 @arg X
    @param double* 传入的目标指针 @arg Y
    **/
    int event(double*, double*);
    /**
    @brief 有限状态机运行启动函数
    **/
    void run();
    /**
    @brief 有限状态及构造函数
    @param ros::NodeHandle* ros句柄调用
    **/
    FSM(ros::NodeHandle* nh);
};