#include "Joint.h"

#include <ros.h>
#include <std_msgs/Bool.h>
//#include <std_msgs/UInt16.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle node_handle;

//std_msgs::UInt16 command_msg;
std_msgs::Bool complete_msg;
geometry_msgs::Twist command_msg;

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

int joint1Pos = 0;
int joint2Pos = 0;
int joint3Pos = 0;

int joint1Vel = 0;
int joint2Vel = 0;
int joint3Vel = 0;

void subscriberCallback(const geometry_msgs::Twist& command_msg) {
    // complete_msg.data = false;
    // complete_publisher.publish(&complete_msg);

    joint1Pos = int(command_msg.linear.x);
    joint2Pos = int(command_msg.linear.y);
    joint3Pos = int(command_msg.linear.z);

    joint1Vel = int(command_msg.angular.x);
    joint2Vel = int(command_msg.angular.y);
    joint3Vel = int(command_msg.angular.z);

    // Set the speed in RPM
    joint1.setSpeed(joint1Vel);  // Adjust to your desired speed
    joint2.setSpeed(joint2Vel);  // Adjust to your desired speed
    joint3.setSpeed(joint3Vel);  // Adjust to your desired speed

    // while (joint1.distanceToGo() != 0 || joint2.distanceToGo() != 0 || joint3.distanceToGo() != 0) {
    //   ;
    // }

    // complete_msg.data = true;
    // complete_publisher.publish(&complete_msg);
}

ros::Subscriber<geometry_msgs::Twist> command_subscriber("arm_command", &subscriberCallback);

void setup() {
    joint1.setup();
    joint2.setup();
    joint3.setup();

    // joint1.setSpeed(200);
    // joint2.setSpeed(200);
    // joint3.setSpeed(200);

    // joint1Pos = 2000;
    // joint2Pos = 2000;
    // joint3Pos = 2000;

    node_handle.initNode();
    node_handle.advertise(complete_publisher);
    node_handle.subscribe(command_subscriber);
}

void loop() {

    // Rotate the stepper motor
    joint1.moveTo(joint1Pos);  // Rotate 100 steps
    joint2.moveTo(joint2Pos);  // Rotate 100 steps
    joint3.moveTo(joint3Pos);  // Rotate 100 steps
    
    // main loop code here
    node_handle.spinOnce();
}