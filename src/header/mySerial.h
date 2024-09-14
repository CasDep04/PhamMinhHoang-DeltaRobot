#include <Arduino.h>

unsigned long Serial_time = 0; // time in us
extern int sliderValue;
extern int joystickX;
extern int joystickY;

// ====================================================================================
void Init_Serial()
{
  Serial.begin(115200);
  while (!Serial)
    ;
}
// ====================================================================================
void SerialDataPrint()
{
  if (micros() - Serial_time >= 10000)
  {
    Serial_time = micros();
    // For MATLAB
    Serial.print(Serial_time / 10000);
    //Serial.print(",");
    //Serial.print(MOT1_cmd);
    //Serial.print(",");
    //Serial.print(setpointMotor1);
    //Serial.print(",");
    //Serial.print(encoderDegree1);
    //Serial.println();

    // For Teleplot
    // Serial.println(Serial_time / 10000);
    //motor1
     Serial.print(">MOT1_cmd:");
     Serial.println(MOT1_cmd);
     Serial.print(">encoderDegree1:");
     Serial.println(encoderDegree1);
     Serial.print(">setpointMotor1:");
     Serial.println(setpointMotor1);
    
    //motor2
    Serial.print(">MOT2_cmd:");
     Serial.println(MOT2_cmd);
     Serial.print(">encoderDegree2:");
     Serial.println(encoderDegree2);
     Serial.print(">setpointMotor2:");
     Serial.println(setpointMotor2);

    //motor3
    
    Serial.print(">MOT3_cmd:");
     Serial.println(MOT3_cmd);
     Serial.print(">encoderDegree3:");
     Serial.println(encoderDegree3);
     Serial.print(">setpointMotor3:");
     Serial.println(setpointMotor3);

    //slider
    Serial.print(">Slider:");
    Serial.println(sliderValue);

    //joystick
    Serial.print(">JoystickX:");
    Serial.println(joystickX);
    
    Serial.print(">JoystickY:");
    Serial.println(joystickY);

    // Serial.print(">kp:");
    // Serial.println(kp);
    // Serial.print(">ki:");
    // Serial.println(ki);
    // Serial.print(">kd:");
    // Serial.println(kd);
  }
}