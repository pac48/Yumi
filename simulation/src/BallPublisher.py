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
        self.ball_pub = rospy.Publisher("/ball_position",Float32MultiArray,queue_size=1)
        self.ball_vel_pub = rospy.Publisher("/ball_velocity",Float32MultiArray,queue_size=1)

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

    def getPacket(self):
        try:
            (data, addr) = self.sock.recvfrom(18*2*4)
            if (data==b""):
                print("no data")
                return
            format = ">" + "f"*18*2
            data = list(unpack(format,data))
            packet = data[18:21]
            #print(packet)
        except Exception as e2:
            print(e2)
            return []
        return packet


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
                pos_msg = Float32MultiArray()
                vel_msg = Float32MultiArray()
                pos_msg.data = ballPublisher.getPacket()
                ballPublisher.ball_pub.publish(pos_msg)
                if ballPublisher.old_pos==None:
                    vel = np.zeros((7,1))
                    ballPublisher.old_time = time.time()
                else:
                    vel = (np.array(pos_msg.data)-np.array(ballPublisher.old_pos))/(time.time()-ballPublisher.old_time)
                ballPublisher.old_pos = pos_msg.data
                ballPublisher.old_time=time.time()
                vel_msg.data = vel.tolist()
                ballPublisher.ball_pub.publish(pos_msg)
                ballPublisher.ball_vel_pub.publish(vel_msg)
                print(1/(time.time()-tmp+0.0000000000001))
                tmp = time.time()
            except Exception as e:
                print(e)
                pass


