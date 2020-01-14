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


class BlenderBridge:
    def __init__(self):
        #self.tf = TransformListener()
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(None)
        try:
            self.sock.connect(("127.0.0.1", 5000))

        except Exception as e:
            self.sock = None
            print(e)
        self.joint_states_sub = rospy.Subscriber("/joint_state_R",Float32MultiArray,self.callback_joint_state_R,buff_size=1)
        self.joints_R =[0.0,0.0,0.0,0.0,0.0,0.0,0.0]
        #self.sub = rospy.Subscriber("/tf",TFMessage,self.callback,buff_size=1)

    def callback_joint_state_R(self,msg):
        if any(np.isnan(msg.data)):
            return
        self.joints_R = msg.data[:7]

    def buildPacket(self):
        packet =[]
        frames = ["yumi_link_1_r", "yumi_link_2_r","yumi_link_3_r","yumi_link_4_r", "yumi_link_5_r", "yumi_link_6_r", "yumi_link_7_r"]
        #rospy.wait_for_service('getTranformations')
        try:
            serv= rospy.ServiceProxy('getTranformations', getM)
            resp = serv(self.joints_R)
        except rospy.ServiceException, e:
            print("Service call failed: %s"%e)
            return
        i = 0
        data = list(resp.M)
        for name in frames:
            t = rospy.Duration()
            #position, quaternion = self.tf.lookupTransform("yumi_body", name, t)
            position = data[i:i+3]
            quaternion = data[i+3:i+7]
            i=i+7
            packet = packet+position
            packet = packet+quaternion
        return packet

    def sendPacket(self,packet):
        b = []
        for i in range(0,len(packet)):
            v1 = float(packet[i])
            format = ">" + "f"
            b1 = pack(format,v1)
            b.append(b1)
        try:
            bytes = b''.join(b)
         #   if (len(bytes)==196):
            self.sock.send(bytes)
        except Exception as e:
            print(e)

if __name__ == '__main__':
    rospy.init_node('BlenderBridge', anonymous=True)
    blenderBridge = BlenderBridge()
    rate = rospy.Rate(60) # 10hz

    while not rospy.is_shutdown():
        tmp = time.time()
        rate.sleep()
        if blenderBridge.sock==None:
            blenderBridge = BlenderBridge()
        else:
            try:
                packet = blenderBridge.buildPacket()
                blenderBridge.sendPacket(packet)
                print('sent')
            except Exception as e:
                print(e)

        print(1/(time.time()-tmp+0.0000000000001))