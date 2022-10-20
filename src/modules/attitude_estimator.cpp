# include "attitude_estimator.h"

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
    //
    p_bias = 0;
    q_bias = 0;
    r_bias = 0;
 
 }

 // Initialize class
 void AttitudeEstimator :: init ()
 {
  imu.init();
  
  for (int i=0; i<500; i++)
  {
      imu.read();
      p_bias += imu.gx/500.0;
      q_bias += imu.gy/500.0;
      r_bias += imu.gz/500.0;
      wait(dt);
  }
 }

 // Estimate Euler angles (rad ) and angular velocities ( rad /s)
void AttitudeEstimator :: estimate ()
 {
 imu.read();

    // serial.printf("Acc [m/s^2]: %6.2f %6.2f %6.2f\n",imu.ax,imu.ay,imu.az);
    // serial.printf("Gyr [rad/s]: %6.2f %6.2f %6.2f\n",imu.gx,imu.gy,imu.gz);

    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;

    float phi_a = atan2(-imu.ay, -imu.az);
    float sign_az = (imu.az>0) - (imu.az<0);
    float theta_a = atan2(imu.ax,-sign_az*sqrt(imu.ay*imu.ay + imu.az*imu.az));
    
    float phi_g = phi + (p + sin(phi)*tan(theta)*q + cos(phi)*tan(theta)*r)*dt ;
    float theta_g = theta + (cos(phi)*q - sin(phi)*r)*dt ;
    float psi_g = psi + (sin(phi)/cos(theta)*q + cos(phi)/cos(theta)*r)*dt;
    
    phi = (1.0-alfa)*phi_g + alfa*phi_a;
    theta = (1.0-alfa)*theta_g + alfa*theta_a;
    psi = psi_g;
  }
