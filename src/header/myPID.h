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
extern double current_position2;
// Declare the calculatePID function
void calculatePID();

#endif
