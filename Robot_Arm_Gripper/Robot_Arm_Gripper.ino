#include "Gripper.h"
#include "Joint.h"

// motor variables
const int dirPin_1 = 29;
const int stepPin_1 = 28;

const int dirPin_2 = 41;
const int stepPin_2 = 40;

const int dirPin_3 = 35;
const int stepPin_3 = 34;

#define motorInterfaceType 1

const int powerPin = 53;

// gripper variables
const int feedbackPin = A0;
const int gripperPin = 22;

// object initiation
Gripper gripper(gripperPin, feedbackPin);
Joint joint1(motorInterfaceType, stepPin_1, dirPin_1);
Joint joint2(motorInterfaceType, stepPin_2, dirPin_2);
Joint joint3(motorInterfaceType, stepPin_3, dirPin_3);

void setup() {

    // serial communication
    Serial.begin(115200);

    // turn on power
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, HIGH);

    // turn on motors
    joint1.setup();
    joint1.setSpeed(1000);
    // joint2.setup();
    // joint2.setSpeed(1000);
    // joint3.setup();
    // joint3.setSpeed(1000);

    // turn on gripper
    gripper.setup();
}

// initial desired position
int j1_desiredPos = 0;
int j2_desiredPos = 0;
int j3_desiredPos = 0;
int gripper_desiredPos = 180;

void loop() {

    // send serial command in the format 180, 180, 180, 180
    if (Serial.available() > 0) {
      
      String receivedData = Serial.readStringUntil('\n');
      
      int values[4];
      int index = 0;
      char *ptr = strtok(const_cast<char *>(receivedData.c_str()), ",");
      
      while (ptr != nullptr && index < 4) {
        values[index] = atoi(ptr);
        index++;
        ptr = strtok(nullptr, ",");
      }

      for (int i = 0; i < 4; i++){

        if (i < 3){
          if (values[i] >= -90 && values[i] <= 90){}
          else{ 
            Serial.println("Warning: joints values should be from -90 to 90");
            break; 
          }
        }

        if (i == 3){
          if (values[3] >= 0 && values[3] <= 180){
            
            j1_desiredPos = float(values[0] / 180.0) * 10000;
            j2_desiredPos = float(values[1] / 180.0) * 10000;
            j3_desiredPos = float(values[2] / 180.0) * 10000;
            gripper_desiredPos = values[3];   

            gripper.moveTo(90);

            Serial.print("Joint1: ");
            Serial.print(j1_desiredPos);
            Serial.print("  Joint2: ");
            Serial.print(j2_desiredPos);
            Serial.print("  Joint3: ");
            Serial.print(j3_desiredPos);
            Serial.print("  Gripper: ");
            Serial.println(gripper_desiredPos);
          }
          else{ 
            Serial.println("Warning: gripper values should be from 0 to 180");
            break; 
          }
        }
      }
    }

    // int pos = gripper.readPos();
    // Serial.print("Analog Reading: ");
    // Serial.println(pos);

    // motor the gripper and joints
    joint1.moveTo(j1_desiredPos);
    // joint2.moveTo(j2_desiredPos);
    // joint3.moveTo(j3_desiredPos);

    if (joint1.noDistToGo() && joint2.noDistToGo() && joint3.noDistToGo()){
      gripper.moveTo(180);
    }
}