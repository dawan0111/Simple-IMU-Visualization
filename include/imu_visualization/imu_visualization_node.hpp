#ifndef IMU_VISUALIZATION_NODE_HPP_
#define IMU_VISUALIZATION_NODE_HPP_
#include "imu_visualization/imu_util.hpp"
#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
class ImuVisualizationNode : public rclcpp::Node {
public:
  ImuVisualizationNode(const rclcpp::NodeOptions &options);
  void imuCallback(const sensor_msgs::msg::Imu::ConstSharedPtr msg);

private:
  void tfTransformTimerCallback();

private:
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
  tf2::Quaternion angular_q_;
  tf2::Quaternion imu_q_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr tf_transform_timer_;
  rclcpp::TimerBase::SharedPtr timer_;
};

#endif