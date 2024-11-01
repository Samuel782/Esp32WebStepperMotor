#include "stepper.h"

const int DIR = 12;
const int STEP = 14;

const int steps_per_rev = 200;

void setupStepper()
{
    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
}

void spinClockwise(int rotations) {
    digitalWrite(DIR, HIGH); 
    for (int i = 0; i < steps_per_rev * rotations; i++) {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(2000);
        digitalWrite(STEP, LOW);
        delayMicroseconds(2000);
    }
}

void spinAntiClockwise(int rotations) {
    digitalWrite(DIR, LOW);  
    for (int i = 0; i < steps_per_rev * rotations; i++) {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(2000);
        digitalWrite(STEP, LOW);
        delayMicroseconds(2000);
    }
}