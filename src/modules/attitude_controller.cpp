#include "attitude_controller.h"

// Class constructor
AttitudeController ::AttitudeController() {
  tau_phi = 0;
  tau_psi = 0;
  tau_theta = 0;
}

// Control torques (N.m) given reference angles ( rad) and current angles ( rad
// ) and angular velocities ( rad /s)
void AttitudeController ::control(float phi_r, float theta_r, float psi_r,
                                  float phi, float theta, float psi, float p,
                                  float q, float r) {

  float phi_ac = control_siso(phi_r, phi, p, kp_phi, kd_phi);
  float theta_ac =
      control_siso(theta_r, theta, q, kp_theta, kd_theta);
  float psi_ac =
      control_siso(psi_r, psi, r, kp_psi, kd_psi);

  tau_phi = I_xx * phi_ac;
  tau_theta = I_yy * theta_ac;
  tau_psi = I_zz * psi_ac;
}

// Control torque (N.m) given reference angle ( rad ) and current angle ( rad )
// and angular velocity ( rad /s) with given controller gains
float AttitudeController ::control_siso(float angle_r, float angle, float rate,
                                        float kp,
                                        float kd) {

  return kp * (angle_r - angle) + kd * (0 - rate);
}
