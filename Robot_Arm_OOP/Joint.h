#ifndef JOINT_H
#define JOINT_H

#include <AccelStepper.h>

class Joint {
public:
    Joint(int motorInterfaceType, int stepPin, int dirPin);
    void setup();
    void setSpeed(int desiredSpeed);
    void move(int desiredSteps);
    void moveTo(int desiredPos);
    void moveToSerial();

private:
    AccelStepper stepper;
};

#endif