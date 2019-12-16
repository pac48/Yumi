#!/usr/bin/env python

import sys
import rospy
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
np.set_printoptions(threshold=sys.maxsize)

class controller_jug:

  def __init__(self):
    self.kp=1.0*1
    self.kd=1.0*0
    self.robot_R = [0.0,0.0,0.0,0.0,0.0,0.0]
    self.robot_L = [0.0,0.0,0.0,0.0,0.0,0.0]
    self.robot_pose = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0])
    self.robot_vel = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]) # message order is right then left
    self.goal = np.array([0.28637367486953735, -0.23328398168087006, 0.09796947240829468, 0.9996191263198853+0.1, 0.027586041018366814, -0.0007667283643968403 /
                          0.16970492899417877, 0.3836527466773987, 0.16571415960788727, 0.8278752565383911, -0.37586238980293274, -0.4163532853126526])
    self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_operational_R,buff_size=1)
    self.operational_sub = rospy.Subscriber("/operational_position_L",Float32MultiArray,self.callback_operational_L,buff_size=1)
    self.operational_sub = rospy.Subscriber("/goal_position",Float32MultiArray,self.callback_goal,buff_size=1)
    self.operational_pub = rospy.Publisher("/operational_velocity_command",Float32MultiArray,queue_size=10)
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
  rospy.init_node('controller_jug', anonymous=True)
  ic = controller_jug()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")

#!/usr/bin/env python

import sys
import rospy
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from numpy import linalg as LA
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
np.set_printoptions(threshold=sys.maxsize)

