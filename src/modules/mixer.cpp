#include "mixer.h"

// Class constructor
Mixer ::Mixer()
    : motor_1(MOTOR1), motor_2(MOTOR2), motor_3(MOTOR3), motor_4(MOTOR4),
      led_red_r(LED_RED_R, false), led_red_l(LED_RED_L, false),
      led_green_l(LED_GREEN_L, false), led_green_r(LED_GREEN_R, false) {
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
  if (armed) {
    mixer(f_t, tau_phi, tau_theta, tau_psi);
    motor_1 = control_motor(omega_1);
    motor_2 = control_motor(omega_2);
    motor_3 = control_motor(omega_3);
    motor_4 = control_motor(omega_4);
    led_red_l = false;
    led_red_r = false;
  } else {
    led_red_l = true;
    led_red_r = true;
    led_green_l = false;
    led_green_r = false;
  }
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

void Mixer ::arm() {
  led_green_l = true;
  led_green_r = true;
  armed = true;
  int i = 5;
  while (i > 0) {
    led_red_l = false;
    led_red_r = false;
    wait(0.5);
    led_red_l = true;
    led_red_r = true;
    wait(0.5);
    i--;
  }

  int noteIndex = 0;
  int melodia[] = {
      660, 150, 660, 300, 660, 300, 510, 100, 660, 300, 150, 660, 300, 660, 300,
      510, 100, 660, 300, 770, 660, 300, 660, 300, 510, 100, 660, 300, 770, 550,
      300, 660, 300, 510, 100, 660, 300, 770, 550, 380, 660, 300, 510, 100, 660,
      300, 770, 550, 380, 575, 300, 510, 100, 660, 300, 770, 550, 380, 575, 510,
      510, 100, 660, 300, 770, 550, 380, 575, 510, 450, 100, 660, 300, 770, 550,
      380, 575, 510, 450, 380, 660, 300, 770, 550, 380, 575, 510, 450, 380, 400,
      300, 770, 550, 380, 575, 510, 450, 380, 400, 320, 770, 550, 380, 575, 510,
      450, 380, 400, 320, 500, 550, 380, 575, 510, 450, 380, 400, 320, 500, 440,
      380, 575, 510, 450, 380, 400, 320, 500, 440, 300, 575, 510, 450, 380, 400,
      320, 500, 440, 300, 480, 510, 450, 380, 400, 320, 500, 440, 300, 480, 330,
      450, 380, 400, 320, 500, 440, 300, 480, 330, 450, 380, 400, 320, 500, 440,
      300, 480, 330, 450, 150, 400, 320, 500, 440, 300, 480, 330, 450, 150, 430,
      320, 500, 440, 300, 480, 330, 450, 150, 430, 300, 500, 440, 300, 480, 330,
      450, 150, 430, 300, 380, 440, 300, 480, 330, 450, 150, 430, 300, 380, 200,
      300, 480, 330, 450, 150, 430, 300, 380, 200, 660, 480, 330, 450, 150, 430,
      300, 380, 200, 660, 200, 330, 450, 150, 430, 300, 380, 200, 660, 200, 760,
      450, 150, 430, 300, 380, 200, 660, 200, 760, 150, 150, 430, 300, 380, 200,
      660, 200, 760, 150, 860, 430, 300, 380, 200, 660, 200, 760, 150, 860, 300,
      300, 380, 200, 660, 200, 760, 150, 860, 300, 700, 380, 200, 660, 200, 760,
      150, 860, 300, 700, 150, 200, 660, 200, 760, 150, 860, 300, 700, 150, 760,
      660, 200, 760, 150, 860, 300, 700, 150, 760, 350, 200, 760, 150, 860, 300,
      700, 150, 760, 350, 660, 760, 150, 860, 300, 700, 150, 760, 350, 660, 300,
      150, 860, 300, 700, 150, 760, 350, 660, 300, 520, 860, 300, 700, 150, 760,
      350, 660, 300, 520, 150, 300, 700, 150, 760, 350, 660, 300, 520, 150, 580,
      700, 150, 760, 350, 660, 300, 520, 150, 580, 150, 150, 760, 350, 660, 300,
      520, 150, 580, 150, 480, 760, 350, 660, 300, 520, 150, 580, 150, 480, 500,
      350, 660, 300, 520, 150, 580, 150, 480, 500, 510, 660, 300, 520, 150, 580,
      150, 480, 500, 510, 450, 300, 520, 150, 580, 150, 480, 500, 510, 450, 380,
      520, 150, 580, 150, 480, 500, 510, 450, 380, 400, 150, 580, 150, 480, 500,
      510, 450, 380, 400, 320, 580, 150, 480, 500, 510, 450, 380, 400, 320, 500,
      150, 480, 500, 510, 450, 380, 400, 320, 500, 440, 480, 500, 510, 450, 380,
      400, 320, 500, 440, 300, 500, 510, 450, 380, 400, 320, 500, 440, 300, 480,
      510, 450, 380, 400, 320, 500, 440, 300, 480, 330, 450, 380, 400, 320, 500,
      440, 300, 480, 330, 450, 380, 400, 320, 500, 440, 300, 480, 330, 450, 150,
      400, 320, 500, 440, 300, 480, 330, 450, 150, 430, 320, 500, 440, 300, 480,
      330, 450, 150, 430, 300, 500, 440, 300, 480, 330, 450, 150, 430, 300, 380,
      440, 300, 480, 330, 450, 150, 430, 300, 380, 200, 300, 480, 330, 450, 150,
      430, 300, 380, 200, 660, 480, 330, 450, 150, 430, 300, 380, 200, 660, 200,
      330, 450, 150, 430, 300, 380, 200, 660, 200, 760, 450, 150, 430, 300, 380,
      200, 660, 200, 760, 150, 150, 430, 300, 380, 200, 660, 200, 760, 150, 860,
      430, 300, 380, 200, 660, 200, 760, 150, 860, 300, 300, 380, 200, 660, 200,
      760, 150, 860, 300, 700, 0,   0,   0,   0,   0,   0};

  while (noteIndex < NOTES_COUNT) {
    motor_1.period(1.0 / melodia[noteIndex + 1]);
    motor_1 = 0.05;
    wait_ms(melodia[noteIndex]);
    motor_1 = 0.0;

    motor_2.period(1.0 / melodia[noteIndex + 3]);
    motor_2 = 0.05;
    wait_ms(melodia[noteIndex + 2]);
    motor_2 = 0.0;

    motor_3.period(1.0 / melodia[noteIndex + 5]);
    motor_3 = 0.05;
    wait_ms(melodia[noteIndex + 4]);
    motor_3 = 0.0;

    motor_4.period(1.0 / melodia[noteIndex + 7]);
    motor_4 = 0.05;
    wait_ms(melodia[noteIndex + 6]);
    motor_4 = 0.0;

    noteIndex += 8;
  }

  motor_1.period(1.0 / 500.0);
  motor_2.period(1.0 / 500.0);
  motor_3.period(1.0 / 500.0);
  motor_4.period(1.0 / 500.0);
}
void Mixer ::disarm() {
  actuate(0, 0, 0, 0);

  armed = false;
  led_green_r = false;
  led_green_l = false;
}
