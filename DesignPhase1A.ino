// ACTION: Put the correct pin numbers for the switches, buttons, and LEDS
// ACTION: Test and Debug the code on the Arduino
// ACTION: Check if attach interrupt statements are valid




int red_led = 13; // digital pin
int green_led = 10; // PWM pin
int blue_led = 5; // PWM pin
int toggle_button = 2; // digital pin
int switch1 = 8; // digital pin
int switch2 = 7; // digital pin
bool blue_on = false;
bool fade_on = false;
bool red_on = false;

bool flash_on = false;
volatile bool off_state = false;
volatile bool on_state = false;
volatile bool run_state = true;
volatile bool sleep_state = false;
volatile bool diagnostic_state = false;
volatile bool switch1_state = false;
volatile bool switch2_state = false;
unsigned long previousMillis = 0;
 



void setup() {
  // This automatically goes into the ON state
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(toggle_button, INPUT_PULLUP);
  Serial.begin(9600);
  // All of the attach interrupt statements
  attachInterrupt(digitalPinToInterrupt(2), toogleStatePressed, RISING);
  attachInterrupt(digitalPinToInterrupt(8), switch1Pressed, RISING);
  attachInterrupt(digitalPinToInterrupt(7), switch2Pressed, RISING);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (off_state) {
    // Do nothing
  }
  else if(on_state) {
    on_state_logic();
  }else if (run_state) {
    run_state_logic();
  }else if (sleep_state) {
    sleep_state_logic();
  }else if (diagnostic_state) {
    diagnostic_state_logic();
  }
}


// Interrupt Service Routine (ISR) to toggle between states
void toogleStatePressed(){
  if (off_state) {
    off_state = false;
    on_state = true;
  }else if (on_state){
    on_state = false;
    run_state = true;
  }else if (run_state){
    run_state = false;
    sleep_state = true;
    switch1_state = false; //switch states are only valid in run state
    switch2_state = false; // fix this Ayah
  }else if (sleep_state){
    sleep_state = false;
    diagnostic_state = true;
  }else if (diagnostic_state){
    diagnostic_state = false;
    off_state = true;
  }
}




// Interrupt Service Routine (ISR) for Switch 1
void switch1Pressed(){
  switch1_state = true;
}




// Interrupt Service Routine (ISR) for Switch 2
void switch2Pressed(){
  switch2_state = true;
}




// Toggle red lED
void ToggleRedLED(){
  if (red_on){
    digitalWrite(red_led, LOW);
    red_on = false;
    Serial.print("I'm in ToggleRedLED");

  }else{
    digitalWrite(red_led, HIGH);
    red_on = true;
  }
}




// Toggle blue LED
void PWMToggleBlueLED(int brightness){
  if (blue_on){
    analogWrite(blue_led, 0);
    blue_on = false;
  }else{
    analogWrite(blue_led, brightness);
    blue_on = true;
  }
}




// Toggle Blink and Fade State
void ToggleSleepStates(){
  if (!fade_on){
    fade_on = true;
  }else{
    fade_on = false;
  }
}




// Toggle green LED in run state
void PWMToggleFlashLED(int pin_num, int brightness){
  if (flash_on){
    analogWrite(pin_num, 0);
    flash_on = false;
  }else{
    analogWrite(pin_num, brightness);
    flash_on = true;
  }
}




// blinks the Red LED at 10Hz
void on_state_logic(){
  int frequency = 10; //Hz
  red_on = false;
  unsigned long start_time = millis();
  unsigned long current_time = 0;
  unsigned long time_elapsed = 0;
  unsigned long toggle_period = 1000/frequency;
  while (true){
    current_time = millis();
    time_elapsed = current_time - start_time;
    if ((time_elapsed % toggle_period) <= 10){ //less than 10 ms
      ToggleRedLED();
    }
  }
}


// int blue_brightness = 255;
//unsigned long previousMillis = 0;


