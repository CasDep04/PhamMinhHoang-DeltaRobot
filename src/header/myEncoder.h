#ifndef MYENCODER_H
#define MYENCODER_H

// Encoder pins
//motor1
extern const int encoderPinA;
extern const int encoderPinB;

//motor2
extern const int encoderPinA2;
extern const int encoderPinB2;

//motor3
extern const int encoderPinA3;
extern const int encoderPinB3;
//initialize
void encoder_init();
// Function prototypes
void readEncoder();
void readEncoder2();
void readEncoder3();

//motor2
#endif
