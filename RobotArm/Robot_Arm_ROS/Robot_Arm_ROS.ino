#include "Joint.h"

#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle node_handle;

std_msgs::UInt16 command_msg;
std_msgs::Bool complete_msg;

// Define the number of steps per revolution and motor pins
int stepsPerRevolution = 200;  // Replace with your motor's steps per revolution
int motor1_dirPin = 8;  // Replace with your motor's pin 1
int motor1_stepPin  = 9;  // Replace with your motor's pin 2

Joint joint1(motor1_dirPin, motor1_stepPin, stepsPerRevolution);

ros::Publisher complete_publisher("arm_complete", &complete_msg);

void subscriberCallback(const std_msgs::UInt16& command_msg) {
    complete_msg.data = false;
    complete_publisher.publish(&complete_msg);
    // Set the speed in RPM
    joint1.setSpeed(30);  // Adjust to your desired speed
    // Rotate the stepper motor
    joint1.moveTo(command_msg.data);  // Rotate 100 steps
    complete_msg.data = true;
    complete_publisher.publish(&complete_msg);
}

ros::Subscriber<std_msgs::UInt16> command_subscriber("arm_command", &subscriberCallback);

void setup() {
    node_handle.initNode();
    node_handle.advertise(complete_publisher);
    node_handle.subscribe(command_subscriber);
}

void loop() {
    // main loop code here
    node_handle.spinOnce();
}