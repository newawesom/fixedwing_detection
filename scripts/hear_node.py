#! /usr/bin/env python
#-*- coding: UTF-8 -*- 

import rospy
from mavros_msgs.msg import State
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped

current_state = State()
current_pose = PoseStamped()
current_vec = TwistStamped()
target_pose = PoseStamped()
def state_CB(msg):
    global current_state
    current_state = msg
def pose_CB(msg):
    global current_pose
    current_pose = msg
def vec_CB(msg):
    global current_vec
    current_vec = msg
def tar_CB(msg):
    global target_pose
    target_pose = msg
if __name__ == "__main__": 
    rospy.init_node("hear_node_py")

    state_sub = rospy.Subscriber('/mavros/state',State,callback=state_CB)
    pose_sub = rospy.Subscriber("/mavros/local_position/pose",PoseStamped,callback=pose_CB)
    vec_sub = rospy.Subscriber("/mavros/local_position/velocity_local",TwistStamped,callback=vec_CB)
    target_pub = rospy.Subscriber("/mavros/setpoint_position/local",PoseStamped,callback=tar_CB)
    rate = rospy.Rate(10)

    while(not rospy.is_shutdown()):
        if(current_state.armed == True):
            rospy.loginfo("MODE->%s Position->x:%f y:%f z:%f Velocity->x:%f y:%f z:%f",current_state.mode,current_pose.pose.position.x,current_pose.pose.position.y,current_pose.pose.position.z,current_vec.twist.linear.x,current_vec.twist.linear.y,current_vec.twist.linear.z)
            rospy.loginfo(">>>Target>>>x:%s y:%s z:%s", target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z)
        rate.sleep()