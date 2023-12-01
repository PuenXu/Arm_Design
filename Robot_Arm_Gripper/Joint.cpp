#include "Joint.h"

Joint::Joint(int motorInterfaceType, int stepPin, int dirPin) : stepper(motorInterfaceType, stepPin, dirPin) {}

void Joint::setup() {
    stepper.setMaxSpeed(2000);
    stepper.setAcceleration(500);
}

void Joint::setSpeed(int desiredSpeed){
    stepper.setSpeed(desiredSpeed);
}

void Joint::move(int desiredSteps) {
    if (stepper.distanceToGo() == 0) {
        stepper.move(desiredSteps);
    }
    stepper.run();
}

void Joint::moveTo(int desiredPos) {
    if (stepper.distanceToGo() == 0) {
        stepper.moveTo(desiredPos);
    }
    stepper.run();
}

void Joint::moveToSerial() {
    if (stepper.distanceToGo() == 0) {
        if (Serial.available()) {
            int desiredPos = Serial.parseInt();
            stepper.moveTo(desiredPos);
        }
    }
    stepper.run();
}

bool Joint::noDistToGo(){

    bool noDist = stepper.distanceToGo() == 0;
    return noDist;
}