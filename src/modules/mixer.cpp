#include "mixer.h"

// Class constructor
Mixer ::Mixer()
    : motor_1(MOTOR1), motor_2(MOTOR2), motor_3(MOTOR3), motor_4(MOTOR4) {
  motor_1.period(1.0 / 500.0);
  motor_2.period(1.0 / 500.0);
  motor_3.period(1.0 / 500.0);
  motor_4.period(1.0 / 500.0);
  motor_1 = 0.0;
  motor_2 = 0.0;
  motor_3 = 0.0;
  motor_4 = 0.0;
}

// Actuate motors with desired total trust force (N) and torques (N.m)
void Mixer ::actuate(float f_t, float tau_phi, float tau_theta, float tau_psi) {
  mixer(f_t, tau_phi, tau_theta, tau_psi);
  motor_1 = control_motor(omega_1);
  motor_2 = control_motor(omega_2);
  motor_3 = control_motor(omega_3);
  motor_4 = control_motor(omega_4);
}

// Convert total trust force (N) and torques (N.m) to angular velocities ( rad
// /s)
void Mixer ::mixer(float f_t, float tau_phi, float tau_theta, float tau_psi) {

  float omega_1_sqr =
      (1.0 / (4.0 * kl)) * f_t - (1.0 / (4.0 * kl * l)) * tau_phi -
      (1.0 / (4.0 * kl * l)) * tau_theta - (1.0 / (4.0 * kd)) * tau_psi;
  if (omega_1_sqr > 0) {
    omega_1 = sqrt(omega_1_sqr);
  } else {
    omega_1 = 0.0;
  }

  float omega_2_sqr =
      (1.0 / (4.0 * kl)) * f_t - (1.0 / (4.0 * kl * l)) * tau_phi +
      (1.0 / (4.0 * kl * l)) * tau_theta + (1.0 / (4.0 * kd)) * tau_psi;
  if (omega_2_sqr > 0) {
    omega_2 = sqrt(omega_2_sqr);
  } else {
    omega_2 = 0.0;
  }

  float omega_3_sqr =
      (1.0 / (4.0 * kl)) * f_t + (1.0 / (4.0 * kl * l)) * tau_phi +
      (1.0 / (4.0 * kl * l)) * tau_theta - (1.0 / (4.0 * kd)) * tau_psi;
  if (omega_3_sqr > 0) {
    omega_3 = sqrt(omega_3_sqr);
  } else {
    omega_3 = 0.0;
  }

  float omega_4_sqr =
      (1.0 / (4.0 * kl)) * f_t + (1.0 / (4.0 * kl * l)) * tau_phi -
      (1.0 / (4.0 * kl * l)) * tau_theta + (1.0 / (4.0 * kd)) * tau_psi;
  if (omega_4_sqr > 0) {
    omega_4 = sqrt(omega_4_sqr);
  } else {
    omega_4 = 0.0;
  }
}

// Convert desired angular velocity ( rad /s) to PWM signal (%)
float Mixer ::control_motor(float omega) {
  return a2 * (omega * omega) + a1 * omega;
}