#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

def publisher():
    # Initialize the ROS node with a unique name
    rospy.init_node('string_publisher', anonymous=True)

    # Create a publisher object
    pub = rospy.Publisher('cmd_angle', Int32, queue_size=10)

    # Set the publishing rate (in Hz)
    rate = rospy.Rate(2)  

    
    while not rospy.is_shutdown():
        # Publish the message
        
        for message in range(0,180,10):
            rospy.loginfo(message)
            pub.publish(message)
            
            # Wait according to the publishing rate
            rate.sleep()
        for message in range(180,0, -10):
            rospy.loginfo(message)
            pub.publish(message)
            
            # Wait according to the publishing rate
            rate.sleep()
if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass
