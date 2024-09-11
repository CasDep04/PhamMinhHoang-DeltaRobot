#include <Arduino.h>
#include <PID_v1.h>

double setpointMotor1 = 350; 
double setpointMotor2 = 350; 
double setpointMotor3 = 350; 
//double kp = 10.0, ki = 5.0, kd = 0.05;
double kp = 10, ki = 5.0, kd = 0.05;


// Input, output, reference
PID MOT1_PID(&encoderDegree1, &MOT1_cmd, &setpointMotor1, kp, ki, kd, DIRECT);
PID MOT2_PID(&encoderDegree2, &MOT2_cmd, &setpointMotor2, kp, ki, kd, DIRECT);
PID MOT3_PID(&encoderDegree3, &MOT3_cmd, &setpointMotor3, kp, ki, kd, DIRECT);

// ================================================================
// Function Definition
// ================================================================
void Init_PID()
{
  //motor1
  MOT1_PID.SetMode(AUTOMATIC);
  MOT1_PID.SetOutputLimits(-255, 255);
  MOT1_PID.SetSampleTime(10);

  //motor2
  MOT2_PID.SetMode(AUTOMATIC);
  MOT2_PID.SetOutputLimits(-255, 255);
  MOT2_PID.SetSampleTime(10);

  //motor3
  MOT3_PID.SetMode(AUTOMATIC);
  MOT3_PID.SetOutputLimits(-255, 255);
  MOT3_PID.SetSampleTime(10);
}
// ================================================================
void Compute_PID()
{
  MOT1_PID.SetTunings(kp, ki, kd);
  MOT1_PID.Compute();

  MOT2_PID.SetTunings(kp, ki, kd);
  MOT2_PID.Compute();

  MOT3_PID.SetTunings(kp, ki, kd);
  MOT3_PID.Compute();
}
// ================================================================
