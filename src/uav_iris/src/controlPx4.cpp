#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

geometry_msgs::PoseStamped pose;

// void mpc_control_out_cb(const nav_msgs::RollPitchYawrateThrust::ConstPtr &mpc_control_out)
// {
// }

int main(int argc, char **argv)
{
    ros::init(argc, argv, "controlPx4");
    ros::NodeHandle nh;

    // ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("/firefly/command/pose", 10);

    //  ros::Subscriber mpc_control_out = nh.subscribe<nav_msgs::RollPitchYawrateThrust>("/firefly/command/roll_pitch_yawrate_thrust", 1000, mpc_control_out_cb);

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