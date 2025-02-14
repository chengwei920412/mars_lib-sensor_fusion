// Copyright (C) 2021 Christian Brommer, Control of Networked Systems, University of Klagenfurt, Austria.
//
// All rights reserved.
//
// This software is licensed under the terms of the BSD-2-Clause-License with
// no commercial use allowed, the full terms of which are made available
// in the LICENSE file. No license in patents is granted.
//
// You can contact the author at <christian.brommer@ieee.org>

#ifndef UTILS_H
#define UTILS_H

#include <mars/sensors/imu/imu_measurement_type.h>
#include <Eigen/Dense>
#include <string>
#include <vector>

namespace mars
{
class Utils
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Utils();

  ///
  /// \brief TransformImu Transform IMU measurements from current frame A to frame B
  ///
  /// This function takes angular accleration into account and thus needs the previous IMU measurement and dt
  ///
  /// \param prev Previos IMU measurement expressed in frame A
  /// \param now  Current IMU measurement expressed in frame A
  /// \param dt   Delta time between both IMU measurements
  /// \param p_ab Transformation of frame B w.r.t. frame A
  /// \param q_ab Rotation of frame B w.r.t. frame A
  /// \param result Transformed current IMU measurement expressed in frame B
  ///
  static void TransformImu(const mars::IMUMeasurementType& prev, const mars::IMUMeasurementType& now, const double& dt,
                           const Eigen::Vector3d& p_ab, const Eigen::Quaterniond& q_ab,
                           mars::IMUMeasurementType& result);

  ///
  /// \brief TransformImu Transform IMU measurements from current frame A to frame B
  ///
  /// This function does not take the angular accleration into account and thus does not need the previous IMU
  /// measurement and dt
  ///
  /// \param now  Current IMU measurement expressed in frame A
  /// \param p_ab Transformation of frame B w.r.t. frame A
  /// \param q_ab Rotation of frame B w.r.t. frame A
  /// \param result Transformed current IMU measurement expressed in frame B
  ///
  static void TransformImu(const mars::IMUMeasurementType& now, const Eigen::Vector3d& p_ab,
                           const Eigen::Quaterniond& q_ab, mars::IMUMeasurementType& result);

  ///
  /// \brief skew generate the skew symmetric matrix of v
  /// \param v 3d vector
  /// \return skew symmetric matrix
  ///
  static Eigen::Matrix3d Skew(const Eigen::Vector3d& v);

  ///
  /// \brief mat_exp Calculation of the matrix exponential, Taylor series cut-off at specified order
  /// \param A Matrix for Taylor series
  /// \param order Order at wich the series is cut-off
  /// \return
  ///
  static Eigen::Matrix4d MatExp(const Eigen::Matrix4d& A, const int& order = 4);

  ///
  /// \brief omega_mat ight multiplication
  /// \param v
  /// \return
  ///
  /// \note Reference: Joan Sola - Quaternion Kinematics for the error-state kalman filter - Equation(199)
  ///
  static Eigen::Matrix4d OmegaMat(const Eigen::Vector3d& v);

  ///
  /// \brief QuatFromSmallAngle
  /// \param d_theta_vec angle for the generation of the quaternion
  /// \return Resulting quaternion
  ///
  static Eigen::Quaterniond QuatFromSmallAngle(const Eigen::Vector3d& d_theta_vec);

  ///
  /// \brief ApplySmallAngleQuatCorr
  /// \param q_prior
  /// \param correction
  /// \return
  ///
  static Eigen::Quaterniond ApplySmallAngleQuatCorr(const Eigen::Quaterniond& q_prior,
                                                    const Eigen::Vector3d& correction);

  ///
  /// \brief RPYFromRotMat derives the roll pitch and yaw angle from a rotation matrix (in that order)
  /// \param rot_mat 3x3 rotation matrix
  /// \return Vector with [roll, pitch, yaw]
  ///
  static Eigen::Vector3d RPYFromRotMat(const Eigen::Matrix3d& rot_mat);

  ///
  /// \brief check_cov Performs tests for the properties of a given covariance matrix
  /// \param cov_mat
  /// \param description Used to associate the warning with the given covariance
  /// \param check_cond Check the condition number of the covariance matrix
  /// \return true if the covariance matrix is valid, false otherwise
  ///
  static bool CheckCov(const Eigen::MatrixXd& cov_mat, const std::string& description, const bool& check_cond = false);

  ///
  /// \brief EnforceMatrixSymmetry
  /// \param mat_in
  /// \return
  ///
  static Eigen::MatrixXd EnforceMatrixSymmetry(const Eigen::Ref<const Eigen::MatrixXd>& mat_in);

  ///
  /// \brief quaternionAverage without weights
  /// \param quats vector of quaternion being averaged
  /// \return Eigen::Quaterniond averaged quaternion
  ///
  /// \note Reference: Markley et al., Averaging Quaternions, Journal of Guidance, Control, and Dynamics,
  /// 30(4):1193-1196, June 2007
  ///
  static Eigen::Quaterniond quaternionAverage(const std::vector<Eigen::Quaterniond>& quats);

  ///
  /// \brief VecExtractEveryNthElm Takes a vector and returns a new vector which only contains every n'th element
  /// \param data Vector with a number of entries
  /// \param nth Defines the reduction of entries to only every n'th
  /// \return Vector with reduced entries
  ///
  template <typename T, typename A>
  static std::vector<T> VecExtractEveryNthElm(std::vector<T, A> const& data, const int& nth)
  {
    std::vector<T> every_nth_data;
    const int len = data.size();

    for (int k = 0; k < len - nth; k += nth)
    {
      every_nth_data.push_back(data[k]);
    }
    return every_nth_data;
  }
};
}  // namespace mars

#endif  // UTILS_H
