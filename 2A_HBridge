int right_pin = 5;
int left_pin = 3;
int right_on = 8;
int left_on = 7;
int max_brightness = 255;
int off = 0;
volatile bool off_state = true;
volatile bool right_state = false;
volatile bool left_state = false;

void rightStateToggle(){
  Serial.println("right");
  off_state = false;
  left_state = false;
  right_state = true;
}

void leftStateToggle(){
  Serial.println("left");
  off_state = false;
  right_state = false;
  left_state = true;
}

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
  pinMode(right_pin, OUTPUT);
  pinMode(left_pin, OUTPUT);
  pinMode(right_on, INPUT_PULLUP);
  pinMode(left_on, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(right_on), rightStateToggle, RISING);
  attachInterrupt(digitalPinToInterrupt(left_on), leftStateToggle, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (off_state){
    //nothing
    Serial.println("off logic");
  }else if(right_state){
    right_state_logic();
  }else if(left_state){
    left_state_logic();
  }
}

void right_state_logic(){
  Serial.println("right logic");
  analogWrite(left_pin, off);
  analogWrite(right_pin, max_brightness/2);
}

void left_state_logic(){
  Serial.println("left logic");
  analogWrite(right_pin, off);
  analogWrite(left_pin, max_brightness/2);
}
