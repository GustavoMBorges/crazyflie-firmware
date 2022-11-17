#ifndef parameters_h
#define parameters_h

#include <cmath>

// Physical constants
const float pi = 3.1416;
const float g = 9.81;       // m/s^2

// Quadcopter dimensions
const float m = 30.0e-3;    // kg
const float I_xx = 16.0e-6; // kg.m^2
const float I_yy = 16.0e-6; // kg.m^2
const float I_zz = 29.0e-6; // kg.m^2
const float l = 33.0e-3;    // m


const float a1 = 1.987e-14;
const float a2 = 1.295e-7;

const float kl=1.632e-08;

const float kd=1.538e-10;

const float dt = 0.002;

// Attitude estimator (Lab 7)
const float wc = 1.0;
const float alfa = (wc*dt)/(1.0 + wc*dt);

// Attitude controller (Lab 8)
const float Ts_phi=0.3;
const float UP_phi=0.005;
const float zeta_phi = abs(log(UP_phi))/sqrt(log(UP_phi)*log(UP_phi)+pi*pi);
const float Wn_phi=4.0/(zeta_phi*Ts_phi);
const float kp_phi=Wn_phi*Wn_phi;
const float kd_phi=2.0*zeta_phi*Wn_phi;
const float kp_theta=kp_phi;
const float kd_theta=kd_phi;

const float Ts_psi=0.6;
const float UP_psi=0.005;
const float zeta_psi = abs(log(UP_psi))/sqrt(log(UP_psi)*log(UP_psi)+pi*pi);
const float Wn_psi= 4.0/(zeta_psi*Ts_psi);
const float kp_psi=Wn_psi*Wn_psi;
const float kd_psi=2.0*zeta_psi*Wn_psi;

// Vertical estimator (Lab 9)
const float l_ver = 10.0;
const float zeta_ver = sqrt(2.0)/2.0;
const float dt_range = 0.05;
const float l1 = l_ver*l_ver;
const float l2 = 2*zeta_ver*l_ver;

// Vertical controller (Lab 10)
const float Ts_z=2.0;
const float UP_z=0.005;
const float zeta_z = abs(log(UP_z))/sqrt(log(UP_z)*log(UP_z)+pi*pi);
const float Wn_z= 4.0/(zeta_z*Ts_z);
const float kp_z=Wn_z*Wn_z;
const float kd_z=2.0*zeta_z*Wn_z;

// Horizontal estimator (Lab 11)
const float ang_visao = 42.0*(pi/180.0);
const float W = 420.0;
const float sigma = (2.0*tan(ang_visao/2.0))/(W*dt);
const float l_hor = 50.0;

// Horizontal controller (Lab 12)
const float Ts_x=2.0;
const float UP_x=0.005;
const float zeta_x = abs(log(UP_x))/sqrt(log(UP_x)*log(UP_x)+pi*pi);
const float Wn_x= 4.0/(zeta_x*Ts_x);
const float kp_x=Wn_x*Wn_x;
const float kd_x=2.0*zeta_x*Wn_x;
const float kp_y=kp_x;
const float kd_y=kd_x;

// Parâmetros de voô

const float ts = 2;
const float tv= 5;
const float td = 2;
const float tt = ts + tv + td;

const float h = 1.0;
const float d = 2.0;


#endif