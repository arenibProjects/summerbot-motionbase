#include "Motion_base.hpp"
#include <Arduino.h>
#include <math.h> //math lib

short rightStepperPinId;
short rightStepperDirectionPinId;
short leftStepperPinId;
short leftStepperDirectionPinId;
short ms1PinId;
short ms2PinId;
short ms3PinId;
short initialXPos;
short initialYPos;
double initialAngle;

void setup (){
	
	rightStepperPinId = 3;
	rightStepperDirectionPinId = 4;
	leftStepperPinId = 5;
	leftStepperDirectionPinId = 6;
	ms1PinId = 7;
	ms2PinId = 8;
	ms3PinId = 9;
	initialXPos = 0;
	initialYPos = 0;
	initialAngle = 0;
	
	Motion_base motion_base(
		rightStepperPinId,
		rightStepperDirectionPinId,
		leftStepperPinId,
		leftStepperDirectionPinId,
		ms1PinId,
		ms2PinId,
		ms3PinId,
		initialXPos,
		initialYPos,
		initialAngle
	);
	
	//some tests
	motion_base.moveStraight(20); //forward 20mm
	delay(10000); //let the base finish the movement
	motion_base.rotate(M_PI*2); //full turn
	delay(10000);
	motion_base.moveStraight(-20); //backward 20mm
	delay(10000);
	
	motion_base.goToCoords(20,20,M_PI);
	delay(5000); //should be to short and cause the interruption of the movement
	motion_base.goToCoords(0,0,0);
	delay(10000);
	
}

void loop (){
	
}