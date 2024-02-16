#ifndef IMU_UTIL_HPP_
#define IMU_UTIL_HPP_
#include <Eigen/Core>
#include <iostream>
#include <tf2/LinearMath/Quaternion.h>
namespace ImuUtils {
/**
 * @brief 3d vector into skew symmetric matrix
 *
 * @param vector 3d vector
 */
Eigen::Matrix3d vector2matrix(const Eigen::Vector3d &vector);
Eigen::Matrix4d angularVel2Omega(const Eigen::Vector3d &angular_velocities);
tf2::Quaternion angularQuaternionUpdate(const tf2::Quaternion &q,
                                        const Eigen::Matrix4d &omega,
                                        const double &delta);
} // namespace ImuUtils

#endif