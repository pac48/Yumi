#!/usr/bin/env python
from __future__ import print_function

import roslib
roslib.load_manifest('camera1')
import sys
import rospy
import cv2
import numpy as np
from std_msgs.msg import String,Int32,Int32MultiArray,MultiArrayLayout,MultiArrayDimension
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)
    self.pub = rospy.Publisher('pixpos', Int32MultiArray, queue_size=1)
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/camera/color/image_raw",Image,self.callback)

  def callback(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
      cv2.imshow("Image window r", cv_image)
    except CvBridgeError as e:
      print(e)

    (rows,cols,channels) = cv_image.shape
    print(channels)
    
    if cols > 60 and rows > 60 :
      cv2.circle(cv_image, (50,50), 10, 255)
    cv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2RGB)
    cv_image = cv2.cvtColor(cv_image, cv2.COLOR_RGB2HSV)
    dark_green_bgr = np.uint8([[[100,10,10 ]]])
    dark_green = cv2.cvtColor(dark_green_bgr, cv2.COLOR_BGR2HSV)
    dark_green = (100,0,0) 
    #dark_green = (90,255,255)
    #light_green_bgr = np.uint8([[[255,0,0 ]]])
    #light_green = cv2.cvtColor(light_green_bgr, cv2.COLOR_BGR2HSV)
    light_green = (300,255,255)
    lower_red = np.array([100,150,10]) 
    upper_red = np.array([180,255,200])
    mask = cv2.inRange(cv_image,lower_red, upper_red)
    #cv_image[mask == 1] = ([75,255,225])
    #cv_image[mask == 0] = ([0,0,0])
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_HSV2BGR)
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
    result = cv2.bitwise_and(cv_image, cv_image, mask=mask)
    result = cv2.cvtColor(result, cv2.COLOR_HSV2BGR)
    cv_image = cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)
    #green_low = np.array([40 , 100, 50])
    #green_high = np.array([80, 255, 255])
    #curr_mask = cv2.inRange(cv_image, green_low, green_high)
    #cv_image[curr_mask >0] = ([75,255,225])
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_HSV2BGR)
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
    #threshVal = 90
    ret,thresh = cv2.threshold(cv_image, 0, 255, 0)
    #cv_image = cv2.cvtColor(thresh, cv2.COLOR_GRAY2BGR) 
    cv_image, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE) 
    #print('contours',len(contours))
    c = max(contours, key = cv2.contourArea)
    M = cv2.moments(c)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    pix_coord = [cX,cY]
    msg = Int32MultiArray()
    msg.data = pix_coord
    self.pub.publish(msg)
    cv2.circle(cv_image, (cX,cY), 7, (0,0,0),-1)
    cv2.putText(cv_image, "center", (cX -20, cY - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,0), 2)
    #print('cX', cX)
    #print('cY', cY)
    print(pix_coord)
    cv2.drawContours(cv_image, [c], 0, (80,0,0), 3) 
    #depth_frame = data.frame()
    #x,y,w,h = cv2.boundingRect(c)
    #cv2.rectangle(cv_image,(x,y),(x+w,y+h),(0,255,0),2)
    #print('contours', contours)
    #cv_image = cv2.cvtColor(cv_image, cv2.COLOR_GRAY2BGR)
    #cnt = contours[4]
    #cv2.drawContours(cv_image, [cnt], -1, (0,225,0), 3)
    #print(contours)
    cv2.imshow("Image window", cv_image)
    cv2.waitKey(3)

    try:
      self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "mono8"))
    except CvBridgeError as e:
      print(e)

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