// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
#include "MotorClass.h"

// Analog Ouput pins for forward and backward movement
MotorClass Motor1(5,6);
MotorClass Motor2(9,10);

int max_power = 255;
int off = 0;
float Leftfudge_factor = 3.2; // Experimental value from our bot to get time/degree turned
float Rightfudge_factor = 3.05; // Experimental value from our bot to get time/degree turned
volatile bool collision = false;

// STATE VARIABLES
int IDLE_STATE = 1;
int ACTIVE_STATE = 2;

int CURRENT_STATE = ACTIVE_STATE;

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
}

void loop() {
  // MAIN LOOP
  // Get variables
  if (CURRENT_STATE == IDLE_STATE){
    // Do Nothing
  }else if (CURRENT_STATE == ACTIVE_STATE){
    Move12In();
    delay(1000);  
    turnClockwise(180);
    delay(1000);
    MoveBack3In();
    delay(1000);
    LeftRightRightRight();
    CURRENT_STATE = IDLE_STATE;
  }
}

void Move12In(){
  Motor1.goForward(max_power);
  Motor2.goForward(200);
  delay(800);
  Motor1.stop();
  Motor2.stop();
}

void MoveBack3In(){
  Motor1.goForward(max_power);
  Motor2.goForward(200);
  delay(800);
  Motor1.stop();
  Motor2.stop();
}

void LeftRightRightRight(){
  turnCounterClockwise(90);
  delay(500);
  turnClockwise(90);
  delay(500);
  turnClockwise(90);
  delay(500);
  turnClockwise(90);
}

void turnClockwise(int degrees){
  Motor2.goBackward(max_power);
  Motor1.goForward(max_power);
  delay(degrees * Leftfudge_factor);
  Motor1.stop();
  Motor2.stop();
}

void turnCounterClockwise(int degrees){
  Motor1.goBackward(max_power);
  Motor2.goForward(max_power);
  delay(degrees * Rightfudge_factor);
  Motor1.stop();
  Motor2.stop();
}

