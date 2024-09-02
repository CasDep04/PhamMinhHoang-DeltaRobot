#ifndef MYMOTOR_H
#define MYMOTOR_H

// Motor control pins for motor 1
extern const int motorPinA;
extern const int motorPinB;

extern const int motorPinA2;
extern const int motorPinB2;

//initailize
void motor_init();
// Function prototypes
void runMotor1(double output);

void runMotor2(double output);

#endif
