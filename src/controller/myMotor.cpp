#include "./header/myMotor.h"
#include <Arduino.h>

// Define motor control pins for motor 1
const int motorPinA = 17; // LPWM, clockwise
const int motorPinB = 18; // RPWM, counter-clockwise

const int motorPinA2 = 19; // LPWM, clockwise
const int motorPinB2 = 21; // RPWM, counter-clockwise

void motor_init(){
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

  pinMode(motorPinA2, OUTPUT);
  pinMode(motorPinB2, OUTPUT);
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

