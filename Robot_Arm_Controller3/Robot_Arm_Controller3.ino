// Library
#include <Encoder.h>
#include <L298N.h>

// PID Control
double kp = 0.4;
double kd = 1.2;
double ki = 0.018;

// Pin Assignment
int m_ena_1 = 9;
int m_in1_1 = 8;
int m_in2_1 = 7;
int e_en2 = 6;
int e_en1 = 5;

// Object Declaration
L298N motor(m_ena_1, m_in1_1, m_in2_1);
Encoder enc(e_en1, e_en2);

// PID Variables
int interval = 10;
long previousMillis = 0; 
int desiredPos = 0;
long error = 0;
long prevError = 0;
long rateError = 0;
long cumError = 0;
// bool moved = false;

// Variables for Serial Communication
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array for use when parsing
boolean newData = false;

// Variables to hold the Parsed Data
char command[numChars] = {0};
float theta_1 = 0.0;
float theta_2 = 0.0;
float theta_3 = 0.0;
float theta_4 = 0.0;

// States
enum states {
  IDLE,
  MOVE,
  STOP
};
states state;

void setup() {

  Serial.begin(115200);

  state = IDLE;
}

void loop() {

  recvWithStartEndMarkers();

  if (newData == true) {

    strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }

  switch(state) {
    
    case IDLE:

      moveTo(0);
      break;

    case MOVE:

      // moveTo(theta_1 * 2800 / 360);
      moveTo(theta_1);
      break;

    case STOP:

      stop();
      break;
  }
}

void moveTo(float pos){

  desiredPos = pos;
  
  unsigned long currentMillis = millis();
  long currEnc = enc.read();
  // float currDeg = currEnc / 2800.0 * 360.0;
  // while (currDeg <= -360) currDeg += 360.0;
  // while (currDeg >= 360) currDeg -= 360.0;

  if(currentMillis - previousMillis > interval){

    error = desiredPos - currEnc;
    rateError = error - prevError;
    cumError = cumError + error;
    if (cumError > 2000) cumError = 2000;
    if (cumError < -2000) cumError = -2000;    

    int speed = kp * abs(error);
    if (speed > 70) speed = 70;
    speed = speed - kd * abs(rateError) + ki * abs(cumError);
    
    if (speed > 100) speed = 100;
    if (speed < 0) speed = 0;

    if(error > 0){
      motor.setSpeed(speed);
      motor.backward();
    }
    else{
      motor.setSpeed(speed);
      motor.forward();
    }

    Serial.print("Desired: ");
    Serial.print(desiredPos);
    Serial.print("\tEncoder: ");
    Serial.print(currEnc);
    // Serial.print("\tPosition: ");
    // Serial.print(currDeg);
    Serial.print("\tError: ");
    Serial.print(error);
    Serial.print("\tRate Error: ");
    Serial.print(rateError);
    Serial.print("\tCum Error: ");
    Serial.print(cumError);
    Serial.print("\tSpeed: ");
    Serial.println(speed);
    
    previousMillis = currentMillis; 
    prevError = error; 
  }


}

void stop(){

  long currEnc = enc.read();
  unsigned long currentMillis = millis();

  float currDeg = currEnc / 2800.0 * 360.0;
  while (currDeg <= -360) currDeg += 360.0;
  while (currDeg >= 360) currDeg -= 360.0;

  if(currentMillis - previousMillis > interval){

    previousMillis = currentMillis;  
    motor.setSpeed(0);
    motor.forward();

    Serial.print("Encoder Value: ");
    Serial.print(currEnc);
    Serial.print("\tPosition: ");
    Serial.println(currDeg);
  }
}

void recvWithStartEndMarkers() {
  
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {

    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars,",");      // get the first part - the string
  strcpy(command, strtokIndx); // copy it to command

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  theta_1 = atoi(strtokIndx);     // convert this part to an float

  strtokIndx = strtok(NULL, ",");
  theta_2 = atof(strtokIndx);     // convert this part to a float

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  theta_3 = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  theta_4 = atof(strtokIndx);     // convert this part to a float
}

void showParsedData() {

  if (command[0] == 'M') {

    Serial.print("Command: ");
    Serial.println(command);
    Serial.print("Theta 1: ");
    Serial.println(theta_1);
    Serial.print("Theta 2: ");
    Serial.println(theta_2);
    Serial.print("Theta 3: ");
    Serial.println(theta_3);
    Serial.print("Theta 4: ");
    Serial.println(theta_4);

    state = MOVE;

    Serial.println("State: MOVE");
  }
  else if (command[0] == 'S'){
    
    Serial.print("Command: ");
    Serial.println(command);

    state = STOP;

    Serial.println("State: STOP");
  }
  else if (command[0] == 'I'){
    
    Serial.print("Command: ");
    Serial.println(command);

    state = IDLE;

    Serial.println("State: IDLE");
  }
}