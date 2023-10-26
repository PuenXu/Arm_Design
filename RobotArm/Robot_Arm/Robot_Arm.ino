// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 39;
const int stepPin = 38;

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void motorInit(){
  myStepper.setMaxSpeed(1000);
	myStepper.setAcceleration(300);
}

void motorSetSpeed(int speed){
	myStepper.setSpeed(speed);
}

void moveTo(int desiredPos){
	// Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) {

      myStepper.moveTo(desiredPos);
      Serial.print("desiredPos: ");
      Serial.println(desiredPos);
  }

	// Move the motor one step
	myStepper.run();
}

void moveToSerial(){
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

void setup() {
  Serial.begin(115200);
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
  motorInit();
  motorSetSpeed(500);
  moveTo(2000);

}

void loop() {
  moveToSerial();
}






// -----------------------------------------
// // Include the AccelStepper Library
// #include "Joint.h"

// // Define pin connections
// const int motor1_dirPin = 39;
// const int motor1_stepPin = 38;
// int stepsPerRevolution = 200;  // Replace with your motor's steps per revolution

// Joint joint1(motor1_dirPin, motor1_stepPin, stepsPerRevolution);

// void setup() {

//   Serial.begin(115200);

// 	joint1.setSpeed(300);
// }

// void loop() {
//   joint1.moveTo();
// }