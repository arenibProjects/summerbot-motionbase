/*
 * Synchronous Multi-motor group driver
 * All motors reach their target at the same time.
 *
 * Copyright (C)2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include "DoubleDriver.h"
#include <Arduino.h>

#define FOREACH_MOTOR(action) for (short i=count-1; i >= 0; i--){action;}

/*
 * Initialize motor parameters
 */
void DoubleDriver::asyncMove(long steps1, long steps2){
    long steps[2] = {steps1, steps2};
    FOREACH_MOTOR(
        if (steps[i]){
            motors[i]->asyncMove(steps[i]);
        };
    );
}

long DoubleDriver::update(void){
    FOREACH_MOTOR(
        motors[i]->update();
    );
    return isRunning();
}
void DoubleDriver::startBrake(void){
    FOREACH_MOTOR( motors[i]->startBrake());
}
bool DoubleDriver::isRunning(void){
    bool running = false;
    FOREACH_MOTOR(
        if (motors[i]->getCurrentState() != Motor::STOPPED){
            running = true;
            break;
        }
    )
    return running;
}
void DoubleDriver::setMicrostep(unsigned microsteps){
    FOREACH_MOTOR(motors[i]->setMicrostep(microsteps));
}

void DoubleDriver::enable(void){
    FOREACH_MOTOR(motors[i]->enable());
}
void DoubleDriver::disable(void){
    FOREACH_MOTOR(motors[i]->disable());
}