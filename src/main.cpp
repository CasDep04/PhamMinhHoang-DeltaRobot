#include <Arduino.h>
#include "./header/myPID.h"  // Include the PID header
#include "./header/myMotor.h"  // Include the Motor control header
#include "./header/myEncoder.h"  // Include the Encoder handling header
#include "./header/mySerial.h"  // Include the Serial handling header

void setup() {

  serial_innit();
  motor_init();
  encoder_init();
}

void loop() {
  calculatePID();
  calculatePID2();

  runMotor1(speed); 
  runMotor2(speed2);
  runMotor3(speed);

  // Use the new serial debugging function
  printDebugInfo(setpoint, current_position);
  printDebugInfo2(setpoint2, current_position2);
  printDebugInfo3(setpoint, current_position3);
}