#include"../include/fixedwing/FinitStateMachine.h"
void test(ros::NodeHandle* nh){
    FSM fsm(nh);
    
    fsm.setStart_State(MY_DEBUG);
    fsm.setTrans(Transition(MY_DEBUG,MY_SUCCESS,MY_DEBUG));
    fsm.run();
}
void fixedwing(ros::NodeHandle* nh)
{
    FSM fsm(nh);

    fsm.setTrans(Transition(MY_TAKEOFF,MY_SUCCESS,MY_DETEC_1));
    fsm.setTrans(Transition(MY_TAKEOFF,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_DETEC_1,MY_SUCCESS,MY_TASK_1));
    fsm.setTrans(Transition(MY_DETEC_1,MY_FAIL,MY_DETEC_2));
    fsm.setTrans(Transition(MY_DETEC_2,MY_SUCCESS,MY_TASK_2));
    fsm.setTrans(Transition(MY_DETEC_2,MY_FAIL,MY_DETEC_1));
    fsm.setTrans(Transition(MY_TASK_1,MY_SUCCESS,MY_LAND));
    fsm.setTrans(Transition(MY_TASK_1,MY_FAIL,MY_TASK_2));
    fsm.setTrans(Transition(MY_TASK_2,MY_SUCCESS,MY_LAND));
    fsm.setTrans(Transition(MY_TASK_2,MY_FAIL,MY_TASK_1));
    fsm.run();
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"fixedwing_node");
    ros::NodeHandle nh;
    //fixedwing(&nh);
    test(&nh);
    return 0;
}