#ifndef attitude_estimator_h
#define attitude_estimator_h

#include "crazyflie.h"
#include "mbed.h"

// Attitude estimator class
class AttitudeEstimator {
public:
  // Class constructor
  AttitudeEstimator();
  // Initialize class
  void init();
  // Estimate Euler angles (rad ) and angular velocities ( rad /s)
  void estimate();
  // Euler angles ( rad)
  float phi, theta, psi;
  // Angular velocities ( rad /s)
  float p, q, r;

private:
  // IMU sensor object
  // MPU9250 imu ;
  BMI088 imu;
  //
  float p_bias, q_bias, r_bias;
};

#endif