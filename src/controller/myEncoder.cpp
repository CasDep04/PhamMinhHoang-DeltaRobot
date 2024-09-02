#include "./header/myEncoder.h"
#include <Arduino.h>

// Define encoder pins
//motor1
const int encoderPinA = 22;  // Yellow wire
const int encoderPinB = 23; // Green wire


// Declare the current position variable (shared with myPID)
//motor1
extern double current_position;

void encoder_init(){
  // Setup encoder pins as inputs (now handled in myEncoder.cpp)
  //motor1
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  
  // Attach interrupt to encoder pin A
  attachInterrupt(digitalPinToInterrupt(encoderPinA), readEncoder, CHANGE);

}

void readEncoder() {
  // Read encoder pins and update position
  int encoderA = digitalRead(encoderPinA);
  int encoderB = digitalRead(encoderPinB);

  if (encoderA == encoderB) {
    current_position++;
  } else {
    current_position--;
  }
}
