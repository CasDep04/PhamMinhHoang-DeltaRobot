#ifndef MYPID_H
#define MYPID_H

// Declare PID constants
extern float Kp;
extern float Ki;
extern float Kd;

// Declare PID variables
extern double setpoint;
extern double current_position;
extern double previous_error;
extern double integral;
extern double speed;

// Declare the calculatePID function
void calculatePID();

#endif
