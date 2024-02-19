#include "imu_visualization/imu_visualization_node.hpp"

ImuVisualizationNode::ImuVisualizationNode(const rclcpp::NodeOptions &options)
    : Node(options.arguments()[0], options) {
  RCLCPP_INFO(this->get_logger(), "%s constructor",
              options.arguments()[0].c_str());
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
  angular_q_ = tf2::Quaternion(0, 0, 0, 1);
  imu_q_ = tf2::Quaternion(0, 0, 0, 1);
  imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "imu", rclcpp::QoS(1),
      std::bind(&ImuVisualizationNode::imuCallback, this,
                std::placeholders::_1));

  tf_transform_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(30),
      std::bind(&ImuVisualizationNode::tfTransformTimerCallback, this));
}

void ImuVisualizationNode::imuCallback(
    const sensor_msgs::msg::Imu::ConstSharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "IMU Callback run!");
  auto angular_velocities = msg->angular_velocity;
  Eigen::Vector3d angular_vector;
  angular_vector << angular_velocities.x, angular_velocities.y,
      angular_velocities.z;
  auto omega = ImuUtils::angularVel2Omega(angular_vector);
  angular_q_ = ImuUtils::angularQuaternionUpdate(angular_q_, omega, 0.005);
  imu_q_.setW(msg->orientation.w);
  imu_q_.setX(msg->orientation.x);
  imu_q_.setY(msg->orientation.y);
  imu_q_.setZ(msg->orientation.z);
}

void ImuVisualizationNode::tfTransformTimerCallback() {}

int32_t main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  options.arguments({"imu_visualization_node"});
  auto node = std::make_shared<ImuVisualizationNode>(options);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}