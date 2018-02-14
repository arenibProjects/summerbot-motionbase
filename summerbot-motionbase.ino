#include <Arduino.h>
#include "src/StepperDriver/DRV8825.h"
#include "MotionBase.h"
IntervalTimer motionTimer;
DRV8825* right=new DRV8825(200, 31, 29, 26, 25, 24);// steps per rev,dir pin, step pin, mode pin 0, mode pin 1, mode pin 2
DRV8825* left =new DRV8825(200, 32, 30, 26, 25, 24);
MotionBase mb(left,right,33,63); // left motor, right motor, wheel radius, robot radius, x, y, a
int r = 0;
void setup (){
  //Timer
  motionTimer.begin(motionLoop,1000);// 1kHz (1000 is the period in microS)
  motionTimer.priority(129); //slightly above normal
  
  //Serial
  Serial.begin(250000);
  
  //Test move
  delay(1000);
  Serial.println("Start");
  mb.moveTo(100,100,3.141592/2); //move diagonaly to x=100 y=100 then turn to a=90deg
  Serial.println(mb.movesString()); //should be 3 moves
}

void loop (){
  //Debug display
  /*if(r>1000){
    Serial.println(mb.movesString());
    Serial.println(right->getRemainingSteps());
    r=0;
  }
  r++;*/
}
void motionLoop(){
  mb.update();
}

