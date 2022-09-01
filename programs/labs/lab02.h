#include "mbed.h"
#include "crazyflie.h"

// Define motor 3 as PWM output object
PwmOut motor(MOTOR3);

// Main program
int main()
{
    // Turn motor on (20% power) and off every second
    while(true) 
    {
        motor = 0.1;
        wait(5);
        motor = 0.0;
        wait(5);
    }
}