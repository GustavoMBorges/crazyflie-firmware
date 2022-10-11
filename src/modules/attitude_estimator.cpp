# include " attitude_estimator .h"

 // Class constructor
 AttitudeEstimator :: AttitudeEstimator () : imu ( IMU_SDA , IMU_SCL )
 {
    phi = 0;
    theta = 0;
    psi = 0;
    // Angular velocities ( rad /s)
    p = 0;
    q = 0;
    r = 0;
 
 }

 // Initialize class
 void AttitudeEstimator :: init ()
 {
  imu.init()
 }

 // Estimate Euler angles (rad ) and angular velocities ( rad /s)
void AttitudeEstimator :: estimate ()
 {
 imu.read()

    // serial.printf("Acc [m/s^2]: %6.2f %6.2f %6.2f\n",imu.ax,imu.ay,imu.az);
    // serial.printf("Gyr [rad/s]: %6.2f %6.2f %6.2f\n",imu.gx,imu.gy,imu.gz);
    p = imu.gx;
    q = imu.gy;
    r = imu.gz;

    phi_a = atan2(-imu.ay, -imu.ax);
    phi = phi_a
  }
