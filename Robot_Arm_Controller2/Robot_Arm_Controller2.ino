// Library
#include <Encoder.h>
#include <L298N.h>

// PID Control
double kp = 0.4;
double kd = 1.2;
double ki = 0.000;

// Pin Assignment
int m_ena_1 = 9;
int m_in1_1 = 8;
int m_in2_1 = 7;
int e_en2 = 6;
int e_en1 = 5;

// Object Declaration
L298N motor(m_ena_1, m_in1_1, m_in2_1);
Encoder enc(e_en1, e_en2);

// Global Variables
int interval = 10;
long previousMillis = 0; 
int desiredPos = 0;
long error = 0;
long prevError = 0;
long rateError = 0;
long cumError = 0;
//int baseSpeedRest = 40;
//int baseSpeedMove = 25;
//long previousEnc = 0;
//bool move = false;

void setup() {

  Serial.begin(115200);
}

void loop() {

  unsigned long currentMillis = millis();
  long currEnc = enc.read();
  // float currDeg = currEnc / 3200.0 * 360.0;
  // while (currDeg <= -360) currDeg += 360.0;
  // while (currDeg >= 360) currDeg -= 360.0;
  // if (currDeg > 180) currDeg -= 360.0;
  // if (currDeg < -180) currDeg += 360.0;


  if(currentMillis - previousMillis > interval){

    //int baseSpeed = 25;

    // if(move){
    //   if (abs(previousEnc - currEnc) > 3) baseSpeed = baseSpeedMove;
    //   else baseSpeed = baseSpeedRest;
    // }
    // else{
    //   move = true;
    // }

    error = desiredPos - currEnc;
    rateError = error - prevError;

    //int speed = kp * abs(error) - kd * abs(rateError);
    int speed = kp * abs(error);
    if (speed > 70) speed = 70 - kd * abs(rateError);
    if (speed < 0) speed = 0;

    if(error > 0){
      motor.setSpeed(speed);
      motor.backward();
    }
    else{
      motor.setSpeed(speed);
      motor.forward();
    }

    // int speed = baseSpeed + 30 * abs(error) / 3200;

    // if(error > 0){
    //   motor.setSpeed(speed);
    //   motor.backward();
    // }
    // else{
    //   motor.setSpeed(speed);
    //   motor.forward();
    // }

    // motor.setSpeed(baseSpeed);
    // motor.backward();

    // if (currEnc > -3200){
    //   motor.setSpeed(200);
    //   motor.forward();
    // }
    // else{
    //   motor.setSpeed(0);
    //   motor.forward(); 
    // }

    Serial.print("Desired: ");
    Serial.print(desiredPos);
    Serial.print("\tEncoder: ");
    Serial.print(currEnc);
    Serial.print("\tError: ");
    Serial.print(error);
    Serial.print("\tRate Error: ");
    Serial.print(rateError);
    // Serial.print("\tBase Speed: ");
    // Serial.print(baseSpeed);
    Serial.print("\tSpeed: ");
    Serial.println(speed);

    // Serial.print("\tPosition: ");
    // Serial.println(currDeg);
    
    previousMillis = currentMillis; 
    prevError = error; 
    //previousEnc = currEnc;
  }

  if(Serial.available()){

    //baseSpeed = Serial.parseInt();
    desiredPos = Serial.parseInt();
  }
}