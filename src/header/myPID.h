#ifndef MYPID_H
#define MYPID_H

// Declare PID constants
extern float Kp;
extern float Ki;
extern float Kd;

// Declare PID variables
//motor1
extern double setpoint;
extern double current_position;

extern double previous_error;
extern double integral;
extern double speed;

//motor2
extern double setpoint2;
extern double current_position2;

extern double previous_error2;
extern double integral2;
extern double speed2;

//motor3
extern double setpoint3;
extern double current_position3;

extern double previous_error3;
extern double integral3;
extern double speed3;

// Declare the calculatePID function
void calculatePID();

void calculatePID2();

void calculatePID3();
#endif
