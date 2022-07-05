#include <ros/ros.h>
#include <math.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>  
#include <nav_msgs/Odometry.h>

#include "std_msgs/String.h"
 
#include <sstream>


class Pub_sub_odometry {

private:
    ros::NodeHandle n;
    ros::Subscriber odom_sub; 
    
   
    tf2_ros::TransformBroadcaster odom_broadcaster; 



public:
       
    Pub_sub_odometry() {
       odom_sub=n.subscribe("/odom", 1, &Pub_sub_odometry::computeOdom, this); 
        
    }
    

    

    void computeOdom(const  nav_msgs::Odometry::ConstPtr& msg){
      
        double x, y, z;
        ros::Time currentTime;
        geometry_msgs::Quaternion quat_msg;

        currentTime = msg->header.stamp;
        
         
        //set pose
        x = msg->pose.pose.position.x;
        y = msg->pose.pose.position.y;
        z = msg->pose.pose.position.z;
        quat_msg = msg->pose.pose.orientation;
        
        publishTfTransformation(x, y, z, currentTime , quat_msg );  

    }

   
    // tf2
    void publishTfTransformation(double x, double y, double z,ros::Time currentTime , geometry_msgs::Quaternion quat_msg ){
        geometry_msgs::TransformStamped odometryTransformation;
       


        //PUBLISHING:

        //set header
        odometryTransformation.header.stamp = currentTime;
        odometryTransformation.header.frame_id = "odom";
        odometryTransformation.child_frame_id = "base_link";
        //set transformation
        odometryTransformation.transform.translation.x = x;
        odometryTransformation.transform.translation.y = y;
        odometryTransformation.transform.translation.z = z;
        odometryTransformation.transform.rotation =quat_msg;

        //publish transformation
        odom_broadcaster.sendTransform(odometryTransformation);
    }

    
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "ComputeOdometry");

    Pub_sub_odometry pubSubOdometry;


    ros::spin();
    return 0;
}