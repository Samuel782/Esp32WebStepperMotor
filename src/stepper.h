#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

void setupStepper();

void spinClockwise(int rotations);

void spinAntiClockwise(int rotations);

#endif
