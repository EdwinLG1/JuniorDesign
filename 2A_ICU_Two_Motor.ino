// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
int m1forward_pin = A0;
int m1backward_pin = A1;
int m2forward_pin = A2;
int m2backward_pin = A3;
int mstate_pin = 8;
int m1control_pin = 7;
int m2control_pin = 6;
int max_power = 255;
int off = 0;
volatile bool motor_off = true;
volatile bool m1forward = false;
volatile bool m2forward = false;
volatile bool m1backward = false;
volatile bool m2backward = false;

void toggle_motor_on(){
  motor_off = !motor_off;
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
  pinMode(mstate_pin, INPUT_PULLUP);
  pinMode(m1control_pin, INPUT);
  pinMode(m2control_pin, INPUT);
  pinMode(m1forward_pin, OUTPUT);
  pinMode(m1backward_pin, OUTPUT);
  pinMode(m2forward_pin, OUTPUT);
  pinMode(m2backward_pin, OUTPUT);
  attachInterrupt(mstate_pin, toggle_motor_on, CHANGE);
  attachInterrupt(m1control_pin, m1forwardISR, HIGH);
  attachInterrupt(m1control_pin, m1backwardISR, LOW);
  attachInterrupt(m2control_pin, m2forwardISR, HIGH);
  attachInterrupt(m2control_pin, m2backwardISR, LOW);
}

void loop() {
  // MAIN LOOP
  if (motor_off){
    //nothing
  }else{
    m1_state_logic();
    m2_state_logic();
  }
}

void m1_state_logic(){
  if (m1forward){
    analogWrite(m1backward_pin, off);
    analogWrite(m1forward_pin, max_power);
  }else if (m1backward){
    analogWrite(m1forward_pin, off);
    analogWrite(m1backward_pin, max_power);
  }
}

void m2_state_logic(){
  if (m2forward){
    analogWrite(m2backward_pin, off);
    analogWrite(m2forward_pin, max_power);
  }else if (m2backward){
    analogWrite(m2forward_pin, off);
    analogWrite(m2backward_pin, max_power);
  }
}
