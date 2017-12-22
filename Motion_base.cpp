// Driver headers
#include <A4988.h> //stepper up to 1:16
#include <DRV8825.h> //stepper up to 1:32
#include <DRV8834.h> //low volateg stepper up to 1:32
#include <DRV8880.h> //stepper up to 1:16, with current/torque control
#include <MultiDriver.h>
#include <SyncDriver.h>

// Base Roulante header
#include "Motion_base.hpp"

#define MATH_PI 3.14159265359

// Dimensionnement
#define RAYON_ROUE 47 //en mm
#define RAYON_ROBOT 72 //en mm
#define NBSTEPS 200
#define RPM 10
#define MICROSTEPS 1 //manual microstepping set

// Fonctions
Motion_base::Motion_base(short rightStepperMovementDirectionPinId, short rightStepperPinId, short leftStepperMovementDirectionPinId, short leftStepperPinId){
  *right = BasicStepperDriver(NBSTEPS, rightStepperMovementDirectionPinId, rightStepperPinId);
  *left = BasicStepperDriver(NBSTEPS, leftStepperMovementDirectionPinId, leftStepperPinId);
  *controller = SyncDriver(*right, *left);
  /*gestion du microstepping*/
  right->begin(RPM,MICROSTEPS);
  left->begin(RPM,MICROSTEPS);
}

void Motion_base::moveForward(short d){ //distance en mm
  /*gestion du microstepping*/
  const short steps = d*NBSTEPS/2*MATH_PI*RAYON_ROUE;
  controller->move(steps,steps); 
}

void Motion_base::rotate(short rad){
  /*gestion du microstepping*/
  const short steps = rad*RAYON_ROBOT*NBSTEPS/2*MATH_PI*RAYON_ROUE;
  controller->move(steps,steps);
  
}
