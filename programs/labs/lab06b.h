# include "mbed.h"
# include "crazyflie.h"
// Declare mixer
 Mixer mixer ;

// Main program
int main ()
{
// Arm mixer
mixer.arm();
// Actuate motor with 70% mg total thrust force (N) and zero torques
mixer.actuate (0.2 ,0 ,0 ,0) ;
wait (5) ;
 // Disarm mixer
 mixer.disarm() ;
 // End of program
 while ( true )
{
}
}