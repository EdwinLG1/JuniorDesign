// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
int state_user_pin = 8; // Input Digital Pin
int m1_user_pin = 13; // Input Digital Pin
int m2_user_pin = 12; // Input Digital Pin
int m1direction_pin = 2; // Output Digital Pin
int m2direction_pin = 4; // Output Digital Pin
int m1PWM_pin = 5; // Output Analog Pin
int m2PWM_pin = 10; // Output Analog Pin
int max_power = 255;
int off = 0;
volatile bool motor_off = true;
volatile bool m1forward = false;
volatile bool m2forward = false;
volatile bool m1backward = false;
volatile bool m2backward = false;

void motorON_ISR(){
  Serial.println("motor on");
  motor_off = false;
}

void motorOFF_ISR(){
  Serial.println("motor off");
  motor_off = true;
}

void m1forwardISR(){
  m1backward = false;
  m1forward = true;
}

void m1backwardISR(){
  m1forward = false;
  m1backward = true;
}

void m2forwardISR(){
  m2backward = false;
  m2forward = true;
}

void m2backwardISR(){
  m2forward = false;
  m2backward = true;
}

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
  pinMode(state_user_pin, INPUT_PULLUP);
  pinMode(m1_user_pin, INPUT_PULLUP);
  pinMode(m2_user_pin, INPUT_PULLUP);
  pinMode(m1direction_pin, OUTPUT);
  pinMode(m2direction_pin, OUTPUT);
  pinMode(m1PWM_pin, OUTPUT);
  pinMode(m2PWM_pin, OUTPUT);
  attachInterrupt(state_user_pin, motorON_ISR, HIGH);
  attachInterrupt(state_user_pin, motorOFF_ISR, LOW);
  attachInterrupt(m1_user_pin, m1forwardISR, HIGH);
  attachInterrupt(m1_user_pin, m1backwardISR, LOW);
  attachInterrupt(m2_user_pin, m2forwardISR, HIGH);
  attachInterrupt(m2_user_pin, m2backwardISR, LOW);
}

void loop() {
  // MAIN LOOP
  if (motor_off){
    off_state();
  }else{
    m1_state_logic();
    m2_state_logic();
  }
}

void off_state(){
  // Turn off motors
  analogWrite(m1PWM_pin, off);
  analogWrite(m2PWM_pin, off);

}

void m1_state_logic(){
  if (m1forward){ // Makes motor 1 go to the right
    digitalWrite(m1direction_pin, HIGH);
    analogWrite(m1PWM_pin, max_power);
  }else if (m1backward){ // Makes motor 1 go to the left
    digitalWrite(m1direction_pin, LOW);
    analogWrite(m1PWM_pin, max_power);
  }
}

void m2_state_logic(){
  if (m2forward){ // Makes motor 2 go to the right
    digitalWrite(m2direction_pin, HIGH);
    analogWrite(m2PWM_pin, max_power);
  }else if (m2backward){ // Makes motor 2 go to the left
    digitalWrite(m2direction_pin, LOW);
    analogWrite(m2PWM_pin, max_power);
  }
}
