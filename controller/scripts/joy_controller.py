#!/usr/bin/env python 
# Aran Sena 2018
#
# Code example only, provided without guarantees
#
# Example for how to get both cameras streaming together
#
####
# Standard imports

import rospy
from std_msgs.msg import Float32MultiArray, Bool
from sensor_msgs.msg import Joy


pub = rospy.Publisher("/operational_vel_R", Float32MultiArray, queue_size=2)
pub_gripper = rospy.Publisher("/gripper_command", Bool, queue_size=2)
grip_state = False
cartesian = True
cartisian = True

toggle_helper = dict()
speed_scale = {cartisian: .2*1.0, not cartisian: .2*2.0}
map1 = {0:0, 1:1, 2:2, 3:3, 4:4, 5:5} # joy to velocity mapping
map2 = {0:4, 1:3, 2:5, 3:0, 4:1, 5:2} # joy to angular velocity mapping
x_sign = {cartisian: 1, not cartisian: 1.0}
y_sign = {cartisian: 1, not cartisian: -1.0}
z_sign = {cartisian: 1, not cartisian: 1.0}
toggleBottons = [0, 1]
thresh = rospy.Duration(0, int(5E8))

def callback(msg):
    global grip_state
    global offset
    global cartisian

    xd = -1*1*msg.axes[1]*speed_scale[cartisian]*x_sign[cartisian]
    yd = -1*1*msg.axes[0]*speed_scale[cartisian]*y_sign[cartisian]
    zd = 0
    if (msg.buttons[5] == 1):
        zd = .3*speed_scale[cartisian]*z_sign[cartisian]
    if (msg.buttons[6] == 1):
        zd = -.3*speed_scale[cartisian]*z_sign[cartisian]
    if cartisian:
        map = map1
    else:
        map = map2
    command = Float32MultiArray()
    command.data = [0 for _ in range(6)]
    command.data[map[0]] = xd
    command.data[map[1]] = yd
    command.data[map[2]] = zd
    pub.publish(command)
    for b in toggleBottons:
        if (msg.buttons[b] == 1 and (b not in toggle_helper or (rospy.Time.now() - toggle_helper[b] > thresh))):
            toggle_helper[b] = rospy.Time.now()
            if (b==0): # gripper
                grip_state = not grip_state
                print(grip_state)
                msgB = Bool()
                msgB.data = grip_state
                pub_gripper.publish(msgB)
            elif (b==1):
                cartisian = not cartisian

if __name__ == '__main__':
    rospy.init_node('control_node')
    sub = rospy.Subscriber("/joy", Joy, callback)
    rospy.spin()
