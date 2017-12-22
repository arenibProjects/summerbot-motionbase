#ifndef MOTION_BASE
#define MOTION_BASE 1

class Motion_base {
  
  public : 
    Motion_base(short rightStepperMovementDirectionPinId, short rightStepperPinId, short leftStepperMovementDirectionPinId, short leftStepperPinId);
    void moveForward(short d);
    void rotate(short rad);
    
  private : 
    short posx;
    short posy;
    short posangle;
    BasicStepperDriver *right;
    BasicStepperDriver *left;
    SyncDriver *controller;
    
};

#endif
