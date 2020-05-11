#!/usr/bin/env python

# This file allows for camera callibration to begin
# the user uses the record_points subscriber to begin collection of transfromation points
# the user than moves YuMi's hand and the program collects points as the hand is moved

from __future__ import print_function

import roslib
roslib.load_manifest('camera1')
import sys
import rospy
import cv2
import time
import numpy as np
from std_msgs.msg import Float32MultiArray,Bool
from cv_bridge import CvBridge, CvBridgeError
np.set_printoptions(threshold=sys.maxsize)

class image_converter:

  def __init__(self):
    self.pub_camera = rospy.Publisher('/camera_calibration_points', Float32MultiArray, queue_size=5)
    self.pub_robot = rospy.Publisher('/robot_calibration_points', Float32MultiArray, queue_size=5)
    self.record_points = rospy.Subscriber('record_points',Bool , self.handle_request,buff_size=1)
    self.bridge = CvBridge()
    self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_robot)
    self.camera_transform_sub = rospy.Subscriber("/camera_coords",Float32MultiArray,self.callback_camera_coords)
    self.pixpos = [0,0]
    self.P1_all_points = []
    self.P2_all_points = []
    self.P3_all_points = []
    self.P4_all_points = []
    self.P1_robot = []
    self.P2_robot = []
    self.P3_robot = []
    self.P4_robot = []
    self.camera_coords = [0,0,0,0]
    self.robot_coords = [0,0,0,0]
    self.calibrated = 0
    self.recording_camera=False
#  def callback_pixpos(self,data):
#    self.pixpos = data.data

  def handle_request(self,msg):
    if msg.data==True:
      self.recording_camera=True

  def callback_robot(self, data):
    self.robot_coords = data.data[0:3]

  def callback_camera_coords(self, msg):
    if len(msg.data)!=3 or self.recording_camera==False:
      return

    if len(self.P1_all_points)<10:
      self.P1_all_points.append(list(msg.data))
      if len(self.P1_all_points)==10:
        self.recording_camera=False
        self.P1_robot=self.robot_coords
      return
    if len(self.P2_all_points)<10:
      self.P2_all_points.append(list(msg.data))
      if len(self.P2_all_points)==10:
        self.recording_camera=False
        self.P2_robot=self.robot_coords
      return
    if len(self.P3_all_points)<10:
      self.P3_all_points.append(list(msg.data))
      if len(self.P3_all_points)==10:
        self.recording_camera=False
        self.P3_robot=self.robot_coords
      return
    if len(self.P4_all_points)<10:
      self.P4_all_points.append(list(msg.data))
      self.P4_robot=self.robot_coords
      return
    if len(self.P1_all_points)==10 and len(self.P2_all_points)==10 and len(self.P3_all_points)==10 and len(self.P4_all_points)==10:
      P1_average = np.mean(np.array(self.P1_all_points),0)
      P2_average = np.mean(np.array(self.P2_all_points),0)
      P3_average = np.mean(np.array(self.P3_all_points),0)
      P4_average = np.mean(np.array(self.P4_all_points),0)
      msg = Float32MultiArray()
      list_of_lists = [P1_average,P2_average,P3_average,P4_average]
      msg.data=[float(y) for x in list_of_lists for y in x]
      self.pub_camera.publish(msg)
      list_of_lists = [self.P1_robot,self.P2_robot,self.P3_robot,self.P4_robot]
      msg.data=[float(y) for x in list_of_lists for y in x]
      self.pub_robot.publish(msg)
      self.P1_all_points=[]
      self.P2_all_points=[]
      self.P3_all_points=[]
      self.P4_all_points=[]
      self.recording_camera=False
      return

def main(args):
  rospy.init_node('image_converter', anonymous=True)
  ic = image_converter()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
