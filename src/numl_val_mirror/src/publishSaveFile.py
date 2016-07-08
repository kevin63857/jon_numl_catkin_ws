#!/usr/bin/env python

import rospy
import ihmc_msgs
from ihmc_msgs.msg import *
from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Vector3
import tf
import math
import time
from time import sleep
import sys

def arm(arr):
    msg = ArmTrajectoryRosMessage( joint_trajectory_messages = [
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[3]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[4]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[5]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[6]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[7]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[8]), velocity = 0.5)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[9]), velocity = 0.5)])
        ], execution_mode = 0, unique_id = 14, robot_side=int(arr[2]))
    pub[0].publish(msg)
def neck(arr):
    msg = NeckTrajectoryRosMessage( joint_trajectory_messages = [
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[2]), velocity = 0.3)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[3]), velocity = 0.4)]),
        OneDoFJointTrajectoryRosMessage(trajectory_points = [ TrajectoryPoint1DRosMessage(time= float(arr[1]), position = float(arr[4]), velocity = 0.5)]),
        ], unique_id = 14) #rospy.Time.now().secs)
    pub[1].publish(msg)

def pelvis(arr):
    msg = PelvisHeightTrajectoryRosMessage(trajectory_points = [
        TrajectoryPoint1DRosMessage( position = float(arr[2]), velocity = 0.5, time = float(arr[1])  )]
        , unique_id = 13) #rospy.Time.now().secs)
    pub[2].publish(msg)

def chest(arr):
    tfq = tf.transformations.quaternion_from_euler(float(arr[2]),float(arr[3]),float(arr[4]))
    q = Quaternion(tfq[0], tfq[1], tfq[2], tfq[3])
    msg = ChestTrajectoryRosMessage(taskspace_trajectory_points = [
        SO3TrajectoryPointRosMessage( orientation= q, angular_velocity = Vector3(0.3,0.3,0.3), time = float(arr[1])  )]
        , execution_mode = 0, unique_id = 13) #rospy.Time.now().secs)
    pub[3].publish(msg)

def home(arr):
    print "yeah, this isn't implemented yet....\n"

def sleep(arr):
    sleep(1000/arr[1])

if __name__ == '__main__':
    reader= open(sys.argv[1], "r")
    rospy.init_node ("saveFilePublisher")
    pubs = [rospy.Publisher("/ihmc_ros/valkyrie/control/arm_trajectory", ArmTrajectoryRosMessage, queue_size = 100),
            rospy.Publisher("/ihmc_ros/valkyrie/control/neck_trajectory", NeckTrajectoryRosMessage, queue_size = 100),
            rospy.Publisher("/ihmc_ros/valkyrie/control/pelvis_height_trajectory", PelvisHeightTrajectoryRosMessage, queue_size = 100),
            rospy.Publisher("/ihmc_ros/valkyrie/control/chest_trajectory", ChestTrajectoryRosMessage, queue_size = 100),
            rospy.Publisher("/ihmc_ros/valkyrie/control/go_home", GoHomeRosMessage, queue_size = 100)]
    options = {
            * : sleep,
            1 : arm,
            2 : neck,
            3 : pelvis,
            4 : chest,
            5 : home}
    text=reader.readLine()
    while(len(string)!=0)
        arr=text.split(" ");
        options[arr[0][0]](arr)
        text=reader.readLine()
