#ifndef JOINT_H
#define JOINT_H

#include <AccelStepper.h>

class Joint {
public:
  Joint(int dirPin, int stepPin, int stepsPerRevolution);
  void setSpeed(float rpm);
  void move(int steps);
  void moveTo(int position);

private:
  AccelStepper stepper;
};

#endif