class controller_node_jug:

  def __init__(self):
    self.robot_home_R = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    self.robot_home_L = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

    self.robot_pose = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0])
    self.robot_vel = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]) # message order is right then left

    self.goal = np.array([0.0+0.1, 0.0, 0.0, 0.0, 0.0, 0.0 /
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

    # self.Jacobian_R = getJacobian(self.goal)
    # self.inv_Jacobian_R = invJacobian(self.Jacobian_R)

    self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_joint_angles,buff_size=1)
    self.operational_sub = rospy.Subscriber("/goal_position_Sean_sim",Float32MultiArray,self.callback_goal_Sean_sim,buff_size=1)

    self.operational_pub = rospy.Publisher("/operational_velocity_command",Float32MultiArray,queue_size=10)
    self.moving=True

    # rate = rospy.Rate(10) # 10hz

  def callback_goal_Sean_sim(self,msg):
    self.goal = np.array(msg.data)
    self.moving = True

  def callback_joints_angles(self,msg):
    self.theta = list(msg.data)
    if self.moving==True:
      self.operational_pub.publish(self.getVelMsg())

  def getJacobian(self):
    MD_0 = np.array([0.0, 0.0, 0.0]) #Mid point of a reference point
    RP = np.array([438.94, 307.41, 201.56])#Mid point of a reference point from CAD model

    #Joint 1
    MD_1 = np.array([466.51, 246.19, 575.69]) - RP
    #Take two point on the same plane to find normal vector
    P11 = np.array([454.03, 259.27, 606.82]) - RP - MD_1
    P12 = np.array([482.88, 276.6, 569.47]) - RP - MD_1

    #Joint 2
    MD_2 = np.array([538.86, 178.9, 678.43]) - RP
    P21 = np.array([521.17, 176.56, 669.39]) - RP - MD_2
    P22 = np.array([537.75, 198.65, 675.48]) - RP - MD_2

    #Joint 3
    MD_3 = np.array([477.31, 85.66, 601.74]) - RP
    P31 = np.array([489.05, 76.6, 588.65]) - RP - MD_3
    P32 = np.array([473.26, 100.53, 589.32]) - RP - MD_3

    #Joint 4
    MD_4 = np.array([414.11, -19.98, 533.33]) - RP
    P41 = np.array([417.63, -13.83, 546.44]) - RP - MD_4
    P42 = np.array([401.1, -24.55, 538.97]) - RP - MD_4

    #Joint 5
    MD_5 = np.array([477.01, 24.03, 418.39]) - RP
    P51 = np.array([481.43, 34.43, 428.26]) - RP - MD_5
    P52 = np.array([469.06, 34.4, 411.02]) - RP - MD_5

    #Joint 6
    MD_6 = np.array([569.49, 98.8, 327.86]) - RP
    P61 = np.array([561.49, 101.25, 313.3]) - RP - MD_6
    P62 = np.array([546.85, 96.87, 327.54]) - RP - MD_6

    #Joint 7
    MD_7 = np.array([581.27, 49.12, 347.1]) - RP
    P71 = np.array([573.19, 50.63, 341.48]) - RP - MD_7
    P72 = np.array([581.27, 58.73, 349.69]) - RP - MD_7

    #take a cross product of two normalized vectors for each joint
    #both vectors are on the same plane
    #Nomal_# vector is in z-direction (local coordinate system of each joint)
    Normal_1 = np.cross([P11 / LA.norm(P11)], [P12 / LA.norm(P12)])
    Normal_2 = -np.cross([P21 / LA.norm(P21)], [P22 / LA.norm(P22)])
    Normal_3 = np.cross([P31 / LA.norm(P31)], [P32 / LA.norm(P32)])
    Normal_4 = np.cross([P41 / LA.norm(P41)], [P42 / LA.norm(P42)])
    Normal_5 = np.cross([P51 / LA.norm(P51)], [P52 / LA.norm(P52)])
    Normal_6 = np.cross([P61 / LA.norm(P61)], [P62 / LA.norm(P62)])
    Normal_7 = np.cross([P71 / LA.norm(P71)], [P72 / LA.norm(P72)])

    Normal_0 = [0.0, 0.0, 1.0]

    #Find representation of global coordinate system to each join.
    #R0_# - from frame 0 to frame #

    #add function to get R
    #COMPARE WITH MATLAB
    def getR(zi, zj):

      zj=zj/LA.norm(zj)
      zi=zi/LA.norm(zi)

      theta=np.arctan2(LA.norm(np.cross(zi, zj)), np.dot(zi, zj))
      k=np.cross(zi, zj)
      k=k/LA.norm(k)
      K = np.array([
        [0.0, -k[0, 2], k[0, 1]],
        [k[0, 2], 0.0, -k[0, 0]],
        [-k[0, 1], k[0, 0], 0.0]
      ])

      R = np.eye(3) + np.sin(theta)*K + (1-np.cos(theta))*np.matmul(K,K)
      return (R)

    R0_1 = getR(Normal_1, Normal_0)
    R0_2 = getR(Normal_2, Normal_0)
    R0_3 = getR(Normal_3, Normal_0)
    R0_4 = getR(Normal_4, Normal_0)
    R0_5 = getR(Normal_5, Normal_0)
    R0_6 = getR(Normal_6, Normal_0)
    R0_7 = getR(Normal_7, Normal_0)

    T0_1H=np.ones((4,4))
    T0_1H[0:3, 0:3]=np.matrix.transpose(R0_1)
    T0_1H[0:3, 3]=MD_1 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_1H[3, 0:3]=0.0

    T0_2H=np.ones((4,4))
    T0_2H[0:3, 0:3]=np.matrix.transpose(R0_2)
    T0_2H[0:3, 3]=MD_2 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_2H[3, 0:3]=0.0

    T0_3H=np.ones((4,4))
    T0_3H[0:3, 0:3]=np.matrix.transpose(R0_3)
    T0_3H[0:3, 3]=MD_3 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_3H[3, 0:3]=0.0

    T0_4H=np.ones((4,4))
    T0_4H[0:3, 0:3]=np.matrix.transpose(R0_4)
    T0_4H[0:3, 3]=MD_4 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_4H[3, 0:3]=0.0

    T0_5H=np.ones((4,4))
    T0_5H[0:3, 0:3]=np.matrix.transpose(R0_5)
    T0_5H[0:3, 3]=MD_5 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_5H[3, 0:3]=0.0

    T0_6H=np.ones((4,4))
    T0_6H[0:3, 0:3]=np.matrix.transpose(R0_6)
    T0_6H[0:3, 3]=MD_6 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_6H[3, 0:3]=0.0

    T0_7H=np.ones((4,4))
    T0_7H[0:3, 0:3]=np.matrix.transpose(R0_7)
    T0_7H[0:3, 3]=MD_7 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    T0_7H[3, 0:3]=0.0


    t1 = self.theta[0, 1]
    t2 = self.theta[0, 2]
    t3 = self.theta[0, 3]
    t4 = self.theta[0, 4]
    t5 = self.theta[0, 5]
    t6 = self.theta[0, 6]
    t7 = self.theta[0, 6]

    # t1=0.0
    # t2=0.0
    # t3=0.0
    # t4=0.0
    # t5=0.0
    # t6=0.0
    # t7=0.0

    def findR(t):
      R=np.array([
        [np.cos(t), -np.sin(t), 0.0, 0.0],
        [np.sin(t), np.cos(t), 0.0, 0.0],
        [0.0, 0.0, 1.0, 0.0],
        [0.0, 0.0, 0.0, 1.0]
      ])
      return(R)

    R1=findR(t1)
    R2=findR(t2)
    R3=findR(t3)
    R4=findR(t4)
    R5=findR(t5)
    R6=findR(t6)
    R7=findR(t7)


    T0_1=T0_1H
    T1_2=np.matmul(R1, (np.matmul(np.linalg.inv(T0_1H), T0_2H))) # mistake is here - (np.linalg.inv(T0_1H)*T0_2H)
    T2_3=np.matmul(R2, (np.matmul(np.linalg.inv(T0_2H), T0_3H)))
    T3_4=np.matmul(R3, (np.matmul(np.linalg.inv(T0_3H), T0_4H)))
    T4_5=np.matmul(R4, (np.matmul(np.linalg.inv(T0_4H), T0_5H)))
    T5_6=np.matmul(R5, (np.matmul(np.linalg.inv(T0_5H), T0_6H)))
    T6_7=np.matmul(R6, (np.matmul(np.linalg.inv(T0_6H), T0_7H)))

    T0_1=T0_1H
    T0_2=np.matmul(T0_1, T1_2)
    T0_3=np.matmul(np.matmul(T0_1, T1_2), T2_3)
    T0_4=np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4)
    T0_5=np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5)
    T0_6=np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5), T5_6)
    T0_7=np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5), T5_6), T6_7)

    p0=np.zeros((1, 3))
    p1=T0_1[0:3, 3]
    p2=T0_2[0:3, 3]
    p3=T0_3[0:3, 3]
    p4=T0_4[0:3, 3]
    p5=T0_5[0:3, 3]
    p6=T0_6[0:3, 3]
    p7=T0_7[0:3, 3]

    z0=np.array([0.0,  0.0, 1.0])
    z1=T0_1H[0:3, 2]
    z2=T0_2H[0:3, 2]
    z3=T0_3H[0:3, 2]
    z4=T0_4H[0:3, 2]
    z5=T0_5H[0:3, 2]
    z6=T0_6H[0:3, 2]
    z7=T0_7H[0:3, 2]

    P=T0_7[0:3, 3]

    J=np.ones((6, 7))
    J[0:3, 0]=np.cross(z1, P-p1)
    J[0:3, 1]=np.cross(z2, P-p2)
    J[0:3, 2]=np.cross(z3, P-p3)
    J[0:3, 3]=np.cross(z4, P-p4)
    J[0:3, 4]=np.cross(z5, P-p5)
    J[0:3, 5]=np.cross(z6, P-p6)
    J[0:3, 6]=np.cross(z7, P-p7)

    J[3:6, 0]=z1
    J[3:6, 1]=z2
    J[3:6, 2]=z3
    J[3:6, 3]=z4
    J[3:6, 4]=z5
    J[3:6, 5]=z6
    J[3:6, 6]=z7

    # Final position of end-effector

    dx=self.goal[0, 1]
    dy=self.goal[0, 2]
    dz=self.goal[0, 3]
    wx=self.goal[0, 4]
    wy=self.goal[0, 5]
    wz=self.goal[0, 6]

    # dx=0.0
    # dy=0.0
    # dz=0.0
    # wx=0.0
    # wy=0.0
    # wz=0.0

    e=np.array([dx, dy, dz, wx, wy, wz])

    # Find pseudo inverso of Jacobian
    Jinv=np.linalg.pinv(J)

    # Change in angle from pseudo inverse
    angl_vel=np.matmul(Jinv, e)
    self.pose = angl_vel


    # msg = Float32MultiArray()
    #
    # self.robot_arm_R = deltaTH
    #
    # msg.data = self.deltaTH.tolist()

    p = (self.goal[0:3]-self.pose[0:3])
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

if __name__ == '__main__':
  rospy.init_node('controller_node_jug', anonymous=True)
  ic = controller_node_jug()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")