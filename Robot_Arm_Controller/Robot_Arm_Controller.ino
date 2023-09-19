// Library
#include <Encoder.h>
#include <L298N.h>

// PID Control
double kp = 2;
double kd = 0.003;
double ki = 0;

// Pin Assignment
int m_ena_1 = 9;
int m_in1_1 = 8;
int m_in2_1 = 7;
int e_en2 = 6;
int e_en1 = 5;

// Object Declaration
L298N motor(m_ena_1, m_in1_1, m_in2_1);
Encoder enc(e_en1, e_en2);

// Variables for PID Control
long currEnc = 0;
long current_val = 0;
long error_val = 0;
int desiredPos = 0;
long previousMillis = 0; 
long interval = 10;  
unsigned short driverPwm = 0;
long error_val_init = 0;
long previousTime = 0;
long elapsedTime = 0;
long cumError = 0;
long rateError = 0;

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

  pinMode(m_ena_1, OUTPUT); 
  pinMode(m_in1_1, OUTPUT);

  state = IDLE;
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

  recvWithStartEndMarkers();

  if (newData == true) {

    strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }

  currEnc = enc.read();

  switch(state) {
    
    case IDLE:

      moveTo(0);

      break;

    case MOVE:

      moveTo(theta_1);
      break;

    case STOP:

      controlMotor(0, L298N::BACKWARD);
      Serial.print("\tEncoder Value: ");
      Serial.println(currEnc);

      break;
  }
}

void moveTo(float pos){
    
  desiredPos = pos;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval){

    error_val = desiredPos - currEnc;
    int effort = kp*error_val;
    int direction = (abs(error_val > 0 ) ? L298N::FORWARD : L298N::BACKWARD);
    previousMillis = currentMillis;  
    controlMotor(effort, direction);  

    Serial.print("PWM value: ");
    Serial.print(driverPwm);
    Serial.print("\tEncoder Value: ");
    Serial.print(currEnc);
    Serial.print("\tError value: ");
    Serial.print(error_val);
    Serial.print("\tDirection: ");
    Serial.println(direction);

    if (Serial.available()) {

      desiredPos = Serial.parseInt();
      Serial.print("New Desired Position: ");
      Serial.print(desiredPos);
    }
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