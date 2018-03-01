//#include <Arduino.h>
#include "DualDRV8825.h"
#include "MotionBase.h"
IntervalTimer motionTimer;
DualDRV8825* dd=new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);// steps per rev,left dir pin, left step pin, right dir pin, right step pin, mode pin 0, mode pin 1, mode pin 2
MotionBase mb(dd,33,63); // motors, wheel radius, robot radius, x, y, a
int r = 0;
void setup (){
  //Timer
  motionTimer.begin(motionLoop,100);// 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal
  
  //Serial
  Serial.begin(9600);
  
  //Test move
  delay(5000);
  Serial.println("Test");
  /*for(int i = 0 ; i < 3 ; i ++){
    digitalWrite(30,HIGH);
    digitalWrite(29,HIGH);
    delay(1);
    digitalWrite(30,LOW);
    digitalWrite(29,LOW);
    delay(5);
  }*/
  delay(100);
  Serial.println("Start");
  mb.moveTo(100,100,3.141592/2); //move diagonaly to x=100 y=100 then turn to a=90deg
  Serial.println(mb.movesString()); //should be 3 moves
}

void loop (){
  //Debug display
  if(r>1000){
    Serial.println(mb.movesString());
    Serial.println(dd->getRemainingSteps());
    r=0;
  }
  r++;
}
void motionLoop(){
  mb.update();
}

