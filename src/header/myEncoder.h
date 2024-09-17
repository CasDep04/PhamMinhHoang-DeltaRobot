#include <Arduino.h>

//red in, white out
#define ENC1_A 4    // green wire
#define ENC1_B 16   // yellow wire 

#define ENC2_A 22    //green wire
#define ENC2_B 23   // yellow wire 

#define ENC3_A 27    // green wire
#define ENC3_B 32   // yellow wire 
#define ENC_RES 330 // Encoder resolution*Gearbox ratio: 11*30

volatile long int encoderCount1 = 0; // Volatile as it changed during interrupt
double encoderDegree1 = 0;             // Position angle in degrees

volatile long int encoderCount2 = 0; 
double encoderDegree2 = 0;             

volatile long int encoderCount3 = 0; 
double encoderDegree3 = 0;    
   
//================================================================================
void readEncoder1()
{
    int b = digitalRead(ENC1_B);
    encoderCount1 = (b > 0) ? (encoderCount1 + 1) : (encoderCount1 - 1);
}

void readEncoder2()
{
    int b = digitalRead(ENC2_B);
    encoderCount2 = (b > 0) ? (encoderCount2 + 1) : (encoderCount2 - 1);
}

void readEncoder3()
{
    int b = digitalRead(ENC1_B);
    encoderCount2 = (b > 0) ? (encoderCount2 + 1) : (encoderCount2 - 1);
}
void Init_Encoder()
{
    pinMode(ENC1_A, INPUT);
    pinMode(ENC1_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC1_A), readEncoder1, RISING);

    pinMode(ENC2_A, INPUT);
    pinMode(ENC2_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC2_A), readEncoder2, RISING);

    pinMode(ENC3_A, INPUT);
    pinMode(ENC3_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC3_A), readEncoder3, RISING);
}

void Get_Angle()
{
    encoderDegree1 = encoderCount1 * 360 / ENC_RES; // Conversion between encoder count and degree
    encoderDegree2 = encoderCount2 * 360 / ENC_RES;
    encoderDegree3 = encoderCount3 * 360 / ENC_RES;
}