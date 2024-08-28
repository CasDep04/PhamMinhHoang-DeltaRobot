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

double calculatePID(double setpoint, double current_position) {
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

  return output;
}

