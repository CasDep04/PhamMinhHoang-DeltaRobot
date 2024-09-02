#include "./header/myPID.h"
#include <Arduino.h>

// Define PID constants
float Kp = 1.0;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 0.05; // Derivative gain

// Define PID variables
//motor1
double setpoint = 200;  // Desired position or speed
double current_position = 0;  // Current position or speed

double previous_error = 0;
double integral = 0;
double speed =0;

//motor2
double setpoint2 = 200;
double current_position2 = 0;

double previous_error2 = 0;
double integral2 = 0;
double speed2 =0;

//motor3
double current_position3 = 0;

void calculatePID() {
  // Calculate the error
  double error = setpoint - current_position;

  // Calculate the integral
  integral += error;

  // Calculate the derivative
  double derivative = error - previous_error;

  // Calculate the PID output
  double output = Kp * error + Ki * integral + Kd * derivative;

  // Store the current error as previous error for the next loop
  previous_error = error;

  // Limit the output to the motor's PWM range (0-255)
  output = constrain(output, -255, 255);

  speed = output;
}

void calculatePID2() {
  // Calculate the error
  double error2 = setpoint2 - current_position2;

  // Calculate the integral
  integral2 += error2;

  // Calculate the derivative
  double derivative2 = error2 - previous_error2;

  // Calculate the PID output
  double output2 = Kp * error2 + Ki * integral2 + Kd * derivative2;

  // Store the current error as previous error for the next loop
  previous_error2 = error2;

  // Limit the output to the motor's PWM range (0-255)
  output2 = constrain(output2, -255, 255);

  speed2 = output2;
}