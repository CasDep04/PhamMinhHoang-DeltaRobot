#include <Arduino.h>
#include "./header/myPID.h"  // Include the PID header
#include "./header/myMotor.h"  // Include the Motor control header
#include "./header/myEncoder.h"  // Include the Encoder handling header
#include "./header/mySerial.h"  // Include the Serial handling header
#include "./header/myWifi.h"  // Include the Serial handling header

void setup() {

  serial_innit();
  motor_init();
  encoder_init();
  //initWebApp();
}

void loop() {
  //runMotor1PID();
  //runMotor2PID();
  //runMotor3PID();

  //handleClient();
  runMotor1(-100);

  // Use the new serial debugging function
  //printDebugInfo(setpoint, current_position);
  //printDebugInfo2(setpoint2, current_position2);
  //printDebugInfo3(setpoint3, current_position3);
}