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
int ambientlight_pin = A4; // Analog Input Pin
int max_power = 255;
int off = 0;
int unsigned long fudge_factor = 2000; // 2 seconds || Experimental value from our bot to get time/degree turned
int day_range[2] = {700, 1024}; // range of acceptable voltage for daytime
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
volatile bool collision = false;
// COLORS
int BLACK = 1;
int RED = 2;
int BLUE = 3;
int YELLOW = 4;
// STATE VARIABLES
int IDLE_STATE = 1;
int GoToWALL_STATE = 2;
int FindRED_STATE = 3;
int FollowRED_STATE = 4;
int GoToYELLOW_STATE = 5;
int FollowYELLOW_STATE = 6;
int GoToEND_STATE = 7;
int Finished_STATE = 8;

int CURRENT_STATE = IDLE_STATE;

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
}

void loop() {
  // MAIN LOOP
  // Get variables
  headlight_logic();
  color_logic();
  collision_logic();
  if (CURRENT_STATE == IDLE_STATE){
    // Do Nothing
  }else if (CURRENT_STATE == GoToWALL_STATE){
    GoToWALL_STATELOGIC();
  }else if (CURRENT_STATE == FindRED_STATE){
    FindRED_STATELOGIC();
  }else if (CURRENT_STATE == FollowRED_STATE){
    FollowRED_STATELOGIC();
  }else if (CURRENT_STATE == GoToYELLOW_STATE){
    GoToYELLOW_STATELOGIC();
  }else if (CURRENT_STATE == FollowYELLOW_STATE){
    FollowYELLOW_STATELOGIC();
  }else if (CURRENT_STATE == GoToEND_STATE){
    GoToEND_STATELOGIC();
  }else if (CURRENT_STATE == Finished_STATE){
    // Do Nothing
  }
}

void collision_logic(){
  if (ir_value >= collision_range[0] && ir_value <= collision_range[1]){
    collision = true;
  }else{
    collision = false;
  }
}

void color_logic(){
  c_value[0] = analogRead(c1_transistor);
  c_value[1] = analogRead(c2_transistor);

  //Serial.println(c_value[0]);

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

void red_steering_logic(){
  if (road_color[0] == RED && road_color[1] == RED){
    Motor1.goForward(max_power);
    Motor2.goForward(max_power);
  }else if (road_color[0] == RED && road_color[1] != RED){
    turnCounterClockwise(1); // 1 degree turn
  }else if (road_color[0] != RED && road_color[1] == RED){
    turnClockwise(1); // 1 degree turn
  }
}

void yellow_steering_logic(){
  if (road_color[0] == YELLOW && road_color[1] == YELLOW){
    Motor1.goForward(max_power);
    Motor2.goForward(max_power);
  }else if (road_color[0] == YELLOW && road_color[1] != YELLOW){
    turnCounterClockwise(1); // 1 degree turn
  }else if (road_color[0] != YELLOW && road_color[1] == YELLOW){
    turnClockwise(1); // 1 degree turn
  } 
}

void blue_steering_logic(){
  if (road_color[0] == BLUE && road_color[1] == BLUE){
    Motor1.goForward(max_power);
    Motor2.goForward(max_power);
  }else if (road_color[0] == BLUE && road_color[1] != BLUE){
    turnCounterClockwise(1); // 1 degree turn
  }else if (road_color[0] != BLUE && road_color[1] == BLUE){
    turnClockwise(1); // 1 degree turn
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
  Serial.println(light_value);
  if (light_value >= day_range[0] && light_value <= day_range[1]){
    day = true;
    digitalWrite(headlight_pin, LOW);
  }else{
    //Serial.println("Night");
    digitalWrite(headlight_pin, HIGH);
  }
}

void GoToWALL_STATELOGIC(){
  Motor1.goForward(max_power);
  Motor2.goForward(max_power);
  if collision {
    Motor1.stop();
    Motor2.stop();
    turnClockwise(180);
    CURRENT_STATE = FindRED_STATE
  }
}

void FindRED_STATELOGIC(){
  Motor1.goForward(max_power);
  Motor2.goForward(max_power);
  if (road_color[0] == RED & road_color[1] == RED){
    turnCounterClockwise(45);
    CURRENT_STATE = FollowRED_STATE;
  }
}

void FollowRED_STATELOGIC(){
  red_steering_logic();
    if collision {
    Motor1.stop();
    Motor2.stop();
    turnCounterClockwise(90);
    CURRENT_STATE = GoToYELLOW_STATE;
  }
}

void GoToYELLOW_STATELOGIC(){
  Motor1.goForward(max_power);
  Motor2.goForward(max_power);
  if (road_color[0] == YELLOW & road_color[1] == YELLOW){
    turnCounterClockwise(45);
    CURRENT_STATE = FollowYELLOW_STATE;
  }
}

void FollowYELLOW_STATELOGIC(){
  yellow_steering_logic();
  if collision {
  Motor1.stop();
  Motor2.stop();
  turnCounterClockwise(90);
  CURRENT_STATE = GoToEND_STATE;
  }
}

void GoToEND_STATELOGIC(){
  Motor1.goForward(max_power);
  Motor2.goForward(max_power);
  if collision {
  Motor1.stop();
  Motor2.stop();
  turnCounterClockwise(180);
  CURRENT_STATE = Finished_STATE;
  }
}