// dims green LED and then flashes twice
void run_state_logic(){
  bool flash_state = false;
  int green_brightness = 255; // start off with max brightness
  //int blue_brightness = 255; //max brightness blue
  //int red_brightness = 255; // max red brightness
  int fadeAmount = 10;  
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  int onDuration = 0;
  int offDuration = 0;

    while (flash_state == false) {
      //set pin brightness
      // int green_brightness = 255;
      analogWrite(green_led, green_brightness);

     
      //lessen brightness
      green_brightness = green_brightness - fadeAmount;
      delay(100); // delay for 10 ms - divides evenly into 6 seconds over 51 quantized dims
      //check if light is off
      if(green_brightness <=0) {
        flash_state = true;
        digitalWrite(green_led, HIGH);
        delay(250);
        digitalWrite(green_led, LOW);
        delay(250);
        digitalWrite(green_led, HIGH);
        delay(250);
        digitalWrite(green_led, LOW);
        delay(250);
        flash_state == false;
    
        // if (switch1_state == true) {
        //   onDuration = 50;
        //   offDuration = 50;
        //   if (currentMillis - previousMillis >= onDuration) {
        //     digitalWrite(blue_led, LOW);
        //     previousMillis = currentMillis;
        //   } else if (currentMillis - previousMillis >= offDuration) {
        //     digitalWrite(blue_led, HIGH);
        //     previousMillis = currentMillis;
        //   }
          
        //   if (switch2_state == false) {
        //     digitalWrite(red_led, HIGH);
        //   } else {
        //     digitalWrite(red_led, LOW);
        //   }

        // } else {
        //   onDuration = 500;
        //   offDuration = 500;
        //   digitalWrite(red_led, LOW);
        //   if (currentMillis - previousMillis >= onDuration) {
        //     digitalWrite(blue_led, LOW);
        //     previousMillis = currentMillis;
        //   } else if (currentMillis - previousMillis >= offDuration) {
        //     digitalWrite(blue_led, HIGH);
        //     previousMillis = currentMillis;
        //   }
        // }
    }
      
  }
}




// blinks blue LED at 4hz for 1 sec, and fades for 1 sec until off
void sleep_state_logic(){
    bool flash_state = true;
    int blue_brightness = 0;
    int fadeAmount = 50;

    while (flash_state == true) {
      
      if (blue_brightness <= 0) {
        digitalWrite(blue_led, HIGH);
        delay(125);
        digitalWrite(blue_led, LOW);
        delay(125);
        digitalWrite(blue_led, HIGH);
        delay(125);
        digitalWrite(blue_led, LOW);
        delay(125);
        digitalWrite(blue_led, HIGH);
        delay(125);
        digitalWrite(blue_led, LOW);
        delay(125);
        digitalWrite(blue_led, HIGH);
        delay(125);
        blue_brightness = 255;
      
      }

      for (int i = 0; i <= 10; i++) {
        analogWrite(blue_led, blue_brightness);

        blue_brightness = blue_brightness - fadeAmount;
        delay(200); // delay for 10 ms - divides evenly into 6 seconds over 51 quantized dims
      }
    }
}
//   blue_on = true;
//   analogWrite(blue_led, 255);
//   fade_on = false;
//   int frequency = 4; //Hz
//   int brightness = 255;
//   unsigned long time_duration = 1000; // 1 sec of blink and fade
//   unsigned long start_time = millis();
//   unsigned long current_time = 0;
//   unsigned long time_elapsed = 0;
//   unsigned long blink_period = 1000/frequency;
//   unsigned long fade_period = 3000/brightness; //to steadily decrease brightness
//   while (true){
//     current_time = millis();
//     time_elapsed = current_time - start_time;
//     if (brightness == 0) {
//       continue;
//     }else if ((time_elapsed % time_duration) <= 10) { // if a second has passed
//       ToggleSleepStates();
//     }else if (fade_on & ((time_elapsed % fade_period) <= 10)) {
//       analogWrite(blue_led, brightness);
//       brightness = brightness - 1;
//     }else if (!fade_on & ((time_elapsed % blink_period) <= 10)) {
//       PWMToggleBlueLED(brightness);
//     }
//   }
// }




// blinks N number of times for N list of problems
void diagnostic_state_logic(){
  
  int problems = 5;

  while (true) {
    for (int i = 0; i < problems; i++) {
        digitalWrite(red_led, HIGH);
        delay(250);
        digitalWrite(red_led, LOW);
        delay(250);
    }

    delay(1000);
  }
  
  // // Figure out what "list of problems mean"
  // // Assume 5 problems. 2hz blinks, so 2.5 seconds in all
  // red_on = false;
  // int problems = 5;
  // int blinks = 0;
  // int frequency = 2; //Hz
  // int time_duration = 2500; // 2.5 sec
  // unsigned long start_time = millis();
  // unsigned long current_time = 0;
  // unsigned long time_elapsed = 0;
  // unsigned long toggle_period = 1000/frequency;
  // while (true){
  //   current_time = millis();
  //   time_elapsed = current_time - start_time;
  //   if ((blinks % problems) == 0) {
  //     delay(1000);
  //     start_time = millis();
  //   }
  //   if ((time_elapsed % toggle_period) <= 10){ //less than 10 ms
  //     ToggleRedLED();
  //     blinks = blinks + 1;
  //   }
  // }
}
