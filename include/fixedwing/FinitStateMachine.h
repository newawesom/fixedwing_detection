#include<iostream>
#include<vector>
#include<ros/ros.h>

#define TAKEOFF 0
#define IDEL 1
#define DETEC 2
#define TASK 3
#define LAND 4

#define FAIL 0
#define SUCCESS 1

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
    int event();
    void run();
    FSM(ros::NodeHandle* nh);
};