#ifndef IMU_VISUALIZATION_NODE
#define IMU_VISUALIZATION_NODE
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
class ImuVisualizationNode : public rclcpp::Node {
public:
  ImuVisualizationNode(const rclcpp::NodeOptions &options);
  void imuCallback(const sensor_msgs::msg::Imu::ConstSharedPtr msg);

private:
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
};

#endif