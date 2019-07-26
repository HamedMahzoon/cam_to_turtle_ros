#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

import sys
import socket
from socket import error as socket_error

host = "192.168.1.127"
port = 8079

def  listen_command():

    rospy.init_node('listen_command', anonymous=True)

    pub = rospy.Publisher('vel_kame1', Twist, queue_size=10)
    twist_msg = Twist()
    
    twist_msg.linear.x = -1
    twist_msg.linear.y = 0
    twist_msg.linear.z = 0
    twist_msg.angular.x = 0
    twist_msg.angular.y = 0
    twist_msg.angular.z = 0

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((host, port))
    except socket_error as serr:
        print("Connection:"+str(host)+":"+str(port)+" refused.")
        sys.exit()

    #rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        input_text = raw_input('>>')

        if(input_text == 'kill'):
            client.close()
            print('KILL SYSTEM')
            sys.exit()
        else:
            print("SEND To: "+host+" command: "+str(input_text))
            client.send(str(input_text).encode('utf-8'))
            rospy.loginfo(twist_msg)
            for x in range(100) :
                pub.publish(twist_msg)
        #rate.sleep()

if __name__ == '__main__':
    try:
        listen_command()
    except rospy.ROSInterruptException:
        pass
