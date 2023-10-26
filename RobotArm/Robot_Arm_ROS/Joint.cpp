#include "Joint.h"

Joint::Joint(int dirPin, int stepPin, int stepsPerRevolution)
    : stepper(1, dirPin, stepPin) {
    // You can set other properties here, but not the steps per revolution
    stepper.setMaxSpeed(1000); // Set your desired maximum speed in steps per second
    stepper.setAcceleration(500); // Set your desired acceleration in steps per second^2
}

void Joint::setSpeed(float rpm) {
    stepper.setMaxSpeed(rpm);
}

void Joint::move(int steps) {
    int gearRatio = 80;
    stepper.move(steps * gearRatio);
    while (stepper.run()) {
        // Run the stepper motor
    }
}

void Joint::moveTo(int position) {
    int gearRatio = 80;
    stepper.moveTo(position * gearRatio);
    while (stepper.run()) {
        // Run the stepper motor
    }
}