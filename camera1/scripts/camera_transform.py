#!/usr/bin/env python
from __future__ import print_function

import roslib
roslib.load_manifest('camera1')
import sys
import rospy
import cv2
import numpy as np
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
np.set_printoptions(threshold=sys.maxsize)

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/camera/depth/image_rect_raw",Image,self.callback_image)
    self.operational_sub = rospy.Subscriber("robot_calibration_points",Float32MultiArray,self.callback_robot_coords)
    self.camera_transform_sub = rospy.Subscriber("camera_calibration_points",Float32MultiArray,self.callback_camera_coords)
    self.camera_coords_sub = rospy.Subscriber("/camera_coords",Float32MultiArray,self.callback_camera_coords2)
    self.camera_coords2 = [0,0,0,1]
    self.pixpos = [0,0]
    self.x_vec = []
    self.camera_coords = [0,0,0,0]
    self.robot_coords = [0,0,0,0]
    self.transformation_matrix = np.zeros((4,4))

  #  def callback_pixpos(self,data):
#    self.pixpos = data.data
  def callback_camera_coords2(self, msg):
      self.camera_coords2 = list(msg.data)
      self.camera_coords2.append(1.0)

  def callback_robot_coords(self, data):
    self.robot_coords = data.data
  def callback_camera_coords(self, data):
    self.camera_coords = data.data

  def callback_image(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "16UC1")
      
    except CvBridgeError as e:
      print(e)
    #print('camera coords', self.camera_coords)
    val = np.matrix(self.camera_coords2)
    print(self.transformation_matrix*val.transpose())
    if len(self.camera_coords)!=12:
      return
    P1_cam = np.array([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2],1])
    P1_rob = np.array([self.robot_coords[0],self.robot_coords[1],self.robot_coords[2],1])

    P2_cam = np.array([self.camera_coords[3],self.camera_coords[4],self.camera_coords[5],1])
    P2_rob = np.array([self.robot_coords[3],self.robot_coords[4],self.robot_coords[5],1])

    P3_cam = np.array([self.camera_coords[6],self.camera_coords[7],self.camera_coords[8],1])
    P3_rob = np.array([self.robot_coords[6],self.robot_coords[7],self.robot_coords[8],1])

    P4_cam = np.array([self.camera_coords[9],self.camera_coords[10],self.camera_coords[11],1])
    P4_rob = np.array([self.robot_coords[9],self.robot_coords[10],self.robot_coords[11],1])

    camera_matrix = np.array([[P1_cam[0],P1_cam[1],P1_cam[2],P1_cam[3]],[P2_cam[0],P2_cam[1],P2_cam   [2],P2_cam[3]],[P3_cam[0],P3_cam[1],P3_cam[2],P3_cam[3]],[P4_cam[0],P4_cam[1],P4_cam[2],P4_cam[3]]])

    rob_x = np.array([P1_rob[0],P2_rob[0],P3_rob[0],P4_rob[0]])
    top_row = np.linalg.solve(camera_matrix, rob_x)

    rob_y = np.array([P1_rob[1],P2_rob[1],P3_rob[1],P4_rob[1]])
    second_row = np.linalg.solve(camera_matrix, rob_y)

    rob_z = np.array([P1_rob[2],P2_rob[2],P3_rob[2],P4_rob[2]])
    third_row = np.linalg.solve(camera_matrix, rob_z)

    rob_offset = np.array([P1_rob[3],P2_rob[3],P3_rob[3],P4_rob[3]])
    fourth_row = np.linalg.solve(camera_matrix, rob_offset)

    self.transformation_matrix = np.stack((top_row,second_row,third_row,fourth_row))
    
    print('transformation_matrix', self.transformation_matrix)

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
