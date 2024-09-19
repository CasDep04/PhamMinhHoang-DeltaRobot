#include <Arduino.h>
#include <cmath> // For math operations like sqrt, pow
#include "./header/controlMotor.h"

// Global variables for input and motor positions
extern int sliderValue; // Z axis (height)
extern int joystickX;   // X axis (horizontal)
extern int joystickY;   // Y axis (horizontal)
extern double setpointMotor1; 
extern double setpointMotor2; 
extern double setpointMotor3; 

int lastSliderValue = 0;

// Robot-specific constants
const float BASE_RADIUS = 100.0;  // Base radius of the delta robot
const float END_EFFECTOR_RADIUS = 50.0; // Radius of the end-effector
const float ARM_LENGTH = 120.0;  // Length of the robot's arms
const float MAX_HEIGHT = 150.0;  // Maximum height for the Z axis

void updateMotorPositions() {
    // Constants for workspace mapping
    const float maxXYMovement = 50.0;   // Max X and Y movement range
    const float baseHeight = 100.0;     // Base height of the platform
    const float maxHeightChange = 50.0; // Max height (Z) movement range

    // Map joystick and slider inputs to X, Y, Z coordinates
    float targetX = (joystickX / 100.0) * maxXYMovement;   // Map joystickX (-100 to 100) to X
    float targetY = (joystickY / 100.0) * maxXYMovement;   // Map joystickY (-100 to 100) to Y
    float height = baseHeight + (sliderValue / 100.0) * maxHeightChange; // Map sliderZ to Z (height)

    // Inverse kinematics: calculate motor positions based on X, Y, Z
    float motor1Pos = calculateMotorPosition1(targetX, targetY, height);
    float motor2Pos = calculateMotorPosition2(targetX, targetY, height);
    float motor3Pos = calculateMotorPosition3(targetX, targetY, height);

    setpointMotor1 = motor1Pos;
    setpointMotor2 = motor2Pos;
    setpointMotor3 = motor3Pos;
}

// Inverse kinematics calculation for motor 1
float calculateMotorPosition1(float x, float y, float z) {
    // Calculate motor 1 position based on X, Y, Z (using inverse kinematics)
    // This is a simplified IK calculation assuming planar movements
    float motorPos = sqrt(pow(ARM_LENGTH, 2) - pow(x + BASE_RADIUS, 2) - pow(y, 2)) - z;
    return motorPos;
}

// Inverse kinematics calculation for motor 2
float calculateMotorPosition2(float x, float y, float z) {
    // Motor 2 is 120 degrees rotated from motor 1
    float x2 = x * cos(2.0 * M_PI / 3.0) - y * sin(2.0 * M_PI / 3.0);
    float y2 = x * sin(2.0 * M_PI / 3.0) + y * cos(2.0 * M_PI / 3.0);
    float motorPos = sqrt(pow(ARM_LENGTH, 2) - pow(x2 + BASE_RADIUS, 2) - pow(y2, 2)) - z;
    return motorPos;
}

// Inverse kinematics calculation for motor 3
float calculateMotorPosition3(float x, float y, float z) {
    // Motor 3 is -120 degrees rotated from motor 1
    float x3 = x * cos(-2.0 * M_PI / 3.0) - y * sin(-2.0 * M_PI / 3.0);
    float y3 = x * sin(-2.0 * M_PI / 3.0) + y * cos(-2.0 * M_PI / 3.0);
    float motorPos = sqrt(pow(ARM_LENGTH, 2) - pow(x3 + BASE_RADIUS, 2) - pow(y3, 2)) - z;
    return motorPos;
}

