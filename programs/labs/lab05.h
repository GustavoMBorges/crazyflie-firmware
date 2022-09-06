#include "crazyflie.h"
#include "mbed.h"


// Define motor 3 as PWM output object
// Define motor as PWM output object
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

float omega_1;
float omega_2;
float omega_3;
float omega_4;

// Função rad/s para PWM
float control_motor(float omega) { return a2 * (omega * omega) + a1 * omega; }

// Função N e N.m para rad/s
void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi){

    float omega_1_sqr = (1.0/(4.0*kl))*f_t - (1.0/(4.0*kl*l))*tau_phi - (1.0/(4.0*kl*l))*tau_theta - (1.0/(4.0*kd))* tau_psi;
    if (omega_1_sqr>0)
    {
        omega_1 = sqrt(omega_1_sqr);
    }
    else 
    {
        omega_1 = 0.0;
    }


    float omega_2_sqr = (1.0/(4.0*kl))*f_t - (1.0/(4.0*kl*l))*tau_phi + (1.0/(4.0*kl*l))*tau_theta + (1.0/(4.0*kd))* tau_psi;
    if (omega_2_sqr>0)
    {
        omega_2 = sqrt(omega_2_sqr);
    }
    else 
    {
        omega_2 = 0.0;
    }

    float omega_3_sqr = (1.0/(4.0*kl))*f_t + (1.0/(4.0*kl*l))*tau_phi + (1.0/(4.0*kl*l))*tau_theta - (1.0/(4.0*kd))* tau_psi;
    if (omega_3_sqr>0)
    {
        omega_3 = sqrt(omega_3_sqr);
    }
    else 
    {
        omega_3 = 0.0;
    }

    float omega_4_sqr = (1.0/(4.0*kl))*f_t + (1.0/(4.0*kl*l))*tau_phi - (1.0/(4.0*kl*l))*tau_theta + (1.0/(4.0*kd))* tau_psi;
    if (omega_4_sqr>0)
    {
        omega_4 = sqrt(omega_4_sqr);
    }
    else 
    {
        omega_4 = 0.0;
    }

};

// Atuator do motor com força e torque desejados em N e N.m
void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi){
    mixer(f_t, tau_phi, tau_theta, tau_psi);
    motor1 = control_motor(omega_1);
    motor2 = control_motor(omega_2);
    motor3 = control_motor(omega_3);
    motor4 = control_motor(omega_4);
}

// Main program
int main() {
    // Set PWM frequency to 500 Hz
    motor1.period(1.0 / 500.0);
    motor2.period(1.0 / 500.0);
    motor3.period(1.0 / 500.0);
    motor4.period(1.0 / 500.0);

    actuate(0,0,0,-0.001);
    wait(5);

    actuate(0,0,0,0);
  while (true) {
  }
}