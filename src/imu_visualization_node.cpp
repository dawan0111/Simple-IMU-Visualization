#include "imu_visualization/imu_visualization_node.hpp"

ImuVisualizationNode::ImuVisualizationNode(const rclcpp::NodeOptions &options)
    : Node(options.arguments()[0], options) {
  RCLCPP_INFO(this->get_logger(), "%s constructor",
              options.arguments()[0].c_str());

  imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "imu", rclcpp::QoS(1),
      std::bind(&ImuVisualizationNode::imuCallback, this,
                std::placeholders::_1));
}

void ImuVisualizationNode::imuCallback(
    const sensor_msgs::msg::Imu::ConstSharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "IMU Callback run!");
}

int32_t main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  options.arguments({"imu_visualization_node"});
  auto node = std::make_shared<ImuVisualizationNode>(options);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}