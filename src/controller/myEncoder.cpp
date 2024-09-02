#include "./header/myEncoder.h"
#include <Arduino.h>

// Define encoder pins
//motor1
const int encoderPinA = 4;  // Yellow wire
const int encoderPinB = 16; // Green wire

const int encoderPinA2 = 22;  // Yellow wire
const int encoderPinB2 = 23; // Green wire

// Declare the current position variable (shared with myPID)
//motor1
extern double current_position;
extern double current_position2;

void encoder_init(){
  // Setup encoder pins as inputs (now handled in myEncoder.cpp)
  //motor1
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  
  //motor2
  pinMode(encoderPinA2, INPUT);
  pinMode(encoderPinB2, INPUT);
  // Attach interrupt to encoder pin A
  attachInterrupt(digitalPinToInterrupt(encoderPinA), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinA2), readEncoder2, CHANGE);

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

void readEncoder2() {
  // Read encoder pins and update position
  int encoderA2 = digitalRead(encoderPinA2);
  int encoderB2 = digitalRead(encoderPinB2);

  if (encoderA2 == encoderB2) {
    current_position2++;
  } else {
    current_position2--;
  }
}