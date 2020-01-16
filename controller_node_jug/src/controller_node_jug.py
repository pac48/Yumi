#!/usr/bin/env python

import math
import sys
import rospy
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from numpy import linalg as LA
import tf
from geometry_msgs.msg import PoseStamped
from tf import transformations, TransformListener
from dynamics.srv import getM


from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

np.set_printoptions(threshold=sys.maxsize)

#final number e*invJ (array of 7 number) needs to be send to joint_command topic. It tells each joint by how much it needs to rotate in order to get
#to desired position and desired velocity from array e[dx dy dz wx wy wz]


#


class controller:

    def __init__(self):
        # self.kp=1.0*1
        self.moving=True
        self.robot_L = None
        self.robot_R= None
        self.theta= None
        self.goal =np.array([0.0 , 0.0 , 0.0])
        self.ball_pos =np.array([0.0 , 0.0 , 0.0])
        self.ball_vel =np.array([0.0 , 0.0 , 0.0])
        self.kp = 0.3

        self.kp_z = 1.0*0.8

        self.kd = 1.0*0
        # self.kd=1.0*0
        self.robot_R = [0.0,0.0,0.0,0.0,0.0,0.0]
        self.robot_L = [0.0,0.0,0.0,0.0,0.0,0.0]
        self.robot_pose = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0])
        self.robot_vel = np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]) # message order is right then left
        # self.goal = np.array([0.28637367486953735, -0.23328398168087006, 0.09796947240829468, 0.9996191263198853, 0.027586041018366814, -0.0007667283643968403 /
        #                       0.16970492899417877, 0.3836527466773987, 0.16571415960788727, 0.8278752565383911, -0.37586238980293274, -0.4163532853126526])

        # Subscribing to join_state_topic. It should contain message from YuMi Paul node
        # [right arm left arm - joints angles]
        self.tf = TransformListener()
        self.operational_pub = rospy.Publisher("/operational_velocity_command",Float32MultiArray,queue_size=1)

        self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_operational_R,buff_size=1)
        # Subscribing to simulation from Sean with ball's position and velocity
        self.camera_coords_sub = rospy.Subscriber("/camera_coords",Float32MultiArray,self.callback_camera_coords,buff_size=1)
        self.ball_sub = rospy.Subscriber("/ball_position",Float32MultiArray,self.callback_ball,buff_size=1)
        self.ball_vel_sub = rospy.Subscriber("/ball_velocity",Float32MultiArray,self.callback_vel_ball,buff_size=1)
        self.joint_states_sub = rospy.Subscriber("/joint_state_R",Float32MultiArray,self.callback_joint_state_R,buff_size=1)
        self.joints_R =[0.0,0.0,0.0,0.0,0.0,0.0,0.0]


    # Publishing to joint command which receives a message from Yumi Paul node
        # What we actually sending to the robot to do
        # Use Jacobian matrix to find joint velocities for each joint
        self.joint_command_pub = rospy.Publisher("/joint_command_topic",Float32MultiArray,queue_size=10)

        # Publishing to yumi hand topic with velocities message
        # end effector position (need to add rocket length) -[x y z] - get it from transform from 0 to 7
        # Try to get this message from already existing function getVel
        self.yumi_hand_pub = rospy.Publisher("/yumi_hand_topic",Float32MultiArray,queue_size=10)


    def callback_joint_state_R(self,msg):
        if any(np.isnan(msg.data)):
            return
        self.joints_R = msg.data[:7]

    def callback_ball(self,msg):
        self.ball_pos[0] = msg.data[0]
        self.ball_pos[1] = msg.data[1]
        self.ball_pos[2] = msg.data[2]

    def callback_vel_ball(self,msg):
        self.ball_vel[0] = msg.data[0]
        self.ball_vel[1] = msg.data[1]
        self.ball_vel[2] = msg.data[2]

    def callback_camera_coords(self,msg):
        if self.tf.frameExists("yumi_body") and self.tf.frameExists("camera_depth_optical_frame"):
            t = self.tf.getLatestCommonTime("yumi_body", "camera_depth_optical_frame")
            #position, quaternion = self.tf.lookupTransform("yumi_body", "camera_depth_optical_frame", t)
            p1 = PoseStamped()
            p1.pose.position.x =msg.data[0]
            p1.pose.position.y =msg.data[1]
            p1.pose.position.z =msg.data[2]
            p1.header.frame_id = "camera_depth_optical_frame"
            p_in_base = self.tf.transformPose("yumi_body", p1)
            self.goal[0] = p_in_base.pose.position.x
            self.goal[1] = p_in_base.pose.position.y
            #print(p1)

    def callback_operational_R(self,msg):
        self.robot_L = [0.0,0.0,0.0,0.0,0.0,0.0]
        self.robot_R=list(msg.data)
        self.theta=self.robot_R[0:8]
        for i in range(0,len(self.robot_L)):
            self.robot_R.append(self.robot_L[i]) #combines two arrays
        self.robot_pose= np.array(self.robot_R)

        if self.moving==True:
            vel_msg=self.getVelMsg()
            self.operational_pub.publish(vel_msg)



            #velocity message for joints (14 values for each joint. Left can be 0).

            # self.joint_command_pub.publish(vel_Msg)
            # self.yumi_hand_pub.publish(hand_msg)


    def callback_goal(self,msg):
        self.goal = np.array(msg.data)
        self.moving=True

    def getVelMsg(self):
        #self.goal = np.array([0.88,  0.343, 0.3])
        self.ball_vel= self.ball_vel
        try:
            serv= rospy.ServiceProxy('getLastTransformation', getM)
            resp = serv(self.joints_R)
        except rospy.ServiceException, e:
            print("Service call failed: %s"%e)
            return self.robot_vel

        Te = np.matrix(np.zeros((4,4)))
        Te[0:3,:] = np.reshape(resp.M,(3,4))
        Te[3,3] = 1.0
        #Te = np.linalg.inv(Te)
        Tep = np.matrix([[1.0, 0.0,0.0, 0.0],[0.0, 0.0, -1.0, 0.0],[0.0, 1.0, 0.0, 0.25],[0.0, 0.0, 0.0 ,1.0]])
        #Tep = np.matrix([[0.0, 0.0,1.0, 0.0],[0.0, 1.0, 0.0, 0.0],[-1.0, 0.0, 0.0, 0.05],[0.0, 0.0, 0.0 ,1.0]])
        #Tep = np.matrix([[0.0, -1.0 ,0.0, 0.0],[1.0, 0.0, 0.0, 0.0],[0.0, 0.0, 1.0, 0.05],[0.0, 0.0, 0.0 ,1.0]])
        # Tep = np.matrix([[1.0, 0.0 ,0.0, 0.0],[0.0, 1.0, 0.0, 0.0],[0.0, 0.0, 1.0, 0.05],[0.0, 0.0, 0.0 ,1.0]])
    #T0p = np.linalg.inv(np.matmul(Te,Tep))
        #Tep = np.linalg.inv(Tep)
        T0p = np.matmul(Te,Tep)
        tmp = T0p[0:3,3]
        self.ball_pos[2] = 0.25
        p = (self.ball_pos[0:3]-np.array(tmp.transpose()))*2
        normal = np.matmul(T0p[0:3,0:3],np.array([1.0,0.0,0.0]))
        self.ball_pos[2] = 0.0
        save = np.array([0.0,0.0,1.0])-0.5*(self.ball_pos-np.array([0.2,-0.5,0.0]))
        #save[1]*=-1
        save =save/np.linalg.norm(save)
        rot = np.cross(normal,np.array(save))
        rot = np.matrix(rot).transpose()
        tmp = normal
        tmp =tmp/np.linalg.norm(normal)
        an1 = np.arccos(np.clip(np.dot(tmp,np.array([-0.0,0.0,1.0])), -1.0, 1.0))
        #Tpe = np.linalg.inv(Tep)
        #rot = np.matmul(Tpe[0:3,0:3],np.matrix(rot).transpose())
        # d = self.goal[0:3]*0-self.robot_vel[0:3]
        direction = p/np.linalg.norm(p)
        val = direction*np.linalg.norm(p)*self.kp #+direction*d*self.kd
        val = p
        for i in range(0,2):
            #val[i] = np.sign(val[i])
            self.robot_vel[i] =7.0*val[0,i]+self.ball_vel[i]
        self.robot_vel[2] = 4.0*val[0,2]
        # p_z = self.goal[2]-self.robot_pose[2]
        # direction_z = p_z/np.linalg.norm(p_z)
        # val_z = -direction_z*np.linalg.norm(p_z)*self.kp_z

        #val_z = 0.0
        #if (self.ball_vel[2]<0.0):
        self.robot_vel[2] += -1*0.4*self.ball_vel[2]/(2*np.abs(val[0,2])+0.2)
        #else:
       #     self.robot_vel[2] += 0.0
        tmp = self.robot_pose[3:6]
        tmp =tmp/np.linalg.norm(self.robot_pose[3:6])
        rot2 =np.cross(tmp,np.array([1.0,0.0,0.0]))
        an2 = np.arccos(np.clip(np.dot(tmp,np.array([1.0,0.0,0.0])), -1.0, 1.0))
        # np.arccos(np.dot(self.robot_pose[3:6],np.array([1.0,0.0,0.0])))
        self.robot_vel[3:6] = (rot2*0.1*an2+rot.transpose()*an1[0,0])*200
        #self.robot_vel[1]=0.0
        #self.robot_vel[0]=0.1

        vel_msg = Float32MultiArray()
        vel_msg.data = self.robot_vel.tolist()

        return vel_msg

    # def getMsgs(self):
    #     MD_0 = np.array([0.0, 0.0, 0.0]) #Mid point of a reference point
    #     RP = np.array([438.94, 307.41, 201.56])#Mid point of a reference point from CAD model
    #
    #     #Joint 1
    #     MD_1 = np.array([466.51, 246.19, 575.69]) - RP
    #     #Take two point on the same plane to find normal vector
    #     P11 = np.array([454.03, 259.27, 606.82]) - RP - MD_1
    #     P12 = np.array([482.88, 276.6, 569.47]) - RP - MD_1
    #
    #     #Joint 2
    #     MD_2 = np.array([538.86, 178.9, 678.43]) - RP
    #     P21 = np.array([521.17, 176.56, 669.39]) - RP - MD_2
    #     P22 = np.array([537.75, 198.65, 675.48]) - RP - MD_2
    #
    #     #Joint 3
    #     MD_3 = np.array([477.31, 85.66, 601.74]) - RP
    #     P31 = np.array([489.05, 76.6, 588.65]) - RP - MD_3
    #     P32 = np.array([473.26, 100.53, 589.32]) - RP - MD_3
    #
    #     #Joint 4
    #     MD_4 = np.array([414.11, -19.98, 533.33]) - RP
    #     P41 = np.array([417.63, -13.83, 546.44]) - RP - MD_4
    #     P42 = np.array([401.1, -24.55, 538.97]) - RP - MD_4
    #
    #     #Joint 5
    #     MD_5 = np.array([477.01, 24.03, 418.39]) - RP
    #     P51 = np.array([481.43, 34.43, 428.26]) - RP - MD_5
    #     P52 = np.array([469.06, 34.4, 411.02]) - RP - MD_5
    #
    #     #Joint 6
    #     MD_6 = np.array([569.49, 98.8, 327.86]) - RP
    #     P61 = np.array([561.49, 101.25, 313.3]) - RP - MD_6
    #     P62 = np.array([546.85, 96.87, 327.54]) - RP - MD_6
    #
    #     #Joint 7
    #     MD_7 = np.array([581.27, 49.12, 347.1]) - RP
    #     P71 = np.array([573.19, 50.63, 341.48]) - RP - MD_7
    #     P72 = np.array([581.27, 58.73, 349.69]) - RP - MD_7
    #
    #     #take a cross product of two normalized vectors for each joint
    #     #both vectors are on the same plane
    #     #Nomal_# vector is in z-direction (local coordinate system of each joint)
    #     Normal_1 = np.cross([P11 / LA.norm(P11)], [P12 / LA.norm(P12)])
    #     Normal_2 = -np.cross([P21 / LA.norm(P21)], [P22 / LA.norm(P22)])
    #     Normal_3 = np.cross([P31 / LA.norm(P31)], [P32 / LA.norm(P32)])
    #     Normal_4 = np.cross([P41 / LA.norm(P41)], [P42 / LA.norm(P42)])
    #     Normal_5 = np.cross([P51 / LA.norm(P51)], [P52 / LA.norm(P52)])
    #     Normal_6 = np.cross([P61 / LA.norm(P61)], [P62 / LA.norm(P62)])
    #     Normal_7 = np.cross([P71 / LA.norm(P71)], [P72 / LA.norm(P72)])
    #
    #     Normal_0 = [0.0, 0.0, 1.0]
    #
    # #Find representation of global coordinate system to each join.
    # #R0_# - from frame 0 to frame #
    #
    # #add function to get R
    # #COMPARE WITH MATLAB
    #     def getR(zi, zj):
    #
    #         zj=zj/LA.norm(zj)
    #         zi=zi/LA.norm(zi)
    #
    #         theta=np.arctan2(LA.norm(np.cross(zi, zj)), np.dot(zi, zj))
    #         k=np.cross(zi, zj)
    #         k=k/LA.norm(k)
    #         K = np.array([
    #             [0.0, -k[0, 2], k[0, 1]],
    #             [k[0, 2], 0.0, -k[0, 0]],
    #             [-k[0, 1], k[0, 0], 0.0]
    #         ])
    #
    #         R = np.eye(3) + np.sin(theta)*K + (1-np.cos(theta))*np.matmul(K,K)
    #         return (R)
    #
    #     R0_1 = getR(Normal_1, Normal_0)
    #     R0_2 = getR(Normal_2, Normal_0)
    #     R0_3 = getR(Normal_3, Normal_0)
    #     R0_4 = getR(Normal_4, Normal_0)
    #     R0_5 = getR(Normal_5, Normal_0)
    #     R0_6 = getR(Normal_6, Normal_0)
    #     R0_7 = getR(Normal_7, Normal_0)
    #
    #     T0_1H=np.ones((4,4))
    #     T0_1H[0:3, 0:3]=np.matrix.transpose(R0_1)
    #     T0_1H[0:3, 3]=MD_1 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_1H[3, 0:3]=0.0
    #
    #     T0_2H=np.ones((4,4))
    #     T0_2H[0:3, 0:3]=np.matrix.transpose(R0_2)
    #     T0_2H[0:3, 3]=MD_2 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_2H[3, 0:3]=0.0
    #
    #     T0_3H=np.ones((4,4))
    #     T0_3H[0:3, 0:3]=np.matrix.transpose(R0_3)
    #     T0_3H[0:3, 3]=MD_3 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_3H[3, 0:3]=0.0
    #
    #     T0_4H=np.ones((4,4))
    #     T0_4H[0:3, 0:3]=np.matrix.transpose(R0_4)
    #     T0_4H[0:3, 3]=MD_4 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_4H[3, 0:3]=0.0
    #
    #     T0_5H=np.ones((4,4))
    #     T0_5H[0:3, 0:3]=np.matrix.transpose(R0_5)
    #     T0_5H[0:3, 3]=MD_5 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_5H[3, 0:3]=0.0
    #
    #     T0_6H=np.ones((4,4))
    #     T0_6H[0:3, 0:3]=np.matrix.transpose(R0_6)
    #     T0_6H[0:3, 3]=MD_6 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_6H[3, 0:3]=0.0
    #
    #     T0_7H=np.ones((4,4))
    #     T0_7H[0:3, 0:3]=np.matrix.transpose(R0_7)
    #     T0_7H[0:3, 3]=MD_7 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
    #     T0_7H[3, 0:3]=0.0
    #
    #
    #     t1 = self.theta[0]-0.12*math.pi/180.0
    #     t2 = self.theta[1]+130.38*math.pi/180.0
    #     t3 = self.theta[2]+45.05*math.pi/180.0
    #     t4 = self.theta[3]-30.54*math.pi/180.0
    #     t5 = self.theta[4]-0.02*math.pi/180.0
    #     t6 = self.theta[5]-38.06*math.pi/180.0
    #     t7 = self.theta[6]-0.87*math.pi/180.0
    #
    #     # t1=0.0
    #     # t2=0.0
    #     # t3=0.0
    #     # t4=0.0
    #     # t5=0.0
    #     # t6=0.0
    #     # t7=0.0
    #
    #     def findR(t):
    #         R=np.array([
    #             [np.cos(t), -np.sin(t), 0.0, 0.0],
    #             [np.sin(t), np.cos(t), 0.0, 0.0],
    #             [0.0, 0.0, 1.0, 0.0],
    #             [0.0, 0.0, 0.0, 1.0]
    #         ])
    #         return(R)
    #
    #     R1=findR(t1)
    #     R2=findR(t2)
    #     R3=findR(t3)
    #     R4=findR(t4)
    #     R5=findR(t5)
    #     R6=findR(t6)
    #     R7=findR(t7)
    #
    #
    #     T0_1=T0_1H
    #     T1_2=np.matmul(R1, (np.matmul(np.linalg.inv(T0_1H), T0_2H)))
    #     T2_3=np.matmul(R2, (np.matmul(np.linalg.inv(T0_2H), T0_3H)))
    #     T3_4=np.matmul(R3, (np.matmul(np.linalg.inv(T0_3H), T0_4H)))
    #     T4_5=np.matmul(R4, (np.matmul(np.linalg.inv(T0_4H), T0_5H)))
    #     T5_6=np.matmul(R5, (np.matmul(np.linalg.inv(T0_5H), T0_6H)))
    #     T6_7=np.matmul(R6, (np.matmul(np.linalg.inv(T0_6H), T0_7H)))
    #
    #     T0_1=T0_1H
    #     T0_2=np.matmul(T0_1, T1_2)
    #     T0_3=np.matmul(np.matmul(T0_1, T1_2), T2_3)
    #     T0_4=np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4)
    #     T0_5=np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5)
    #     T0_6=np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5), T5_6)
    #     T0_7=np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(np.matmul(T0_1,T1_2),T2_3),T3_4), T4_5), T5_6), T6_7)
    #     # new_T0_7=np.matmul(T0_7, MD_7)
    #
    #     hand_msg = Float32MultiArray()
    #     T0_7inv = np.linalg.inv(T0_7)
    #     hand_msg.data = list(T0_7inv[0:3,3])
    #     # print(hand_msg.data)
    #
    #     p0=np.zeros((1, 3))
    #     p1=T0_1[0:3, 3]
    #     p2=T0_2[0:3, 3]
    #     p3=T0_3[0:3, 3]
    #     p4=T0_4[0:3, 3]
    #     p5=T0_5[0:3, 3]
    #     p6=T0_6[0:3, 3]
    #     p7=T0_7[0:3, 3]
    #
    #     z0=np.array([0.0,  0.0, 1.0])
    #     z1=T0_1H[0:3, 2]
    #     z2=T0_2H[0:3, 2]
    #     z3=T0_3H[0:3, 2]
    #     z4=T0_4H[0:3, 2]
    #     z5=T0_5H[0:3, 2]
    #     z6=T0_6H[0:3, 2]
    #     z7=T0_7H[0:3, 2]
    #
    #     P=T0_7[0:3, 3]
    #
    #     J=np.ones((6, 7))
    #     J[0:3, 0]=np.cross(z1, P-p1)
    #     J[0:3, 1]=np.cross(z2, P-p2)
    #     J[0:3, 2]=np.cross(z3, P-p3)
    #     J[0:3, 3]=np.cross(z4, P-p4)
    #     J[0:3, 4]=np.cross(z5, P-p5)
    #     J[0:3, 5]=np.cross(z6, P-p6)
    #     J[0:3, 6]=np.cross(z7, P-p7)
    #
    #     J[3:6, 0]=z1
    #     J[3:6, 1]=z2
    #     J[3:6, 2]=z3
    #     J[3:6, 3]=z4
    #     J[3:6, 4]=z5
    #     J[3:6, 5]=z6
    #     J[3:6, 6]=z7
    #
    #     # Final position of end-effector
    #
    #     dx=self.goal[0]
    #     dy=self.goal[1]
    #     dz=self.goal[2]
    #     wx=0.0
    #     # wx=self.goal[0, 4]
    #     wy=0.0
    #     # wy=self.goal[0, 5]
    #     wz=0.0
    #     # wz=self.goal[0, 6]
    #
    #     # dx=0.0
    #     # dy=0.0
    #     # dz=0.0
    #     # wx=0.0
    #     # wy=0.0
    #     # wz=0.0
    #
    #     e=np.array([dx, dy, dz, wx, wy, wz])
    #
    #     # Find pseudo inverso of Jacobian
    #     Jinv=np.linalg.pinv(J)
    #
    #     # Change in angle from pseudo inverse
    #     angl_vel=list(np.matmul(Jinv, e))
    #     left_arm=list(np.array([0.0,0.0,0.0,0.0,0.0,0.0,0.0]))
    #     for i in range(0,len(left_arm)):
    #         angl_vel.append(left_arm[i])
    #     vel_msg = Float32MultiArray()
    #     vel_msg.data=angl_vel
    #
    #     return (vel_msg, hand_msg)
    #
    #
    #     # msg = Float32MultiArray()
    #     #
    #     # self.robot_arm_R = deltaTH
    #     #
    #     # msg.data = self.deltaTH.tolist()
    #
    #     # p = (self.goal[0:3]-self.pose[0:3])
    #     # d = self.goal[0:3]*0-self.robot_vel[0:3]
    #     #
    #     # direction = p/np.linalg.norm(p)
    #     # val = direction*np.linalg.norm(p)*self.kp+direction*d*self.kd
    #     # for i in range(0,3):
    #     #     self.robot_vel[i] = val[i]
    #     # msg = Float32MultiArray()
    #     # if np.linalg.norm(p)<0.01 and np.linalg.norm(d)<0.01:
    #     #     msg.data =(self.robot_vel*0).tolist()
    #     #     self.moving=False
    #     # else:
    #     #     msg.data = self.robot_vel.tolist()
    #     # return msg
    #


if __name__ == '__main__':
    rospy.init_node('controller', anonymous=True)
    ic = controller()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
