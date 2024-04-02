// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
#include "MotorClass.h"

// Analog Ouput pins for forward and backward movement
MotorClass Motor1(5,6);
MotorClass Motor2(9,10);

int state_user_pin = 8; // Input Digital Pin
int m1_user_pin = 13; // Input Digital Pin
int m2_user_pin = 12; // Input Digital Pin
int ir_transistor = A0; // Analog Input Pin
int c_transistor = A1; // Analog Input Pin
int max_power = 255;
int off = 0;
int collision_range[2] = {0,500}; // range of acceptable voltage to detect collision
int red_range[2] = {0,500}; // range of acceptable voltage to detect red
int blue_range[2] = {0,500}; // range of acceptable voltage to detect blue
int yellow_range[2] = {0,500}; // range of acceptable voltage to detect yellow
int black_range[2] = {0,500}; // range of acceptable voltage to detect black
char road_color;
volatile int ir_value;
volatile int c_value;
volatile bool obstacle = false;
volatile bool motor_off = true;
volatile bool m1forward = true;
volatile bool m2forward = true;
volatile bool m1backward = false;
volatile bool m2backward = false;

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

void collect_c_data(){
  c_value = analogRead(c_transistor);
  Serial.println(c_value);
}

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
  pinMode(state_user_pin, INPUT_PULLUP);
  pinMode(m1_user_pin, INPUT_PULLUP);
  pinMode(m2_user_pin, INPUT_PULLUP);
  pinMode(ir_transistor, INPUT);
  pinMode(c_transistor, INPUT);
  attachInterrupt(ir_transistor, collect_ir_data, CHANGE);
  attachInterrupt(c_transistor, collect_c_data, CHANGE);
  attachInterrupt(state_user_pin, motorTOGGLE_ISR, CHANGE);
  attachInterrupt(m1_user_pin, m1directionISR, CHANGE);
  attachInterrupt(m2_user_pin, m2directionISR, CHANGE);
}

void loop() {
  // MAIN LOOP
  if (motor_off){
    Motor1.stop();
    Motor2.stop();
  }else{
    collision_logic();
    color_logic();
    m1_state_logic();
    m2_state_logic();
  }
}

void collision_logic(){
  if (ir_value >= collision_range[0] && ir_value <= collision_range[1]){
    obstacle = true;
  }else{
    obstacle = false;
  }
}

void color_logic(){
  if (c_value >= black_range[0] && c_value <= black_range[1]){
    road_color = "black";
  }else if (c_value >= red_range[0] && c_value <= red_range[1]){
    road_color = "red";
  }else if (c_value >= yellow_range[0] && c_value <= yellow_range[1]){
    road_color = "yellow";
  }else if (c_value >= blue_range[0] && c_value <= blue_range[1]){
    road_color = "blue";
  }
}

void m1_state_logic(){
  if (m1forward){ // Makes motor 1 go to the right
    Motor1.goForward(max_power);
  }else if (m1backward){ // Makes motor 1 go to the left
    Motor1.goBackward(max_power);
  }
}

void m2_state_logic(){
  if (m2forward){ // Makes motor 2 go to the right
    Motor2.goForward(max_power);
  }else if (m2backward){ // Makes motor 2 go to the left
    Motor2.goBackward(max_power);
  }
}
