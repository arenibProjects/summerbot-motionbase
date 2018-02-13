#include <Arduino.h>
#include "MyDRV8825.h"
#include "MotionBase.h"
MyDRV8825* right=new MyDRV8825(200, 31, 29, 26, 25, 24);
MyDRV8825* left =new MyDRV8825(200, 32, 30, 26, 25, 24);
MotionBase mb(left,right,33,63);
int r = 0;
void setup (){
  Serial.begin(250000);
  delay(5000);
  Serial.println("Start");
  mb.translate(1000);
  mb.rotate(1000);
  Serial.println(mb.movesString());
}

void loop (){
  if(r>100){
    Serial.println(mb.movesString());
    Serial.println(right->getRemainingSteps());
    r=0;
  }
	mb.update();
  r++;
}
