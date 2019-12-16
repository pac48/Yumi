#!/usr/bin/env python

import sys
import rospy
import numpy as np
from std_msgs.msg import Float32

class gripper_test:

    def __init__(self):
        self.pub_gripper_command_R = rospy.Publisher("gripper_command_R",Float32,queue_size=10)
        rospy.init_node('gripper', anonymous=True)
        self.msg_gripper_command_R = Float32()
        rate = rospy.Rate(0.3) # 10hz
        i=1.0
        while not rospy.is_shutdown():
            #self.send()
            self.msg_gripper_command_R.data=-20.0*i
            i*=-1
            self.pub_gripper_command_R.publish(self.msg_gripper_command_R)
            rate.sleep()
            print("hi")

    def send(self):
        self.msg_gripper_command_R.data=-20.0
        self.pub_gripper_command_R.publish(self.msg_gripper_command_R)
        print("hi")


if __name__ == '__main__':
    try:
        gripper_test()
    except rospy.ROSInterruptException:
        pass


