#include <Arduino.h>
#include "./header/MyMotor.h" 
#include "./header/MyEncoder.h"
#include "./header/MyPID.h"
#include "./header/MySerial.h"

void setup()
{
  Init_Motor();
  Init_Encoder();
  Init_PID();
  Init_Serial();
}

void loop()
{
  Get_Angle();
  Compute_PID(); 
  Run_Motor();
  SerialDataPrint();
  SerialDataWrite();
}
