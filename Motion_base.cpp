// Driver headers
#include <A4988.h> //stepper up to 1:16
#include <DRV8825.h> //stepper up to 1:32
#include <DRV8834.h> //low voltage stepper up to 1:32
#include <DRV8880.h> //stepper up to 1:16, with current/torque control
#include <MultiDriver.h> //multi-stepper control
#include <SyncDriver.h> //synchronized multi-stepper control
#include <math.h> //math lib
#include <TimeLib.h>

// Motion_base header
#include "Motion_base.hpp"

// Dimension
#define RAYON_ROUE 47 //en mm
#define RAYON_ROBOT 72 //en mm
#define NBSTEPS 200
#define RPM 10
#define MICROSTEPS 1 //manual micro-stepping set

// Functions

Motion_base::Motion_base(
  short rightStepperMovementDirectionPinId, 
  short rightStepperPinId, 
  short leftStepperMovementDirectionPinId, 
  short leftStepperPinId, 
  short initialXPos, 
  short initialYPos, 
  double initialAngle
  ){

  //coords
  xPos = initialXPos;
  yPos = initialYPos;
  angle = initialAngle;

  //steppers
  *right = BasicStepperDriver(NBSTEPS, rightStepperMovementDirectionPinId, rightStepperPinId);
  *left = BasicStepperDriver(NBSTEPS, leftStepperMovementDirectionPinId, leftStepperPinId);

  //controller
  *controller = SyncDriver(*right, *left);

  //time
  startTime = 0;
  currentTime = now();

  //last
  lastMovement = NONE;
  lastParam = 0; 
  lastStepParam = 0;
  
  /*gestion physique du microstepping*/
  
  right->begin(RPM,MICROSTEPS);
  left->begin(RPM,MICROSTEPS);
}

short Motion_base::getXPos(void){
  return xPos;
}

short Motion_base::getYPos(void){
  return yPos;
}

double Motion_base::getAngle(void){
  return angle;
}

/*
 * move the given distance straight, positive for moving forward, negative for moving backward
 */

void Motion_base::moveStraight(short d){ //distance en mm
  
  /*gestion physique du microstepping*/
  
  const short steps = d * NBSTEPS/2 * M_PI * RAYON_ROUE;
  controller->startMove(steps,steps); 

  //registering the time when the movement started
  startTime=now();

  //registering the movement as the last movement
  lastMovement = STRAIGHT;
  lastParam = d;
  lastStepParam = steps;

  //calcul of the new coords
  xPos += (short)(d * cos(angle));
  yPos += (short)(d * sin(angle));
  
}

/*
 * rotate the given angle, positive to rotate in the trigonometric way, negative to rotate clockwise
 */

void Motion_base::rotate(double rad){
  
  /*gestion physique du micro-stepping*/
  
  const short steps = rad * RAYON_ROBOT * NBSTEPS/2 * M_PI * RAYON_ROUE;
  controller->startMove(steps,-steps);

  //registering the time when the movement started
  startTime=now();

  //registering the movement as the last movement
  lastMovement = ROTATION;
  lastParam = rad;
  lastStepParam = steps;

  //calcul of the new coords
  angle += rad;
  
}

/*
 * stop the current movement and recalculate position
 */

void Motion_base::interruptMovement(void) {
  
  if(lastMovement != NONE){ //there has been at least one movement

    right->stop();		//meh
	left->stop();
    updateCoords();
	
  }
  
}

void Motion_base::updateCoords(){

  currentTime=now();
  const BasicStepperDriver::State rightState = right->getCurrentState(); //right and left are the same

  if(rightState != BasicStepperDriver::STOPPED){ //the movement is not yet finished

    //get the time needed for the movement
    const long neededTime = right->getTimeForMove(lastParam);
    
    if(lastMovement == STRAIGHT){

      const time_t remainingTime = startTime + neededTime - currentTime;
      const short notTravelledDistance = (short)(remainingTime/neededTime * lastParam);

      //calcul of the new coords
      xPos -= notTravelledDistance * cos(angle);
      yPos -= notTravelledDistance * sin(angle);
      
    }

    if(lastMovement == ROTATION){

      const time_t remainingTime = currentTime - startTime;
      const double notRotatedAngle = remainingTime/neededTime * lastParam;

      //calcul of the new coords
      angle -= notRotatedAngle;
      
    }

  }
  
}

void Motion_base::goToCoords(short finalXPos, short finalYPos, double finalAngle){

  const short deltaX = finalXPos-xPos;
  const short deltaY = finalYPos-yPos;

  //gestion de  la position
  if(deltaX != 0 || deltaY != 0){ // not null movement
    
    if(deltaX == 0){ // only y movement
      rotate(M_PI-angle);
      moveStraight(deltaY);
      
    }
    
    else{
      
      if(deltaY == 0){ // only y movement
        rotate(angle);
        moveStraight(deltaX);
       
      }
      
      else{ //movement on both axis
        
        const double tmpAngle = atan((deltaY)/(deltaX)); //angle for optimal deplacement
        rotate(tmpAngle-angle); 
        
        moveStraight(sqrt(deltaX*deltaX+deltaY*deltaY));
  
      }
      
    }
    
  } 

  const double deltaAngle = finalAngle-angle;
  
  //gestion de l'angle
  if(deltaAngle != 0){
    rotate(deltaAngle);
  }
  
}



