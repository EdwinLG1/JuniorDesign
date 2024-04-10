// PUT IN APPROPRIATE PIN NUMBERS FOR YOUR SYSTEM!!!
int ir_transistor = A0; // Analog Input Pin for reading voltage at phototransistor
int collision_pin = 5; // Digital Input Pin
int collision_initiate_pin = 6; // Dig In Pin || to trigger interrupt
int motorAPin1 = 7
int motorAPin2 = 8
int motorBPin1 = 9
int motorBPin2 = 10
int enableAPin1 = 11
int enableAPin2 = 12
int max_power = 255;
int off = 0;

//TEST THIS WITH YOUR BOT TO GET THE RIGHT VALUES >
int collision_range[2] = {0,500}; // range of acceptable voltage to detect collision 
int ir_value;

// STATE VARIABLES
int FORWARD_STATE = 1
int STOP_STATE = 2;
int CURRENT_STATE = STEERING_STATE;

void collision(){
  stopMotors()
}

void setup() {
  // This automatically goes into the ON state
  Serial.begin(9600);
  pinMode(ir_transistor, INPUT);
  pinMode(collision_pin, INPUT);
  pinMode(collision_initiate_pin, OUTPUT);
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);
  pinMode(enableBPin1, OUTPUT);
  attachInterrupt(collision_pin, collision, RISING);
}


void loop() {
  // MAIN LOOP
  if (CURRENT_STATE == STOP_STATE){
    collision_logic();
  }else if (CURRENT_STATE == FORWARD_STATE){
    collision_logic();
  }
}

void collision_logic(){
  ir_value = analogRead(ir_transistor);
  Serial.println(ir_value);
  if (ir_value >= collision_range[0] && ir_value <= collision_range[1]){
    digitalWrite(collision_initiate_pin, HIGH);
    CURRENT_STATE = STOP_STATE;
  }else{
    digitalWrite(collision_initiate_pin, LOW);
    CURRENT_STATE = FORWARD_STATE;
}

void forwardDirection() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);

  analogWrite(enableAPin1, 150); // Set speed (0 to 255)
  analogWrite(enableBPin1, 150);
}

void stopMotors(){
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);

  analogWrite(enableAPin1, 0); // Set speed (0 to 255)
  analogWrite(enableBPin1, 0);
}

