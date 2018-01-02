#ifndef MOTION_BASE
#define MOTION_BASE 1

class Motion_base {
  
  public : 
    Motion_base(
      short rightStepperMovementDirectionPinId, 
      short rightStepperPinId, 
      short leftStepperMovementDirectionPinId, 
      short leftStepperPinId, 
      short initialXpos, 
      short initialYPos,
      double initialAngle
      );
    void moveStraight(short d);
    void rotate(double rad);
    void goToCoords(short finalXpos, short finalYPos, double finalAngle);
    
  private : 
    short xPos;
    short yPos;
    double angle;
    BasicStepperDriver *right;
    BasicStepperDriver *left;
    SyncDriver *controller;
    
};

#endif
