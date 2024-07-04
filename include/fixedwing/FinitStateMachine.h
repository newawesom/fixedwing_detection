#include<iostream>
#include<vector>
#include<ros/ros.h>

#define MY_TAKEOFF 0
#define MY_IDEL 1
#define MY_DETEC 2
#define MY_TASK 3
#define MY_LAND 4

#define MY_FAIL 0
#define MY_SUCCESS 1

class Transition
{
    private:
    int current;
    int condition;
    int next;
    public:
    Transition(int,int,int);
    Transition();
    int getcur();
    int getcond();
    int getnext();
    void copy(Transition tra);
    int is_match(int,int);
};
class FSM
{
    private:
    int current_state;
    int start_state;
    int rc;
    ros::NodeHandle* _nh;
    std::vector<Transition> trans;

    public:
    int getState();
    void setStart_State(int);
    void setTrans(Transition);
    void event_trans(int);
    int event(double*, double*);
    void run();
    FSM(ros::NodeHandle* nh);
};