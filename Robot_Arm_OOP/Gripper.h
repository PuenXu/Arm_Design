#ifndef GRIPPER_H
#define GRIPPER_H

#include <Servo.h>

class Gripper {
public:
    Gripper(int gripperPin, int feedbackPin);
    void setup();
    void moveTo(int desiredPos);
    int readPos();

private:
    Servo servo;
    int gripperPin;
    int feedbackPin;
};

#endif