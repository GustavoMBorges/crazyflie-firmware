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

const float wc = 1.0;
const float alfa = (wc*dt)/(1.0 + wc*dt);

// phi e theta
const float Ts=0.3;
const float UP=0.005;

const float zeta = abs(log(UP))/sqrt(log(UP)*log(UP)+pi*pi);
const float Wn=4.0/(zeta*Ts);

const float kp_controlador=Wn*Wn;
const float kd_controlador=2*zeta*Wn;

// yaw
const float Ts_y=0.6;
const float UP_y=0.005;

const float zeta_y = abs(log(UP_y))/sqrt(log(UP_y)*log(UP_y)+pi*pi);
const float Wn_y= 4.0/(zeta_y*Ts_y);

const float kp_controlador_y=Wn_y*Wn_y;
const float kd_controlador_y=2*zeta_y*Wn_y;

const float l_ver = 10.0;
const float zeta_ver = sqrt(2.0)/2.0;
const float dt_range = 0.05;
const float l1 = l_ver*l_ver;
const float l2 = 2*zeta_ver*l_ver;

const float kp_lab10 = 5.86;
const float kd_lab10 = 3.42;

#endif