#include"../include/fixedwing/FinitStateMachine.h"
void test(ros::NodeHandle* nh){
    FSM fsm(nh);

    fsm.setTrans(Transition(TAKEOFF,SUCCESS,IDEL));
    fsm.setTrans(Transition(TAKEOFF,FAIL,LAND));
    fsm.setTrans(Transition(IDEL,FAIL,LAND));
    fsm.setTrans(Transition(IDEL,SUCCESS,LAND));
    fsm.run();
}
void fixedwing(ros::NodeHandle* nh)
{
    FSM fsm(nh);

    fsm.setTrans(Transition(TAKEOFF,SUCCESS,IDEL));
    fsm.setTrans(Transition(TAKEOFF,FAIL,LAND));
    fsm.setTrans(Transition(IDEL,SUCCESS,DETEC));
    fsm.setTrans(Transition(IDEL,FAIL,LAND));
    fsm.setTrans(Transition(DETEC,FAIL,IDEL));
    fsm.setTrans(Transition(DETEC,SUCCESS,TASK));
    fsm.setTrans(Transition(TASK,SUCCESS,IDEL));
    fsm.run();
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"fixedwing");
    ros::NodeHandle nh;
    test(&nh);
    return 0;
}
/*
日志：
1、飞机的速度有一定的下限，目前已知的仿真环境飞机的速度不低于10m/s。不清楚是否对识别有影响。。。
2、盘旋半径过小会使得飞机的roll角过大，相机主轴与地面成角度过大，不适和作为飞机的识别模式。
3、飞机的idel模式的设置是否有必要性。。。
(Half Saved)4、每次设置新的飞行任务是否需要切换Hold模式再切换回Mission模式(不需要手动切换模式，完成当前飞行任务时候自动切换，且可作为下一个认为的反馈)，是否会重置Frame = 6 下的相对海拔高度。
(Saved)5、C++语言和python语言写出的代码是否有区别，需要验证。
*/