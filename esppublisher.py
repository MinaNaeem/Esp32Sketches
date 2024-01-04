#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

def publisher():
    # Initialize the ROS node with a unique name
    rospy.init_node('string_publisher', anonymous=True)

    # Create a publisher object
    pub = rospy.Publisher('cmd_vel', Int32, queue_size=10)

    # Set the publishing rate (in Hz)
    rate = rospy.Rate(2)  


    while not rospy.is_shutdown():
        message = int(input("please insert a number 1 for forward, 0 for stop, -1 for reverse:   "))
        # Publish the message
        rospy.loginfo(message)
        pub.publish(message)
    
        # Wait according to the publishing rate
        rate.sleep()

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass
