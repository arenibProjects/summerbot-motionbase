/*
 * Double Stepper Motor Bundler
 * 
 * By Titouan Baillon for ARENIB
 * Based on work from Laurentiu Badea
 */
#ifndef SYNC_DRIVER_H
#define DOUBLE_DRIVER_H
#include <Arduino.h>
#include "DRV8825.h"
#define Motor DRV8825

class DoubleDriver{
protected:
    unsigned short count;
    Motor *motors[2]={(Motor*)0,(Motor*)0};

public:
    DoubleDriver(Motor* motor1, Motor* motor2)
    :count(2)
    {
      motors[0]=motor1;
      motors[1]=motor2;
    };

    void asyncMove(long steps1, long steps2);
    long update(void);
    void setMicrostep(unsigned microsteps);
    void enable(void);
    void disable(void);
    bool isRunning(void);
    void startBrake(void);
};
#endif // DOUBLE_DRIVER_H
