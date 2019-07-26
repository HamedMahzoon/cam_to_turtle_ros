#include "ros/ros.h"
#include "std_msgs/String.h"

/*
void getCamCallback(const std_msgs::String::ConstPtr& msg) {

  ROS_INFO("I heard: [%s]", msg->data.c_str());  
}
*/

int main (int argc, char **argv) {

  ros::init(argc, argv, "cam_to_turtle_sub_pub");
  ros::NodeHandle nh;

  ros::Publisher pub_to_turtle = nh.advertise<std_msgs::String>("signal_from_somebody",1000);
  //ros::Subscriber sub_from_cam = nh.subscribe("signal_from_key", 1000, getCamCallback);

  ros::Rate loop_rate(10);

  int count =0;
  while(ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    pub_to_turtle.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    count++;    
  }
  return 0;
}
