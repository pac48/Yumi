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
import matplotlib.pyplot as plt
np.set_printoptions(threshold=sys.maxsize)

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)
    self.bridge = CvBridge()
    self.pub = rospy.Publisher('camera_coords', Float32MultiArray, queue_size=5)
    self.image_sub = rospy.Subscriber("/camera/aligned_depth_to_color/image_raw",Image,self.callback_image)
    self.pixpos_sub = rospy.Subscriber("pixpos",Int32MultiArray,self.callback_pixpos)
    self.pixpos = [0,0]
    self.x_vec = []

  def callback_pixpos(self,data):
    self.pixpos = data.data

  def callback_image(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "16UC1")

    except CvBridgeError as e:
      print(e)

    #print('cv',cv_image)
    cv_image_array = np.array(cv_image)
    #cv2.imshow("Depth Image window", cv_image_array)
    a = np.size(cv_image_array)
    #print(cv_image_array[self.pixpos[1],self.pixpos[0]])
    print('picpos',self.pixpos)
    depth = cv_image_array[self.pixpos[1],self.pixpos[0]]
    #print('size', np.shape(cv_image_array))
    print('depth',depth)
    AR_x = 85.2/640
    AR_y = 58.0/480
    #AR_x = 91.2/480
    #AR_y = 65.5/640
    a_x = (self.pixpos[0]-640/2)*AR_x
    a_x = a_x*(np.pi/180)
    x_pos = depth*np.sin(a_x)


    z_pos = depth*np.cos(a_x)

    a_y = (self.pixpos[1]-480/2)*AR_y
    a_y = a_y*(np.pi/180)
    y_pos = depth*np.sin(a_y)
    camera_coords = [x_pos,y_pos,z_pos]
    msg = Float32MultiArray()
    msg.data = camera_coords
    self.pub.publish(msg)
    print('x_pos, y_pos, z_pos')
    print(x_pos, y_pos, z_pos)
    cv2.waitKey(3)
    #self.x_vec.append(y_pos)
    x_axis = np.linspace(0,1,len(self.x_vec))
    #plt.plot(x_axis,self.x_vec)
    #plt.show()

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