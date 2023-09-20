// Library
#include <Encoder.h>
#include <L298N.h>

// PID Control
double kp = 0.075;
double kd = 1;
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
int speed = 0;

void setup() {

  Serial.begin(115200);

  //pinMode(m_ena_1, OUTPUT); 
  //pinMode(m_in1_1, OUTPUT);
}

void controlMotor(int speed, int dir){

  motor.setSpeed(speed);

  if(dir == L298N::BACKWARD)
    motor.run(L298N::FORWARD);
  else if (dir == L298N::FORWARD)
    motor.run(L298N::BACKWARD);
  else
    motor.run(L298N::STOP);
}

void loop() {

  unsigned long currentMillis = millis();
  long currEnc = enc.read();
  float currDeg = currEnc / 3200.0 * 360.0;
  while (currDeg <= -360) currDeg += 360.0;
  while (currDeg >= 360) currDeg -= 360.0;
  if (currDeg > 180) currDeg -= 360.0;
  if (currDeg < -180) currDeg += 360.0;
  // currDeg = currDeg % (2*M_PI)
  // currDeg = (currDeg + (2*M_PI)) % (2*M_PI)
  // if (currDeg > M_PI){ 
  //   currDeg = currDeg - (2*M_PI)
  // }

  if(currentMillis - previousMillis > interval){
    // Serial.print("PWM value: ");
    // Serial.print(driverPwm);
    Serial.print("\tEncoder Value: ");
    Serial.println(currEnc);
    Serial.print("\tPosition: ");
    Serial.println(currDeg);
    
    previousMillis = currentMillis;   
  }

  motor.setSpeed(40);
  motor.backward();
}