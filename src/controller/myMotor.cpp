#include "./header/myMotor.h"
#include <Arduino.h>

// Define motor control pins for motor 1
const int motorPinA = 19; // LPWM, clockwise
const int motorPinB = 21; // RPWM, counter-clockwise

void motor_init(){
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);

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


