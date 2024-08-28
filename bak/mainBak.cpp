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
  double output = calculatePID(setpoint, current_position);
  runMotor1(output);

  // Use the new serial debugging function
  printDebugInfo(setpoint, current_position);
}