#include "./header/myPID.h"
#include <Arduino.h>

// Define PID constants
float Kp = 1.0;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 0.05; // Derivative gain

// Define PID variables
//motor1
double volatile setpoint = 0;  // Desired position or speed
double volatile current_position = 0;  // Current position or speed

double volatile previous_error = 0;
double volatile integral = 0;
double volatile speed =0;

//motor2
double volatile setpoint2 = 0;
double volatile current_position2 = 0;

double volatile previous_error2 = 0;
double volatile integral2 = 0;
double volatile speed2 =0;

//motor3
double volatile setpoint3 = 0;
double volatile current_position3 = 0;

double volatile previous_error3 = 0;
double volatile integral3 = 0;
double volatile speed3 =0;

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

void calculatePID3(){
    // Calculate the error
  double error3 = setpoint3 - current_position3;

  // Calculate the integral
  integral3 += error3;

  // Calculate the derivative
  double derivative3 = error3 - previous_error3;

  // Calculate the PID output
  double output3 = Kp * error3 + Ki * integral3 + Kd * derivative3;

  // Store the current error as previous error for the next loop
  previous_error3 = error3;

  // Limit the output to the motor's PWM range (0-255)
  output3 = constrain(output3, -255, 255);

  speed3 = output3;
}

void updateSetPoint(int isLeft, double degree){
  double tempEncoder = (330 * degree) / 360;
  if(isLeft == 1){
    setpoint = setpoint + tempEncoder;
  }else{
    setpoint = setpoint - tempEncoder;
  }
};


void updateSetPoint2(int isLeft, double degree){
  double tempEncoder = (330 * degree) / 360;
  if(isLeft == 1){
    setpoint2 = setpoint2 + tempEncoder;
  }else{
    setpoint2 = setpoint2 - tempEncoder;
  }
};

void updateSetPoint3(int isLeft, double degree){
  double tempEncoder = (330 * degree) / 360;
  if(isLeft == 1){
    setpoint3 = setpoint3 + tempEncoder;
  }else{
    setpoint3 = setpoint3 - tempEncoder;
  }
};