#include "imu_visualization/imu_util.hpp"

namespace ImuUtils {
Eigen::Matrix3d vector2matrix(const Eigen::Vector3d &vector) {
  Eigen::Matrix3d matrix;
  matrix << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  return matrix;
}
Eigen::Matrix4d angularVel2Omega(const Eigen::Vector3d &vector) {
  Eigen::Matrix4d matrix = Eigen::Matrix4d::Zero();
  matrix.block<1, 3>(0, 1) = vector.transpose();
  matrix.block<3, 1>(1, 0) = vector;
  matrix.block<3, 3>(1, 1) = ImuUtils::vector2matrix(vector);

  return matrix;
}
tf2::Quaternion angularQuaternionUpdate(const tf2::Quaternion &q,
                                        const Eigen::Matrix4d &omega,
                                        const double &delta) {
  Eigen::Vector4d quaternion_p;
  tf2::Quaternion tf2_q_updated;
  auto update_term = 0.5 * omega * delta;

  quaternion_p << q.getW(), q.getX(), q.getY(), q.getZ();
  Eigen::Vector4d q_updated =
      (Eigen::Matrix4d::Identity() + update_term) * quaternion_p;

  tf2_q_updated.setW(q_updated(0));
  tf2_q_updated.setX(q_updated(1));
  tf2_q_updated.setY(q_updated(2));
  tf2_q_updated.setZ(q_updated(3));

  return tf2_q_updated;
}
} // namespace ImuUtils