#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

geometry_msgs::PoseStamped pose;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_point");
    ros::NodeHandle nh;

    // ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("/firefly/command/pose", 10);

    // ros::Subscriber position_sub = nh.subscribe<nav_msgs::Odometry>("/firefly/ground_truth/odometry", 1000, position_cb);

    // the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    while (ros::ok())
    {

        pose.pose.position.x = 0;
        pose.pose.position.y = 0;
        pose.pose.position.z = 3;

        local_pos_pub.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}