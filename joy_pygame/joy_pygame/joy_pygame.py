#!/usr/bin/env python

import sys
import rospy
from sensor_msgs.msg import Joy
import pygame as pg


class JoyStick:

  def __init__(self):
    self.msg = Joy()
    pg.init()
    if int(pg.joystick.get_count()) == 0:
      pg.quit()
      sys.exit('No joystick detected')
    elif pg.joystick.get_count() > 1:
      pg.quit()
      sys.exit('More than 1 joystick detected')
    self.joystick = pg.joystick.Joystick(0)
    self.joystick.init()
    self.msg.header.seq = 0
    self.msg.header.stamp = rospy.get_rostime()
    self.msg.buttons = [self.joystick.get_button(x) for x in range(self.joystick.get_numbuttons())]
    self.msg.axes = [self.joystick.get_axis(x) for x in range(self.joystick.get_numaxes()) ]


  def get_msg(self, timeout):
    self.msg.header.seq = self.msg.header.seq + 1
    self.msg.header.stamp = rospy.get_rostime()
    event = pg.event.wait(timeout)
    # if event.type is pg.NOEVENT:
    #   self.msg.buttons = [self.joystick.get_button(x) for x in range(self.joystick.get_numbuttons())]
    #   self.msg.axes = [self.joystick.get_axis(x) for x in range(self.joystick.get_numaxes()) ]
    # else:
    self.msg.buttons = [self.joystick.get_button(x) for x in range(self.joystick.get_numbuttons())]
    self.msg.axes = [-int(100*self.joystick.get_axis(x))/100 for x in range(self.joystick.get_numaxes()) ]

    return self.msg


if __name__ == '__main__':
  rospy.init_node('joy_node', anonymous=True)
  joystick = JoyStick()
  joy_pub = rospy.Publisher("/joy", Joy, queue_size=10)
  if rospy.has_param('autorepeat_rate'):
    val = rospy.get_param('autorepeat_rate')
  else:
    val = 25
  rate = rospy.Rate(val) # 10hz
  while not rospy.is_shutdown():
    msg = joystick.get_msg(val)
    joy_pub.publish(msg)
    rate.sleep()
    # print(msg.axes)

  pg.quit()