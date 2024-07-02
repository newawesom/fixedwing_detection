#include "../include/fixedwing/FinitStateMachine.h"
#include "./takeoff.cpp"
Transition::Transition()
{
    Transition::current = 0;
    Transition::condition = 0;
    Transition::next = 0;
}
Transition::Transition(int cur,int cond, int nex)
{
    Transition::current = cur;
    Transition::condition = cond;
    Transition::next = nex;
}
int Transition::getcur()
{
    return Transition::current;
}
int Transition::getcond()
{
    return Transition::condition;
}
int Transition::getnext()
{
    return Transition::next;
}
void Transition::copy(Transition tra)
{
    Transition::current = tra.getcur();
    Transition::condition = tra.getcond();
    Transition::next = tra.getnext();
}
int Transition::is_match(int cur,int cond)
{
    if(cur == current && cond == condition)
        return 1;
    else
        return 0;
}
FSM::FSM(ros::NodeHandle* nh)
{
    FSM::current_state = 0;
    FSM::start_state = 0;
    FSM::rc = 0;
    FSM::_nh = nh;
}
int FSM::getState()
{
    return FSM::current_state;
}
void FSM::setStart_State(int sta)
{
    FSM::start_state = sta;
}
void FSM::setTrans(Transition tra)
{
    FSM::trans.push_back(tra);
}
void FSM::event_trans(int cond)
{
    bool flag = false;
    for(int i = 0;i < FSM::trans.size();i++)
    {
        if(FSM::trans[i].is_match(FSM::current_state,cond))
        {
            FSM::current_state = FSM::trans[i].getnext();
            flag = true;
            ROS_INFO("Current state has changed to:%d",FSM::current_state);
            break;
        }
        if(flag != true)
        {
            ROS_ERROR("No input and state Matches!!!");
        }
    }
}
int FSM::event()
{
    switch(FSM::current_state)
    {
        case 0:
            ROS_INFO(">>>Take Off!");
            FSM::rc = event_Takeoff(_nh);
            if(rc)
                ROS_INFO("Take Off Successfully!");
            else
                ROS_ERROR("Unable to take off!");
            return rc;
            break;
        case 1:
            ROS_INFO(">>>IDEL:Waiting for detection...");
            //FSM::rc=event_Idel();
            return rc;
            break;
        case 2:
            ROS_INFO(">>>Detecting");
            //FSM::rc = event_Detection();
            if(rc)
            {
                ROS_INFO("Detected!");
                ROS_INFO(">>>Ready for task...");
            }
            else
                ROS_WARN("Nothing has been detected!");
            return rc;
            break;
        case 3:
            ROS_INFO(">>>Tasking>>>");
            //FSM::rc = event_Tasking();
            if(rc)
                ROS_INFO("Task has been finished.");
            return rc;
            break;
        case 4:
            ROS_INFO(">>>Landing...");
            //FSM::rc = event_Landing();
            if(rc)
                ROS_INFO("Landed.");
            return rc;
            break;
        default:
            return rc;
            break;
    }
}
void FSM::run()
{
    for(;;)
    {
        FSM::event();
        if(FSM::current_state == 4)
        {
            ROS_INFO("Exit.");
            break;
        }
        FSM::event_trans(FSM::rc);
    }
}