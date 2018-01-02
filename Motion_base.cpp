// Driver headers
#include <A4988.h> //stepper up to 1:16
#include <DRV8825.h> //stepper up to 1:32
#include <DRV8834.h> //low voltage stepper up to 1:32
#include <DRV8880.h> //stepper up to 1:16, with current/torque control
#include <MultiDriver.h> //multi-stepper control
#include <SyncDriver.h> //syncronised multi-stepper control
#include <math.h> //math lib

// Base Roulante header
#include "Motion_base.hpp"

// Dimensionnement
#define RAYON_ROUE 47 //en mm
#define RAYON_ROBOT 72 //en mm
#define NBSTEPS 200
#define RPM 10
#define MICROSTEPS 1 //manual microstepping set

// Fonctions

Motion_base::Motion_base(
  short rightStepperMovementDirectionPinId, 
  short rightStepperPinId, 
  short leftStepperMovementDirectionPinId, 
  short leftStepperPinId, 
  short initialXPos, 
  short initialYPos, 
  double initialAngle
  ){
    
  xPos=initialXPos;
  yPos=initialYPos;
  angle=initialAngle;
  *right = BasicStepperDriver(NBSTEPS, rightStepperMovementDirectionPinId, rightStepperPinId);
  *left = BasicStepperDriver(NBSTEPS, leftStepperMovementDirectionPinId, leftStepperPinId);
  *controller = SyncDriver(*right, *left);
  
  /*gestion physique du microstepping*/
  
  right->begin(RPM,MICROSTEPS);
  left->begin(RPM,MICROSTEPS);
}

/*
 * move the given distance straight, positive for moving forward, negative for moving backward
 */

void Motion_base::moveStraight(short d){ //distance en mm
  
  /*gestion physique du microstepping*/
  
  const short steps = d*NBSTEPS/2*M_PI*RAYON_ROUE;
  controller->move(steps,steps); 
}

/*
 * rotate the given angle, positive to rotate in the trigonometric way, negative to rotate clockwise
 */

void Motion_base::rotate(double rad){
  
  /*gestion physique du microstepping*/
  
  const short steps = rad*RAYON_ROBOT*NBSTEPS/2*M_PI*RAYON_ROUE;
  controller->move(steps,-steps);
  
}

void Motion_base::goToCoords(short finalXPos, short finalYPos, double finalAngle){

  const short deltaX = finalXPos-xPos;
  const short deltaY = finalYPos-yPos;

  //gestion de  la position
  if(deltaX != 0 || deltaY != 0){ // not null movement
    
    if(deltaX == 0){ // only y movement
      rotate(M_PI-angle);
      moveStraight(deltaY);
      
      //update of the Y pos
      yPos = finalYPos; 
    }
    
    else{
      
      if(deltaY == 0){ // only x movement
        rotate(angle);
        moveStraight(deltaX);
        
        //update of the X pos
        xPos = finalXPos; 
      }
      
      else{ //movement on both axis
        
        const double tmpAngle = atan((deltaY)/(deltaX)); //angle for optimal deplacement
        rotate(tmpAngle-angle); 
        
        //update of the current angle
        angle = tmpAngle; 
        
        moveStraight(sqrt(deltaX*deltaX+deltaY*deltaY));
        
        //update of the current position
        xPos = finalXPos;
        yPos = finalYPos;
      }
      
    }
    
  } 

  const double deltaAngle = finalAngle-angle;
  
  //gestion de l'angle
  if(deltaAngle != 0){
    rotate(deltaAngle);
    angle = finalAngle;
  }
  
}

