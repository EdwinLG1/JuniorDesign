// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
#include "MotorClass.h"

// Analog Ouput pins for forward and backward movement
MotorClass Motor1(5,6);
MotorClass Motor2(9,10);

int headlight_pin = 2; // Digital Output Pin
int state_user_pin = 8; // Input Digital Pin
int m1_user_pin = 13; // Input Digital Pin
int m2_user_pin = 12; // Input Digital Pin
int ir_transistor = A0; // Analog Input Pin
int c1_transistor = A1; // Analog Input Pin
int c2_transistor = A2; // Analog Input Pin
int ambientlight_pin = A5; // Analog Input Pin
int max_power = 255;
int off = 0;
int unsigned long fudge_factor = 2000; // 2 seconds || Experimental value from our bot to get time/degree turned
int day_range[2] = {0, 500}; // range of acceptable voltage for daytime
int collision_range[2] = {0,500}; // range of acceptable voltage to detect collision
int red_range[4] = {960,989 , 930,960}; // range of acceptable voltage to detect red
int blue_range[4] = {930,959 , 860,929}; // range of acceptable voltage to detect blue
int yellow_range[4] = {990,1024 , 960,1024}; // range of acceptable voltage to detect yellow
int black_range[4] = {0,929 , 0,859}; // range of acceptable voltage to detect black
int road_color[2];
volatile int ir_value;
volatile int c_value[2];
volatile int light_value;
volatile bool day = false;
volatile bool motor_off = true;
volatile bool m1forward = true;
volatile bool m2forward = true;
volatile bool m1backward = false;
volatile bool m2backward = false;
// COLORS
int BLACK = 1;
int RED = 2;
int BLUE = 3;
int YELLOW = 4;
// STATE VARIABLES
int STEERING_STATE = 1;
int STOP_STATE = 2;
int TURN_STATE = 3;
int CURRENT_STATE = STEERING_STATE;

void motorTOGGLE_ISR(){
  Serial.println("motor toggle");
  motor_off = !motor_off;
}

void m1directionISR(){
  Serial.println("m1 direction");
  m1forward = !m1forward;
  m1backward = !m1backward;
}

void m2directionISR(){
  Serial.println("m2 direction");
  m2forward = !m2forward;
  m2backward = !m2backward;
}

void collect_ir_data(){
  ir_value = analogRead(ir_transistor);
  Serial.println(ir_value);
}

void collect_c1_data(){
  c_value[0] = analogRead(c1_transistor);
  Serial.println(c_value[0]);
}

void collect_c2_data(){
  c_value[1] = analogRead(c2_transistor);
  Serial.println(c_value[1]);
}

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
  pinMode(state_user_pin, INPUT_PULLUP);
  pinMode(m1_user_pin, INPUT_PULLUP);
  pinMode(m2_user_pin, INPUT_PULLUP);
  pinMode(ir_transistor, INPUT);
  pinMode(c1_transistor, INPUT);
  pinMode(c2_transistor, INPUT);
  pinMode(ambientlight_pin, INPUT);
  pinMode(headlight_pin, OUTPUT);
  attachInterrupt(ir_transistor, collect_ir_data, CHANGE);
  attachInterrupt(c1_transistor, collect_c1_data, CHANGE);
  attachInterrupt(c2_transistor, collect_c2_data, CHANGE);
  attachInterrupt(state_user_pin, motorTOGGLE_ISR, CHANGE);
  attachInterrupt(m1_user_pin, m1directionISR, CHANGE);
  attachInterrupt(m2_user_pin, m2directionISR, CHANGE);
}

void loop() {
  // MAIN LOOP
  headlight_logic();
  if (CURRENT_STATE == STOP_STATE){
    Motor1.stop();
    Motor2.stop();
    CURRENT_STATE = TURN_STATE;
  }else if (CURRENT_STATE == STEERING_STATE){
    // collision_logic();
    Motor1.goForward(50);
    Motor2.goBackward(50);
    color_logic();
    // steering_logic();
  }else if (CURRENT_STATE == TURN_STATE){
    turnCounterClockwise(180); // 180 degree turn
    CURRENT_STATE = STEERING_STATE;
  }
}

void collision_logic(){
  if (ir_value >= collision_range[0] && ir_value <= collision_range[1]){
    CURRENT_STATE = STOP_STATE;
  }
}

void color_logic(){
  c_value[0] = analogRead(c1_transistor);
  c_value[1] = analogRead(c2_transistor);

  if (c_value[0] >= black_range[0] && c_value[0] <= black_range[1]){
    road_color[0] = BLACK;
  }else if (c_value[0] >= red_range[0] && c_value[0] <= red_range[1]){
    road_color[0] = RED;
  }else if (c_value[0] >= yellow_range[0] && c_value[0] <= yellow_range[1]){
    road_color[0] = YELLOW;
  }else if (c_value[0] >= blue_range[0] && c_value[0] <= blue_range[1]){
    road_color[0] = BLUE;
  }
  if (c_value[1] >= black_range[2] && c_value[1] <= black_range[3]){
    road_color[1] = BLACK;
  }else if (c_value[1] >= red_range[2] && c_value[1] <= red_range[3]){
    road_color[1] = RED;
  }else if (c_value[1] >= yellow_range[2] && c_value[1] <= yellow_range[3]){
    road_color[1] = YELLOW;
  }else if (c_value[1] >= blue_range[2] && c_value[1] <= blue_range[3]){
    road_color[1] = BLUE;
  }
}

void steering_logic(){
  if (road_color[0] != BLACK && road_color[1] != BLACK){
    Motor1.goForward(max_power);
    Motor2.goForward(max_power);
  }else if (road_color[0] == BLACK && road_color[1] != BLACK){
    turnClockwise(1); // 1 degree turn
  }else if (road_color[1] == BLACK && road_color[0] != BLACK){
    turnCounterClockwise(1); // 1 degree turn
  }
}

void m2_state_logic(){
  if (m2forward){ // Makes motor 2 go to the right
    Motor2.goForward(max_power);
  }else if (m2backward){ // Makes motor 2 go to the left
    Motor2.goBackward(max_power);
  }
}

void turnClockwise(int degrees){
  Motor2.stop();
  Motor1.goForward(max_power);
  int unsigned long start_time = millis();
  int unsigned long turn_time = degrees * fudge_factor; // fudge factor is experimental time from 360 degree test
  int unsigned long current_time = 0;
  while ((current_time - start_time) < turn_time){
    int unsigned long current_time = millis();
  }
  Motor1.stop();
}

void turnCounterClockwise(int degrees){
  Motor1.stop();
  Motor2.goForward(max_power);
  int unsigned long start_time = millis();
  int unsigned long turn_time = degrees * fudge_factor; // fudge factor is experimental time from 360 degree test
  int unsigned long current_time = 0;
  while ((current_time - start_time) < turn_time){
    int unsigned long current_time = millis();
  }
  Motor2.stop();
}

void headlight_logic(){
  light_value = analogRead(ambientlight_pin);
  //Serial.println(light_value);
  if (light_value >= day_range[0] && light_value <= day_range[1]){
    day = true;
    //Serial.println("Day");
  }else{
    //Serial.println("Night");
  }
}
