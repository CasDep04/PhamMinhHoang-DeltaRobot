#include <Arduino.h>
#include "./header/MyMotor.h" 
#include "./header/MyEncoder.h"
#include "./header/MyPID.h"
#include "./header/MySerial.h"
#include "./wifi/myWifi.h"
#include "./controller/controlMotor.h"

void setup()
{
  Init_Motor();
  Init_Encoder();
  Init_PID();
  Init_Serial();

  webApp_init();
}

void loop()
{
  Get_Angle();
  Compute_PID(); 
  Run_Motor();
  SerialDataPrint();  

  updateMotorPositions();

  //web app
  handleClient();

}
