#include"../include/fixedwing/FinitStateMachine.h"
void test(ros::NodeHandle* nh){
    FSM fsm(nh);

    fsm.setTrans(Transition(MY_TAKEOFF,MY_SUCCESS,MY_IDEL));
    fsm.setTrans(Transition(MY_TAKEOFF,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_IDEL,MY_SUCCESS,MY_LAND));
    fsm.run();
}
void fixedwing(ros::NodeHandle* nh)
{
    FSM fsm(nh);

    fsm.setTrans(Transition(MY_TAKEOFF,MY_SUCCESS,MY_IDEL));
    fsm.setTrans(Transition(MY_TAKEOFF,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_IDEL,MY_SUCCESS,MY_DETEC));
    fsm.setTrans(Transition(MY_IDEL,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_DETEC,MY_FAIL,MY_IDEL));
    fsm.setTrans(Transition(MY_DETEC,MY_SUCCESS,MY_TASK));
    fsm.setTrans(Transition(MY_TASK,MY_SUCCESS,MY_LAND));
    fsm.setTrans(Transition(MY_TASK,MY_FAIL,MY_DETEC));
    fsm.run();
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"fixedwing_node");
    ros::NodeHandle nh;
    fixedwing(&nh);
    return 0;
}