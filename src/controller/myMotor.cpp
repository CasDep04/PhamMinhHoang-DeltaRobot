#include "./header/myMotor.h"
#include "./header/myPID.h"
#include <Arduino.h>

// Define motor control pins for motor 1
const int motorPinA = 17; // LPWM, clockwise
const int motorPinB = 18; // RPWM, counter-clockwise

//motor2
const int motorPinA2 = 19; // LPWM, clockwise
const int motorPinB2 = 21; // RPWM, counter-clockwise

//motor3
const int motorPinA3 = 25; // LPWM, clockwise
const int motorPinB3 = 26; // RPWM, counter-clockwise

void motor_init(){
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  pinMode(motorPinA2, OUTPUT);
  pinMode(motorPinB2, OUTPUT);

  pinMode(motorPinA3, OUTPUT);
  pinMode(motorPinB3, OUTPUT);
}

void runMotor1(double output) {
  // Apply the output to the motor
  if (output > 0) {
    // Rotate clockwise
    analogWrite(motorPinA, output);
    analogWrite(motorPinB, 0);
  } else {
    // Rotate counter-clockwise
    analogWrite(motorPinA, 0);
    analogWrite(motorPinB, -output);
  }

  // Small delay to stabilize the loop
  delay(10);
}

//motor2
void runMotor2(double output) {
  // Apply the output to the motor
  if (output > 0) {
    // Rotate clockwise
    analogWrite(motorPinA2, output);
    analogWrite(motorPinB2, 0);
  } else {
    // Rotate counter-clockwise
    analogWrite(motorPinA2, 0);
    analogWrite(motorPinB2, -output);
  }

  // Small delay to stabilize the loop
  delay(10);
}

void runMotor3(double output) {
  // Apply the output to the motor
  if (output > 0) {
    // Rotate clockwise
    analogWrite(motorPinA3, output);
    analogWrite(motorPinB3, 0);
  } else {
    // Rotate counter-clockwise
    analogWrite(motorPinA3, 0);
    analogWrite(motorPinB3, -output);
  }

  // Small delay to stabilize the loop
  delay(10);
}

void runMotor1PID(){
  calculatePID();
  runMotor1(speed);
}

void runMotor2PID(){
  calculatePID2();
  runMotor2(speed2);
}

void runMotor3PID(){
  calculatePID3();
  runMotor3(speed3);
}