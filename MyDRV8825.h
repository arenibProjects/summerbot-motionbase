/*
 * DRV8825.h hack to get the remaining steps
 */
#ifndef MYDRV8825_H
#define MYDRV8825_H
#include <Arduino.h>
#include "src/StepperDriver/src/DRV8825.h"

class MyDRV8825 : public DRV8825 {

public:
    MyDRV8825(short steps, short dir_pin, short step_pin)
    :DRV8825(steps,dir_pin, step_pin){};
    MyDRV8825(short steps, short dir_pin, short step_pin, short enable_pin)
    :DRV8825(steps, dir_pin, step_pin, enable_pin){};
    MyDRV8825(short steps, short dir_pin, short step_pin, short mode0_pin, short mode1_pin, short mode2_pin)
    :DRV8825(steps, dir_pin, step_pin, mode0_pin, mode1_pin, mode2_pin){};
    MyDRV8825(short steps, short dir_pin, short step_pin, short enable_pin, short mode0_pin, short mode1_pin, short mode2_pin)
    :DRV8825(steps, dir_pin, step_pin, enable_pin, mode0_pin, mode1_pin, mode2_pin){};
    long getRemainingSteps(){
      return steps_remaining;
    }
};
#endif // MYDRV8825_H
