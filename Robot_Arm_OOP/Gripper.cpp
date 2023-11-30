#include "Gripper.h"
#include "Arduino.h"

Gripper::Gripper(int gripperPin, int feedbackPin) : gripperPin(gripperPin), feedbackPin(feedbackPin) {}

void Gripper::setup(){
    servo.attach(gripperPin);
}

void Gripper::moveTo(int desiredPos) {
    servo.write(desiredPos);
}

int Gripper::readPos(){
    int pos = analogRead(feedbackPin); 
    return pos;
}