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
    Motor* const *motors;

public:
    DoubleDriver(const unsigned short count, Motor* const *motors)
    :count(count), motors(motors)
    {};
    DoubleDriver(Motor* motor1, Motor* motor2)
    :DoubleDriver(2, new Motor* const[2]{motor1, motor2})
    {};

    void asyncMove(long steps1, long steps2);
    long update(void);
    void setMicrostep(unsigned microsteps);
    void enable(void);
    void disable(void);
    bool isRunning(void);
    void startBrake(void);
};
#endif // DOUBLE_DRIVER_H
