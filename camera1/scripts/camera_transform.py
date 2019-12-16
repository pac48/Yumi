#!/usr/bin/env python
from __future__ import print_function

import roslib
roslib.load_manifest('camera1')
import sys
import rospy
import cv2
import numpy as np
import tf
import tf2_ros
from tf import transformations
from std_msgs.msg import String, Int32MultiArray, Float32MultiArray
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from geometry_msgs.msg import TransformStamped
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
    self.transformation_matrix = np.eye(4)
    self.transformation_matrix[3,0:3]=0.0
    self.br = tf.TransformBroadcaster()


  def getTransformMsg(self):
    rotation = tf.transformations.quaternion_from_matrix(self.transformation_matrix)
    rotation/=np.sqrt(rotation[0]**2+rotation[1]**2+rotation[2]**2+rotation[3]**2)
    translation = self.transformation_matrix[0:3,3]
    time = rospy.get_rostime()
    parent = "world"
    child ="camera_depth_optical_frame" #"camera_depth_optical_frame"
    msg = TransformStamped()
    msg.header.frame_id = parent
    msg.header.stamp = time
    msg.child_frame_id = child
    msg.transform.translation.x = translation[0]
    msg.transform.translation.y = translation[1]
    msg.transform.translation.z = translation[2]
    msg.transform.rotation.x = rotation[0]
    msg.transform.rotation.y = rotation[1]
    msg.transform.rotation.z = rotation[2]
    msg.transform.rotation.w = rotation[3]
    return msg

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
    #val = np.matrix(self.camera_coords2)
    msg = self.getTransformMsg()
    self.br.sendTransformMessage(msg)
    if len(self.camera_coords)!=12:
      return
    P1_cam = np.matrix([self.camera_coords[0],self.camera_coords[1],self.camera_coords[2],1.0])
    P1_rob = np.matrix([self.robot_coords[0],self.robot_coords[1],self.robot_coords[2]])

    P2_cam = np.matrix([self.camera_coords[3],self.camera_coords[4],self.camera_coords[5],1.0])
    P2_rob = np.matrix([self.robot_coords[3],self.robot_coords[4],self.robot_coords[5]])

    P3_cam = np.matrix([self.camera_coords[6],self.camera_coords[7],self.camera_coords[8],1.0])
    P3_rob = np.matrix([self.robot_coords[6],self.robot_coords[7],self.robot_coords[8]])

    P4_cam = np.matrix([self.camera_coords[9],self.camera_coords[10],self.camera_coords[11],1.0])
    P4_rob = np.matrix([self.robot_coords[9],self.robot_coords[10],self.robot_coords[11]])

    #camera_matrix = np.array([[P1_cam[0],P1_cam[1],P1_cam[2],P1_cam[3]],[P2_cam[0],P2_cam[1],P2_cam   [2],P2_cam[3]],[P3_cam[0],P3_cam[1],P3_cam[2],P3_cam[3]],[P4_cam[0],P4_cam[1],P4_cam[2],P4_cam[3]]])
    camera_matrix = np.zeros((12,12))
    rob_vector = np.zeros((12,1))
    camera_matrix[0,0:4] = P1_cam
    camera_matrix[1,4:8] = P1_cam
    camera_matrix[2,8:12] = P1_cam
    rob_vector[0:3] = P1_rob.transpose()
    camera_matrix[3,0:4] = P2_cam
    camera_matrix[4,4:8] = P2_cam
    camera_matrix[5,8:12] = P2_cam
    rob_vector[3:6] = P2_rob.transpose()
    camera_matrix[6,0:4] = P3_cam
    camera_matrix[7,4:8] = P3_cam
    camera_matrix[8,8:12] = P3_cam
    rob_vector[6:9] = P3_rob.transpose()
    camera_matrix[9,0:4] = P4_cam
    camera_matrix[10,4:8] = P4_cam
    camera_matrix[11,8:12] = P4_cam
    rob_vector[9:12] = P4_rob.transpose()
    #rob_x = np.array([P1_rob[0],P2_rob[0],P3_rob[0],P4_rob[0]])
    T_values = np.linalg.solve(camera_matrix, rob_vector)
    T_values=T_values.transpose()
    #rob_y = np.array([P1_rob[1],P2_rob[1],P3_rob[1],P4_rob[1]])
    #second_row = np.linalg.solve(camera_matrix, rob_y)

    #rob_z = np.array([P1_rob[2],P2_rob[2],P3_rob[2],P4_rob[2]])
    #third_row = np.linalg.solve(camera_matrix, rob_z)

    #rob_offset = np.array([P1_rob[3],P2_rob[3],P3_rob[3],P4_rob[3]])
    fourth_row = np.array([0, 0, 0, 1])
    self.transformation_matrix = np.stack((T_values[0,0:4],T_values[0,4:8],T_values[0,8:12],fourth_row))
    
    print('transformation_matrix', self.transformation_matrix)
    #try:
    #  self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
    #except CvBridgeError as e:
    #  print(e)

def main(args):
  rospy.init_node('transform', anonymous=True)
  ic = image_converter()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
