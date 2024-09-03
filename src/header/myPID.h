#ifndef MYPID_H
#define MYPID_H

// Declare PID constants
extern float Kp;
extern float Ki;
extern float Kd;

// Declare PID variables
//motor1
extern volatile double setpoint;
extern volatile double current_position;

extern volatile double previous_error;
extern volatile double integral;
extern volatile double speed;

//motor2
extern volatile double setpoint2;
extern volatile double current_position2;

extern volatile double previous_error2;
extern volatile double integral2;
extern volatile double speed2;

//motor3
extern volatile double setpoint3;
extern volatile double current_position3;

extern volatile double previous_error3;
extern volatile double integral3;
extern volatile double speed3;

// Declare the calculatePID function
void calculatePID();

void calculatePID2();

void calculatePID3();
#endif
