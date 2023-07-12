#include <ros/ros.h>
#include <mavros/mavros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <mav_msgs/RollPitchYawrateThrust.h>
#include <tf/transform_datatypes.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>

mavros_msgs::State current_state;
geometry_msgs::PoseStamped current_pose;
geometry_msgs::TwistStamped current_twist;
mavros_msgs::AttitudeTarget attitude_target;

void control_cb(const mav_msgs::RollPitchYawrateThrust::ConstPtr &control_mpc)
{
    attitude_target.header.stamp = ros::Time::now();
    attitude_target.header.frame_id = "base_footprint";
    attitude_target.type_mask = mavros_msgs::AttitudeTarget::IGNORE_ROLL_RATE | mavros_msgs::AttitudeTarget::IGNORE_PITCH_RATE;
    attitude_target.orientation = tf::createQuaternionMsgFromRollPitchYaw(control_mpc->roll, control_mpc->pitch, 0.0);
    attitude_target.body_rate.z = control_mpc->yaw_rate;
    attitude_target.thrust = control_mpc->thrust.z;
}

int main(int argc, char **argv)
{
    // 初始化 ROS 节点
    ros::init(argc, argv, "controlPx4");
    ros::NodeHandle nh;

    // 创建一个发布者用于发送姿态控制指令
    ros::Publisher attitude_target_pub = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude", 10);

    // 创建一个订阅者用于接收MPC姿态控制指令
    ros::Subscriber control_sub = nh.subscribe<mav_msgs::RollPitchYawrateThrust>("firefly/command/roll_pitch_yawrate_thrust", 10, control_cb);

    // 循环发送姿态控制指令
    ros::Rate rate(50.0);
    while (ros::ok())
    {

        attitude_target_pub.publish(attitude_target);
        rate.sleep();
    }

    return 0;
}