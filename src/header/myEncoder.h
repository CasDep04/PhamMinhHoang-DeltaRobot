#ifndef MYENCODER_H
#define MYENCODER_H

// Encoder pins
//motor1
extern const int encoderPinA;
extern const int encoderPinB;

extern const int encoderPinA2;
extern const int encoderPinB2;
//initialize
void encoder_init();
// Function prototypes
void readEncoder();
void readEncoder2();

//motor2
#endif
