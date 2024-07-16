#! /usr/bin/env python
#-*- coding: UTF-8 -*- 

import rospy
import math
from mavros_msgs.msg import State
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
tar_x=225
tar_y=0
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
def compute_time(vz,z):
    return ((2.0 * vz + math.sqrt(abs(4.0 * vz * vz + 8.0 * 9.8 * z)))/(2.0 * 9.8))
def combat_d_x(vx,t,cur_x):
    dx = tar_x - cur_x
    return abs(dx - vx * t)
def combat_d_y(vy,t,cur_y):
    dy = tar_y - cur_y
    return abs(dy - vy * t)
if __name__ == "__main__": 
    rospy.init_node("hear_node_py")

    state_sub = rospy.Subscriber('/mavros/state',State,callback=state_CB)
    pose_sub = rospy.Subscriber("/mavros/local_position/pose",PoseStamped,callback=pose_CB)
    vec_sub = rospy.Subscriber("/mavros/local_position/velocity_local",TwistStamped,callback=vec_CB)
    target_pub = rospy.Subscriber("/mavros/setpoint_position/local",PoseStamped,callback=tar_CB)
    rate = rospy.Rate(10)

    while(not rospy.is_shutdown()):
        rospy.loginfo("Position->x:%f y:%f z:%f",current_pose.pose.position.x,current_pose.pose.position.y,current_pose.pose.position.z)
        rospy.loginfo("Velocity->x:%f y:%f z:%f",current_vec.twist.linear.x,current_vec.twist.linear.y,current_vec.twist.linear.z)
        t = compute_time(current_vec.twist.linear.z,current_pose.pose.position.z)
        rospy.logwarn("Difference->:x:%f y:%f t:%f",combat_d_x(current_vec.twist.linear.x,t,current_pose.pose.position.x),combat_d_y(current_vec.twist.linear.y,t,current_pose.pose.position.y),t)
        rate.sleep()