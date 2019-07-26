#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "opencv_apps/FaceArrayStamped.h"

#include <sstream>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    //pub_ = n_.advertise<std_msgs::String>("vel_turtle",1000);
    pub_ = n_.advertise<geometry_msgs::Twist>("vel_turtle",1000);    
    //pub_  = n_.advertise<PUBLISHED_MESSAGE_TYPE>("/published_topic", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("signal_from_somebody", 1000, &SubscribeAndPublish::getCamCallback, this);
    //sub_ = n_.subscribe("/subscribed_topic", 1, &SubscribeAndPublish::callback, this);
    sub_cv = n_.subscribe("face_detection/faces", 1000, &SubscribeAndPublish::getCamCallback_cv, this);
    
    twistMsg.linear.x = 0; twistMsg.linear.y = 0; twistMsg.linear.z = 0;
    twistMsg.angular.x = 0; twistMsg.angular.y = 0; twistMsg.angular.z = 0;
  }

  void getCamCallback (const std_msgs::String::ConstPtr& msg)
  {
    //msg->data.c_str();
    ROS_INFO("I heard: [%s]", msg->data.c_str());  
    //PUBLISHED_MESSAGE_TYPE output;
    //.... do something with the input and generate the output...

    twistMsg.linear.x = 0;
    twistMsg.angular.z = 1;
    //pub_.publish(msg);1
    pub_.publish(twistMsg);
  }

  void getCamCallback_cv (const opencv_apps::FaceArrayStamped::ConstPtr& msg)
  {
    //msg->data.c_str();
    if(msg->faces.size() > 0) {
      ROS_INFO("I heard: [%s]", msg->header.frame_id.c_str());  
      //PUBLISHED_MESSAGE_TYPE output;
      //.... do something with the input and generate the output...

      twistMsg.linear.x = 1;
      twistMsg.angular.z = 1;
      //pub_.publish(msg);1
      pub_.publish(twistMsg);
    }
  }

  
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_, sub_cv;
  geometry_msgs::Twist twistMsg;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}


