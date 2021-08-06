#include "line-follower.h"
int statusCar = 0; // default 0 

void setup() {
    
  // set pin for motor and sensor
    pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
    pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
    pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
    pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
    pinMode(linesens1, INPUT);//Set chân cảm biến 1 là input
    pinMode(linesens2, INPUT);//Set chân cảm biến 2 là input
    pinMode(linesens3, INPUT);//Set chân cảm biến 3 là input
}

void loop() {
 darkLineFollower (inB1, inB2, inA1, inA2, linesens1, linesens2, linesens3);
}

void darkLineFollower (byte inR1, byte inR2, byte inL1, byte inL2, byte sen1, byte sen2, byte sen3)
{
  switch (deviationDarkLine3Sensor (sen1, sen2, sen3))
  {
    case -1:
      robotMover( inR1, inR2, inL1, inL2, 1);// rẽ phải
      break;
    case -2:
      robotMover( inR1, inR2, inL1, inL2, 1);
      break;
    case 1:
      robotMover( inR1, inR2, inL1, inL2, -1);// rẽ trái
      break;
    case 2:
      robotMover( inR1, inR2, inL1, inL2, -1);
      break;
    case 0:
      robotMover( inR1, inR2, inL1, inL2, 0);// tiến thẳng
      break;
  }
  
}
void robotMover (byte inR1, byte inR2, byte inL1, byte inL2, byte action)
{
  /*
  inR1 inR2 là 2 chân tín hiệu động cơ bên phải
  inL1 inL2 là 2 chân tín hiệu động cơ bên trái
  action =0 đi thẳng
  action =-1 rẽ trái
  action =1 rẽ phải

  */
  switch (action)
  {
    case 0://đi thẳng
      motorControlWithSpeed(inR1, inR2, 1, 128, 128);
      motorControlWithSpeed(inL1, inL2, 1, 128, 128);
      break;
    case -1:// rẽ trái
      motorControlWithSpeed(inR1, inR2, 1, 0, 150);
      motorControlWithSpeed(inL1, inL2, 0, 128, 0); //weak momentum
      break;
    case 1:// rẽ phải
      motorControlWithSpeed(inR1, inR2, 2, 0, 128);
      motorControlWithSpeed(inL1, inL2, 1, 150, 0);
      break;
    default:
      action = 0;
  }
}

void motorControlWithSpeed (byte in1, byte in2, byte direct, int spdA, int spdB)
{
  switch (direct)
  {
    case 0:
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
    case 1:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      if(spdA != 0) analogWrite(enA, spdA);
      if(spdB != 0) analogWrite(enB, spdB);
      
      break;
    case 2:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      if(spdA != 0) analogWrite(enA, spdA);
      if(spdB != 0) analogWrite(enB, spdB);
      break;
  }
}

int deviationDarkLine3Sensor (int PinNumb1, int PinNumb2, int PinNumb3)
{
  
  int left = digitalRead (PinNumb1)+digitalRead (PinNumb2); //kiểm tra mấy cảm biến trái ở trong màu đen
  int right= digitalRead (PinNumb2)+digitalRead (PinNumb3); //kiểm tra mấy cảm biến phải ở trong màu đen

  if ((left!=0) || (right!=0))
  {  
    statusCar = left - right;
  }
  return statusCar;
}
