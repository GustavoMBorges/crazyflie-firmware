#include "mbed.h"
#include "crazyflie.h"

// Define all LEDs as digital output objects
DigitalOut led_red_r(LED_RED_R,!false);
DigitalOut led_red_l(LED_RED_L,!false);
DigitalOut led_green_r(LED_GREEN_R,!false);
DigitalOut led_green_l(LED_GREEN_L,!false);
DigitalOut led_blue_l(LED_BLUE_L,!false);


// Define all motors as PWM objects
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

// Main program
int main()
{
    // Blink blue LED indicating inicialization (5 seconds)
    for(int i=0;i<=50;i++)
    {
        led_blue_l = !led_blue_l;
        wait(0.1);
    }
    
    // Turn on red LEDs indicating motors are armed

        led_red_l = !led_red_l;
        led_red_r = !led_red_r;
        wait(2);
    
    // Test all motors with different frequencies (to make different noises)
        motor1.period(1.0/400.0);
        motor1 = 0.2;
        wait(0.2);
        motor1 = 0.0;

        motor2.period(1.0/600.0);
        motor2 = 0.2;
        wait(0.2);
        motor2 = 0.0;

        motor3.period(1.0/500.0);
        motor3 = 0.2;
        wait(0.2);
        motor3 = 0.0;

        motor4.period(1.0/700.0);
        motor4 = 0.2;
        wait(0.2);
        motor4 = 0.0;
    
    // Turn off red LEDs indicating motors are disarmed

        led_red_l = !led_red_l; 
        led_red_r = !led_red_r;
    
    // Blink green LEDs indicating end of program
    while(true)
    {
        led_green_l = !led_green_l;
        led_green_r = !led_green_r;
        wait(0.5);
    }
}
