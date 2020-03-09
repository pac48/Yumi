#!/usr/bin/env python
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
import tf
import tf2_ros
from tf import transformations
from geometry_msgs.msg import TransformStamped
np.set_printoptions(threshold=sys.maxsize)

class image_converter:

  def __init__(self):
    self.camera_coords_sub = rospy.Subscriber("/camera_coords",Float32MultiArray,self.callback_pos_vel)
    self.camera_coords_sub = rospy.Subscriber("/transfrom",Float32MultiArray,self.callback_transform) 
    self.pub_position = rospy.Publisher('/ball_position', Float32MultiArray, queue_size=5)
    self.pub_velocity = rospy.Publisher('/ball_velocity', Float32MultiArray, queue_size=5)
    self.camera_coords2 = [0,0,0]
    self.transform = np.zeros((4,4))
    self.position = [0,0,0]
    self.previous_time = 0.0
    self.previous_position = [0,0,0]
    #self.br = tf.TransformBroadcaster()

#  def getTransformMsg(self,vec):
#    #rotation = tf.transformations.quaternion_from_matrix(self.transform)
#    #rotation/=np.sqrt(rotation[0]**2+rotation[1]**2+rotation[2]**2+rotation[3]**2)
#    #translation = self.transform[0:3,3]
#    time = rospy.get_rostime()
#    #parent = "camera_depth_optical_frame"
#    #child ="world" #"camera_depth_optical_frame"
#    child = "camera_depth_optical_frame"
#    parent ="world" #"camera_depth_optical_frame"
#    msg = TransformStamped()
#    msg.header.frame_id = parent
#    msg.header.stamp = time
#    msg.child_frame_id = child
#    msg.transform.translation.x = vec[4]
#    msg.transform.translation.y = vec[5]
#    msg.transform.translation.z = vec[6]
#    msg.transform.rotation.x = vec[1]
#    msg.transform.rotation.y = vec[2]
#    #wards toward the top of the device Positive Z direction is inward
#    msg.transform.rotation.z = vec[3]
#    msg.transform.rotation.w = vec[0]
#    return msg

  def callback_transform(self, msg):
    data = msg.data
    self.transform = np.matrix(np.stack((data[0:4],data[4:8],data[8:12],data[12:16])) )
    #msgT = self.getTransformMsg(data)
    #self.br.sendTransformMessage(msgT)
    #self.transform = data.data


  def callback_pos_vel(self, msg):
      
      #---- position -----
      data = list(msg.data)
      data.append(1.0)
      self.camera_coords2 = np.array(data)
      position = np.matmul(np.linalg.inv(self.transform), self.camera_coords2)
      position = np.matmul(self.transform, self.camera_coords2)
      position = position[0:3]
      # pub position
      msg = Float32MultiArray()
      msg.data = position
      self.pub_position.publish(msg)
      #print('position: ',position)
      
      #---- velocity -------
      current_time = rospy.get_time()
      velocity = (position - self.previous_position)/(current_time - self.previous_time)
      #pub velocity
      msg2 = Float32MultiArray()
      msg2.data = velocity
      self.pub_velocity.publish(msg2)      
      #print('current_time', current_time)


def main(args):
  rospy.init_node('pos_vel_pub', anonymous=True)
  ic = image_converter()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
