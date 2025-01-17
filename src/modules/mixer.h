#ifndef mixer_h
#define mixer_h

#include "crazyflie.h"
#include "mbed.h"

// Total notes count.
#define NOTES_COUNT 305
// The duration(delay) and frequency numbers in the array.
#define NOTE_SIZE 2



// Mixer class
class Mixer {
public:
  // Class constructor
  Mixer();
  // Actuate motors with desired total trust force (N) and torques (N.m)
  void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi);
  void arm();
  void disarm();
  int i;

private:
  bool armed;
  // Motors PWM outputs
  PwmOut motor_1, motor_2, motor_3, motor_4;
  // Angular velocities ( rad /s)
  DigitalOut led_red_r;
  DigitalOut led_red_l;
  DigitalOut led_green_r;
  DigitalOut led_green_l;
  float omega_1, omega_2, omega_3, omega_4;
  // Convert total thrust force (N) and torques (N.m) to angular velocities
  // (rad/s)
  void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi);
  // Convert desired angular velocity ( rad /s) to PWM signal (%)
  float control_motor(float omega);
};

#endif