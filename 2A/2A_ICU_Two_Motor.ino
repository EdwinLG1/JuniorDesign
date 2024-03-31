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
  attachInterrupt(state_user_pin, motorTOGGLE_ISR, CHANGE);
  attachInterrupt(m1_user_pin, m1directionISR, CHANGE);
  attachInterrupt(m2_user_pin, m2directionISR, CHANGE);
}

void loop() {
  // MAIN LOOP
  digitalWrite(m1direction_pin, HIGH);
  analogWrite(m1PWM_pin, max_power);
  digitalWrite(m2direction_pin, HIGH);
  analogWrite(m2PWM_pin, max_power);
  if (motor_off){
    //off_state();
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
