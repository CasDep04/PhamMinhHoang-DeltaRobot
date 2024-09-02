#include "./header/mySerial.h"
#include <Arduino.h>

void serial_innit(){
  Serial.begin(9600);
}

void printDebugInfo(double setpoint, double current_position) {
  // Debugging output
  Serial.print(">Target Position:");
  Serial.println(setpoint);

  Serial.print(">Current Position:");
  Serial.println(current_position);
}

void printDebugInfo2(double setpoint, double current_position) {
  // Debugging output
  Serial.print(">Target Position 2:");
  Serial.println(setpoint);

  Serial.print(">Current Position 2:");
  Serial.println(current_position);
}
