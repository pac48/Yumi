#!/usr/bin/env python

import math
import sys
import rospy
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from numpy import linalg as LA
import tf
from tf2_msgs.msg import TFMessage
from geometry_msgs.msg import PoseStamped
from tf import transformations, TransformListener
import socket
from struct import unpack, pack
import time
from dynamics.srv import getM


class BallPublisher:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(None)
        self.TCP_IP = "127.0.0.1"
        self.TCP_PORT = 8080
        try:
            self.initialize()
        except Exception as e:
            self.sock = None
            print(e)
        self.ball_pos_pub = rospy.Publisher("/ball_position",Float32MultiArray,queue_size=1)
        self.ball_vel_pub = rospy.Publisher("/ball_velocity",Float32MultiArray,queue_size=1)
	self.ball_angVel_pub = rospy.Publisher("/ball_angular_velocity",Float32MultiArray,queue_size=1)
	self.pad_pos_pub = rospy.Publisher("/pad_position",Float32MultiArray,queue_size=1)
        self.pad_vel_pub = rospy.Publisher("/pad_velocity",Float32MultiArray,queue_size=1)
	self.pad_ori_pub = rospy.Publisher("/pad_orientation",Float32MultiArray,queue_size=1)
	self.pad_angVel_pub = rospy.Publisher("/pad_angular_velocity",Float32MultiArray,queue_size=1)

    def initialize(self):
        self.sock.settimeout(1.0)
        #self.sock.bind((self.TCP_IP, self.TCP_PORT))
        self.sock.connect((self.TCP_IP,self.TCP_PORT))
        self.old_pos=None
        self.old_time=None

        #self.sock.listen()

   # def connect(self):
   #     if (self.conn==None):
   #         try:
   #             self.conn, addr = self.server.accept()
   #             return True
   #         except Exception as e:
   #             return False
   #     else:
   #         return True

    def getMsgs(self):
	ball_pos_msg = Float32MultiArray()
        ball_vel_msg = Float32MultiArray()
	ball_angVel_msg = Float32MultiArray()
	pad_pos_msg = Float32MultiArray()
	pad_vel_msg = Float32MultiArray()
	pad_ori_msg = Float32MultiArray()
	pad_angVel_msg = Float32MultiArray()
        try:
            (data, addr) = self.sock.recvfrom(18*2*4)
            if (data==b""):
                print("no data")
                return
            format = ">" + "f"*18*2
            data = list(unpack(format,data))
	    pad_pos_msg.data = data[0:3]
	    pad_vel_msg.data = data[3:6]
	    pad_ori_msg.data = data[6:15]
	    pad_angVel_msg.data = data[15:18]
            ball_pos_msg.data = data[18:21]
	    ball_vel_msg.data = data[21:24]
	    ball_angVel_msg.data = data[33:36]
#    data = data+list(obj.position)+list(obj.worldLinearVelocity)+list(obj.worldOrientation[0]) \
 #               +list(obj.worldOrientation[1])+list(obj.worldOrientation[2])+list(obj.worldAngularVelocity)
            
            #print(packet)
        except Exception as e2:
            print(e2)
            return []
        return (ball_pos_msg,ball_vel_msg, ball_angVel_msg, pad_pos_msg,pad_vel_msg,pad_ori_msg, pad_angVel_msg)


if __name__ == '__main__':
    rospy.init_node('BallPublisher', anonymous=True)
    ballPublisher = BallPublisher()
    rate = rospy.Rate(120) # 10hz
    tmp = time.time()
    while not rospy.is_shutdown():

        #rate.sleep()
        if ballPublisher.sock==None:
            ballPublisher = BallPublisher()
        else:
            try:
                (ball_pos_msg,ball_vel_msg, ball_angVel_msg, pad_pos_msg,pad_vel_msg,pad_ori_msg, pad_angVel_msg) = ballPublisher.getMsgs()
               # if ballPublisher.old_pos==None:
               #     vel = np.zeros((7,1))
               #     ballPublisher.old_time = time.time()
               # else:
               #     pos_msg.data[0] = 1.0*pos_msg.data[0]+0.0*ballPublisher.old_pos[0]
               #     pos_msg.data[1] = 1.0*pos_msg.data[1]+0.0*ballPublisher.old_pos[1]
               #     pos_msg.data[2] = 1.0*pos_msg.data[2]+0.0*ballPublisher.old_pos[2]
                   # vel = (np.array(pos_msg.data)-np.array(ballPublisher.old_pos))/(1/60.0)


                    #vel = (np.array(pos_msg.data)-np.array(ballPublisher.old_pos))/(time.time()-ballPublisher.old_time)

                #ballPublisher.old_pos = pos_msg.data
                #ballPublisher.old_time=time.time()
                #vel_msg.data = vel.tolist()
		ballPublisher.pad_pos_pub.publish(pad_pos_msg)
                ballPublisher.pad_vel_pub.publish(pad_vel_msg)
		ballPublisher.pad_ori_pub.publish(pad_ori_msg)
		ballPublisher.pad_angVel_pub.publish(pad_angVel_msg)
                ballPublisher.ball_pos_pub.publish(ball_pos_msg)
                ballPublisher.ball_vel_pub.publish(ball_vel_msg)
		ballPublisher.ball_angVel_pub.publish(ball_angVel_msg)
                print(1/(time.time()-tmp+0.0000000000001))
                tmp = time.time()
            except Exception as e:
                print(e)
                pass


