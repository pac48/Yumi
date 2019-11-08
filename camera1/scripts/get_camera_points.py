#!/usr/bin/env python
from __future__ import print_function

import roslib
roslib.load_manifest('camera1')
import sys
import rospy
import cv2
import time
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
np.set_printoptions(threshold=sys.maxsize)

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)
    self.pub = rospy.Publisher('camera_calibration_points', Float32MultiArray, queue_size=5)
    self.pub = rospy.Publisher('robot_calibration_points', Float32MultiArray, queue_size=5)
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/camera/depth/image_rect_raw",Image,self.callback_image)
    self.operational_sub = rospy.Subscriber("/operational_position_R",Float32MultiArray,self.callback_robot)
    self.camera_transform_sub = rospy.Subscriber("camera_coords",Int32MultiArray,self.callback_camera_coords)
    self.pixpos = [0,0]
    self.P1_all_points = []
    self.P2_all_points = []
    self.P3_all_points = []
    self.P4_all_points = []
    self.camera_coords = [0,0,0,0]
    self.robot_coords = [0,0,0,0]
    self.calibrated = 0
#  def callback_pixpos(self,data):
#    self.pixpos = data.data
  def callback_robot(self, data):
    self.robot_coords = data.data

  def callback_camera_coords(self, data):
    self.camera_coords = data.data

  def callback_image(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "16UC1")
      
    except CvBridgeError as e:
      print(e)
    if(self.calibrated == 0):
#### get position for first camera calibration point ####
      for j in range(0,10):
        P_cam = np.array([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2]])
        self.P1_all_points.append(P_cam)   
        print(self.P1_all_points)
        print(len(self.P1_all_points))

      if len(self.P1_all_points) == 10:
        p1_x_sum = 0
        p1_y_sum = 0
        p1_z_sum = 0
        for i in range(0,10):
          p1_x_sum =  p1_x_sum + self.P1_all_points[i][0]
          p1_y_sum =  p1_y_sum + self.P1_all_points[i][1]
          p1_z_sum =  p1_z_sum + self.P1_all_points[i][2]
        p1_x_average = p1_x_sum/10
        p1_y_average = p1_y_sum/10
        p1_z_average = p1_z_sum/10
        p1_pos = [p1_x_average,p1_y_average,p1_z_average]
        print('p1_pos', p1_pos)
      print('REPOSITION CAMERA')

      time.sleep(5)

#### get position for second camera calibration point ####

      for j in range(0,10):
        P_cam = np.array([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2]])
        self.P2_all_points.append(P_cam)   
        print(self.P2_all_points)
        print(len(self.P2_all_points))

      if len(self.P2_all_points) == 10:
        p2_x_sum = 0
        p2_y_sum = 0
        p2_z_sum = 0
        for i in range(0,10):
          p2_x_sum =  p2_x_sum + self.P2_all_points[i][0]
          p2_y_sum =  p2_y_sum + self.P2_all_points[i][1]
          p2_z_sum =  p2_z_sum + self.P2_all_points[i][2]
        p2_x_average = p2_x_sum/10
        p2_y_average = p2_y_sum/10
        p2_z_average = p2_z_sum/10
        p2_pos = [p2_x_average,p2_y_average,p2_z_average]
        print('p2_pos', p2_pos)
      print('REPOSITION CAMERA')

      time.sleep(5)

#### get position for third camera calibration point ####

      for j in range(0,10):
        P_cam = np.array([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2]])
        self.P3_all_points.append(P_cam)   
        print(self.P3_all_points)
        print(len(self.P3_all_points))

      if len(self.P3_all_points) == 10:
        p3_x_sum = 0
        p3_y_sum = 0
        p3_z_sum = 0
        for i in range(0,10):
          p3_x_sum =  p3_x_sum + self.P3_all_points[i][0]
          p3_y_sum =  p3_y_sum + self.P3_all_points[i][1]
          p3_z_sum =  p3_z_sum + self.P3_all_points[i][2]
        p3_x_average = p3_x_sum/10
        p3_y_average = p3_y_sum/10
        p3_z_average = p3_z_sum/10
        p3_pos = [p3_x_average,p3_y_average,p3_z_average]
        print('p3_pos', p3_pos)
      print('REPOSITION CAMERA')

      time.sleep(5)

#### get position for fourth camera calibration point ####

      for j in range(0,10):
        P_cam = np.array([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2]])
        self.P4_all_points.append(P_cam)   
        print(self.P4_all_points)
        print(len(self.P4_all_points))

      if len(self.P4_all_points) == 10:
        p4_x_sum = 0
        p4_y_sum = 0
        p4_z_sum = 0
        for i in range(0,10):
          p4_x_sum =  p4_x_sum + self.P4_all_points[i][0]
          p4_y_sum =  p4_y_sum + self.P4_all_points[i][1]
          p4_z_sum =  p4_z_sum + self.P3_all_points[i][2]
        p4_x_average = p4_x_sum/10
        p4_y_average = p4_y_sum/10
        p4_z_average = p4_z_sum/10
        p4_pos = [p4_x_average,p4_y_average,p4_z_average]
        print('p4_pos', p4_pos)
        
        
        self.calibrated = 1;
      #camera_positions = np.array([p1_pos,p2_pos,p3_pos,p4_pos])
      camera_positions = np.array([p1_x_average,p1_y_average,p1_z_average,p2_x_average,p2_y_average,p2_z_average,p3_x_average,p3_y_average,p3_z_average,p4_x_average,p4_y_average,p4_z_average])
      print(camera_positions)
      msg = Float32MultiArray()
      msg.data = camera_positions
      self.pub.publish(msg)
    else:
      print('Camera Points Obtained')
      #self.pub.publish(msg)
    try:
      self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
    except CvBridgeError as e:
      print(e)

def main(args):

  ic = image_converter()
  rospy.init_node('image_converter', anonymous=True)
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
