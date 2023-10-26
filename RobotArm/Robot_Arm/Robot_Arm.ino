// #include "Joint.h"

// // Define the number of steps per revolution and motor pins
// int stepsPerRevolution = 200;  // Replace with your motor's steps per revolution
// int motor1_dirPin = 39;  // Replace with your motor's pin 1
// int motor1_stepPin  = 38;  // Replace with your motor's pin 2

// Joint joint1(motor1_dirPin, motor1_stepPin, stepsPerRevolution);

// void setup() {

// }

// void loop() {
//     // main loop code here
//         // Rotate the stepper motor
//     joint1.move(100);  // Rotate 100 steps
//     delay(500);
// }

// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 39;
const int stepPin = 38;

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
    Serial.begin(115200);
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
	myStepper.setMaxSpeed(1000);
	myStepper.setAcceleration(50);
	myStepper.setSpeed(500);
}

void loop() {
	// Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) {
		  if(Serial.available()){ 
        int desiredPos = Serial.parseInt();
        myStepper.moveTo(desiredPos);
        Serial.print("desiredPos: ");
        Serial.println(desiredPos);
      }
  }

	// Move the motor one step
	myStepper.run();
}