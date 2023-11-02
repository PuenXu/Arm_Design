#include "Joint.h"

#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle node_handle;

std_msgs::UInt16 command_msg;
std_msgs::Bool complete_msg;

const int dirPin_1 = 39;
const int stepPin_1 = 38;

const int dirPin_2 = 29;
const int stepPin_2 = 28;

const int dirPin_3 = 49;
const int stepPin_3 = 48;
#define motorInterfaceType 1

Joint joint1(motorInterfaceType, stepPin_1, dirPin_1);
Joint joint2(motorInterfaceType, stepPin_2, dirPin_2);
Joint joint3(motorInterfaceType, stepPin_3, dirPin_3);

ros::Publisher complete_publisher("arm_complete", &complete_msg);

void subscriberCallback(const std_msgs::UInt16& command_msg) {
    complete_msg.data = false;
    complete_publisher.publish(&complete_msg);
    // // Set the speed in RPM
    // joint1.setSpeed(30);  // Adjust to your desired speed
    // // Rotate the stepper motor
    // joint1.moveTo(command_msg.data);  // Rotate 100 steps
    // while (joint1.distanceToGo() != 0) {
    //   complete_msg.data = false;
    //   complete_publisher.publish(&complete_msg);
    // }
    complete_msg.data = true;
    complete_publisher.publish(&complete_msg);
}

ros::Subscriber<std_msgs::UInt16> command_subscriber("arm_command", &subscriberCallback);

void setup() {
    joint1.setup();
    joint1.setSpeed(200);
    joint2.setup();
    joint2.setSpeed(200);
    joint3.setup();
    joint3.setSpeed(200);

    node_handle.initNode();
    node_handle.advertise(complete_publisher);
    node_handle.subscribe(command_subscriber);
}

void loop() {
    // main loop code here
    node_handle.spinOnce();
}