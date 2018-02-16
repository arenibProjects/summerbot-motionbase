#include <Arduino.h>
#include "src/StepperDriver/DRV8825.h"
#include "MotionBase.h"
DRV8825* right=new DRV8825(200, 31, 29, 26, 25, 24);
DRV8825* left =new DRV8825(200, 32, 30, 26, 25, 24);
MotionBase mb(left,right,33,63);
int r = 0;
void setup (){
<<<<<<< HEAD
  //Timer
  motionTimer.begin(motionLoop,1000);// 1kHz (1000 is the period in microS)
  motionTimer.priority(1); //slightly above normal
  
  //Serial
=======
>>>>>>> parent of 19af5dd... test sketch conversion to IntervalTimer
  Serial.begin(250000);
  delay(5000);
  Serial.println("Start");
  mb.moveTo(100,100,3.141592/2);
  Serial.println(mb.movesString());
}

void loop (){
  /*if(r>100){
    Serial.println(mb.movesString());
    Serial.println(right->getRemainingSteps());
    r=0;
  }*/
	mb.update();
  r++;
}
