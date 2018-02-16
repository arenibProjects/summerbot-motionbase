#ifndef MOTIONBASE_H
#define MOTIONBASE_H
 
#include <Arduino.h>
#include "src/StepperDriver/DRV8825.h"
#include "src/StepperDriver/DoubleDriver.h"
#define Motor DRV8825
 
#define STEP_PER_REVOLUTION 200
#define RPM 240
#define MOTOR_ACCEL 100
#define MOTOR_DECEL 100
#define TRANSLATION_MICROSTEPS 4 //micro-steps while moving in straight line
#define ROTATION_MICROSTEPS 16 //micro-steps while rotating
class Move{
    public:
        bool isRotation_,direction_;
        long steps_;
        Move* next_=0;
        Move(bool isRotation,bool direction,long steps):isRotation_{isRotation},direction_{direction},steps_{steps}{};
        Move* getNext(){
            return next_;
        }
        Move* getLast(){
            if(next_) return next_->getLast();
            else return this;
        }
        void append(Move* nn){
            if(next_){
                next_->append(nn);
            }else{
                next_ = nn;
            }
        };
        void clear(){
            if(next_){
                next_->clear();
                delete next_;
            }
        }
        String toString(){
          return "|"+String(isRotation_)+","+String(direction_)+","+String(steps_)+">";
        }
};
 
class MotionBase{
    private:
        double prevX_,prevY_,prevA_;
        double lastMoveX_,lastMoveY_,lastMoveA_;
        bool paused_ = false;
        bool motionStarted_ = false;
        Move *moves_=(Move*)0;//chained list
        Motor *left_=(Motor*)0, *right_=(Motor*)0;
        DoubleDriver *driver_=(DoubleDriver*)0;
        double wheelRadius_,robotRadius_;
    public:
        MotionBase(Motor* left, Motor* right,double wheelRadius,double robotRadius,double x=0,double y=0,double a=0)
        :left_{left},right_{right},wheelRadius_{wheelRadius},robotRadius_{robotRadius},prevX_{x},prevY_{y},prevA_{a}{
          driver_ = new DoubleDriver(right_, left_);
          right_->begin(RPM);
          left_->begin(RPM);
          right_->setSpeedProfile(right_->LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
          left_->setSpeedProfile(left_->LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
          driver_->setMicrostep(TRANSLATION_MICROSTEPS);
        };
        // --- moves management ---
        void nextMove();
        void clearMoves();
        void computeMoveCoords(double ix,double iy,double ia,Move* mv,double* ox, double* oy, double* oa);
        void computeMoveCoords(Move* mv,double* ox, double* oy, double* oa);
        void computeLastMoveCoords();
        String movesString();
        // --- moves creators ---
        void translate(double distance);
        void rotate(double rotation);
        void moveTo(double x,double y,double a);
        // ---  ---
        bool update();
        void pause();
        void resume();

        void setPosition(double x,double y,double a);
};
#endif
