// #ifndef Joint_h
// #define Joint_h

// #include <Stepper.h>

// class Joint {
  
//   private:
//       Stepper stepper;
//       int stepsPerRevolution;
//       int currentAngle = 0;

//   public:
//       Joint(int stepsPerRevolution, int motorPin1, int motorPin2, int motorPin3, int motorPin4);
//       void setSpeed(float rpm);
//       void rotateAngle(int angle);
//       void moveTo(int angle);
// };

// #endif

#ifndef JOINT_H
#define JOINT_H

#include <AccelStepper.h>

class Joint {
public:
  Joint(int dirPin, int stepPin, int stepsPerRevolution);
  void setSpeed(float rpm);
  void move(int steps);
  void moveTo(int position);
  void moveToDeg(int angle);

private:
  AccelStepper stepper;
  int stepsPerRevolution;
};

#endif