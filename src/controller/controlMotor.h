#ifndef DELTA_ROBOT_H
#define DELTA_ROBOT_H

#include <Arduino.h>
#include <cmath> // For math operations like sqrt, pow

// Function prototypes for delta robot control
void updateMotorPositions();

// Inverse kinematics function prototypes for calculating motor positions
float calculateMotorPosition1(float x, float y, float z);
float calculateMotorPosition2(float x, float y, float z);
float calculateMotorPosition3(float x, float y, float z);


#endif  // DELTA_ROBOT_H
