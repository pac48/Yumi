#!/usr/bin/env python

import sys
import rospy
import numpy as np
from std_msgs.msg import Float32MultiArray
np.set_printoptions(threshold=sys.maxsize)


class controller:

  def __init__(self):
    self.kp=1.0*1
    self.kd=1.0*0
    self.robot_R = [0.0,0.0,0.0,0.0,0.0,0.0]
    self.robot_L = [0.0,0.0,0.0,0.0,0.0,0.0]
    self.robot_pose = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0])
    self.robot_vel = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]) # message order is right then left
    self.goal = np.array([0.28637367486953735+.0, -0.23328398168087006-.0, 0.09796947240829468+.0, 0.9996191263198853, 0.027586041018366814, -0.0007667283643968403 /
                          0.16970492899417877, 0.3836527466773987, 0.16571415960788727, 0.8278752565383911, -0.37586238980293274, -0.4163532853126526])
    self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_operational_R,buff_size=1)
    self.operational_sub = rospy.Subscriber("/operational_position_L",Float32MultiArray,self.callback_operational_L,buff_size=1)
    self.operational_sub = rospy.Subscriber("/goal_position",Float32MultiArray,self.callback_goal,buff_size=1)
    self.operational_pub = rospy.Publisher("/operational_velocity_command_R",Float32MultiArray,queue_size=10)
    self.moving=True

  def getVelMsg(self):
    p = (self.goal[0:3]-self.robot_pose[0:3])
    d = self.goal[0:3]*0-self.robot_vel[0:3]
    direction = p/np.linalg.norm(p)
    val = direction*np.linalg.norm(p)*self.kp+direction*d*self.kd
    for i in range(0,3):
      self.robot_vel[i] = val[i]
    msg = Float32MultiArray()
    if np.linalg.norm(p)<0.01 and np.linalg.norm(d)<0.01:
      msg.data =(self.robot_vel*0).tolist()
      self.moving=False
    else:
      msg.data = self.robot_vel.tolist()
    return msg

  def callback_operational_R(self,msg):
    self.robot_R=list(msg.data)
    for i in range(0,len(self.robot_L)):
      self.robot_R.append(self.robot_L[i])
    self.robot_pose= np.array(self.robot_R)
    if self.moving==True:
      self.operational_pub.publish(self.getVelMsg())

  def callback_operational_L(self,msg):
    self.robot_L=list(msg.data)

  def callback_goal(self,msg):
    self.goal = np.array(msg.data)
    self.moving=True

if __name__ == '__main__':
  rospy.init_node('py_controllers', anonymous=True)
  ic = controller()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
