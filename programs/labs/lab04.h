#include "crazyflie.h"
#include "mbed.h"

// Define motor 3 as PWM output object
// Define motor as PWM output object
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

// Converts desired angular velocity ( rad/s) to PWM signal (%)
float control_motor(float omega) { return a2 * (omega * omega) + a1 * omega; }

// Main program
int main() {

  while (true) {
    // Set PWM frequency to 500 Hz
    motor1.period(1.0 / 500.0);
    motor2.period(1.0 / 500.0);
    motor3.period(1.0 / 500.0);
    motor4.period(1.0 / 500.0);
    // Turn on motor with 1.000 rad /s for 0.5s
    motor1 = control_motor(1000.0);
    motor2 = control_motor(2000.0);
    motor3 = control_motor(1000.0);
    motor4 = control_motor(2000.0);

    wait(30.0);
    // Turn off motor
    motor1 = 0.0;
    motor2= 0.0;
    motor3 = 0.0;
    motor4 = 0.0;

    wait(15.0);
    // End of program
  }
}