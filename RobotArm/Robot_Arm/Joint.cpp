// #include "Joint.h"

// Joint::Joint(int stepsPerRevolution, int motorPin1, int motorPin2, int motorPin3, int motorPin4)
//     : stepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4) {
//       this->stepsPerRevolution = stepsPerRevolution;
// }

// void Joint::setSpeed(float rpm) {
//     stepper.setSpeed(rpm);
// }

// void Joint::rotateAngle(int angle) {
//     int gearRatio = 80;
//     int steps = angle / 360 * 80 * this->stepsPerRevolution;
//     stepper.step(steps);

//     this->currentAngle += angle;
// }

// void Joint::moveTo(int targetAngle) {
//     int angleToTurn = targetAngle - this->currentAngle;
//     rotateAngle(angleToTurn);
// }

#include "Joint.h"

Joint::Joint(int dirPin, int stepPin, int stepsPerRevolution)
    : stepper(1, dirPin, stepPin) {
    this->stepsPerRevolution = stepsPerRevolution;
    stepper.setMaxSpeed(1000); // Set your desired maximum speed in steps per second
    stepper.setAcceleration(50); // Set your desired acceleration in steps per second^2
}

void Joint::setSpeed(float rpm) {
    stepper.setSpeed(rpm);
}

void Joint::moveTo() {
    // stepper.moveTo(position);
    // while (stepper.run()) {
    //     // Run the stepper motor
    // }
    	// Change direction once the motor reaches target position
	if (stepper.distanceToGo() == 0) {
		  if(Serial.available()){ 
        int desiredPos = Serial.parseInt();
        stepper.moveTo(desiredPos);
        Serial.print("desiredPos: ");
        Serial.println(desiredPos);
      }
  }

	// Move the motor one step
	stepper.run();
}

// void Joint::moveToDeg(int angle) {
//     int gearRatio = 80;
//     int position = angle / 360 * this->stepsPerRevolution * gearRatio;
//     stepper.moveTo(position);
//     while (stepper.run()) {
//         // Run the stepper motor
//     }
// }