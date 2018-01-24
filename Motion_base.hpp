#ifndef MOTION_BASE
#define MOTION_BASE 1

class Motion_base {
  
  public : 
  
	//coords struct
	typedef struct {
		double angle;
		short xPos;
		short yPos;
	} Coords;
  
	//builder
    Motion_base(
      short rightStepperMovementDirectionPinId, 
      short rightStepperPinId, 
      short leftStepperMovementDirectionPinId, 
      short leftStepperPinId, 
      short initialXpos, 
      short initialYPos,
      double initialAngle
      );
	  
	//accessors
    Coords getCoords(void);
	
	//movement functions
    void moveStraight(short d);
    void rotate(double rad);
	void interruptMovement(void);
	
	//coords related functions
    void updateCoords(void);
    void goToCoords(short finalXpos, short finalYPos, double finalAngle);
	
	
    
  private : 
  
	//coords
    short xPos, realXPos;
    short yPos, realYPos;
    double angle, realAngle;
	Coords coords;
	
	//steppers
    BasicStepperDriver *right;
    BasicStepperDriver *left;
	
	//controller
	SyncDriver *controller;
	
	//time
    time_t startTime;
    time_t currentTime;
	
	//last system
    enum movement{NONE = 0, STRAIGHT = 1, ROTATION = 2};
    movement lastMovement;
    short lastParam;
    short lastStepParam;
	
};

#endif
