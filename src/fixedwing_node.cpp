#include"../include/fixedwing/FinitStateMachine.h"
void test(ros::NodeHandle* nh){
    FSM fsm(nh);

    fsm.setTrans(Transition(MY_TAKEOFF,MY_SUCCESS,MY_IDEL));
    fsm.setTrans(Transition(MY_TAKEOFF,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_IDEL,MY_FAIL,MY_LAND));
    fsm.setTrans(Transition(MY_IDEL,MY_SUCCESS,MY_DETEC));
    fsm.setTrans(Transition(MY_DETEC,MY_SUCCESS,MY_TASK));
    fsm.setTrans(Transition(MY_TASK,MY_SUCCESS,MY_LAND));
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
    fsm.setTrans(Transition(MY_TASK,MY_SUCCESS,MY_IDEL));
    fsm.run();
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"fixedwing_node");
    ros::NodeHandle nh;
    test(&nh);
    return 0;
}
/*
日志：
1、飞机的速度有一定的下限，目前已知的仿真环境飞机的速度不低于10m/s。不清楚是否对识别有影响。。。
(Saved)2、盘旋半径过小会使得飞机的roll角过大，相机主轴与地面成角度过大，不适和作为飞机的识别模式。(直接低速飞过，不在盘旋下识别)
(Saved)3、飞机的idel模式的设置是否有必要性。。。(其实没有什么必要，直接takeoff-->detect-->task-->land)
(Saved)4、每次设置新的飞行任务是否需要切换Hold模式再切换回Mission模式(不需要手动切换模式，完成当前飞行任务时候自动切换，且可作为下一个认为的反馈)，是否会重置Frame = 6 下的相对海拔高度(相对海拔只与home点有关)。
(Saved)5、C++语言和python语言写出的代码是否有区别，需要验证。
6、试飞地理位置需要重新配置.
(Saved)7、切换模式会进入死循环。（已将！=AUTO.MISSION修正为==AUTO.LOITER）
(Saved)8、没编译上？？
9、降落迎角过大
10、识别区域过小
*/
/*
主要任务（7月9日）：
1、完成自主起飞
2、巡航
3、识别
4、降落（可选）
*/
/*主要任务：
（Finished）1、完成仿真环境搭建
（Finished）2、完成状态机框架
（Finished）3、自主起飞与降落
4、自主巡航
(Abort)5、识别位置解算
(HARD!!)6、俯冲精确打击 识别接口->打击目标三维位置坐标+固定翼三维坐标+固定翼三向精确速度|->简单平飞：航点规划、抛点精确计算、舵机PWM信号串口传输
                                                                            |->俯冲投弹：板外自动控制？、
*/