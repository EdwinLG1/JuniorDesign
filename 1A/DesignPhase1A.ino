// ACTION: Put the correct pin numbers for the switches, buttons, and LEDS
// ACTION: Test and Debug the code on the Arduino
// ACTION: Check if attach interrupt statements are valid

int red_led = 13;       // digital pin
int green_led = 10;     // PWM pin
int blue_led = 5;       // PWM pin
int toggle_button = 2;  // digital pin
int switch1 = 8;        // digital pin
int switch2 = 7;        // digital pin
int max_brightness = 255;
int green_brightness = 255;
bool blue_on = false;
bool fade_on = false;
bool red_on = false;

unsigned long interval = 250;      // 250 ms
unsigned long fade_interval = 24;  // 24 ms
int flashes = 0;
unsigned long time_elapsed = 0;
unsigned long startMillis = millis();
unsigned long currentMillis = 0;

bool flash_on = true;
bool flash_state = true;
volatile bool run_state = true;
volatile bool switch1_state = false;
volatile bool switch2_state = false;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  // This automatically goes into the ON state
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(toggle_button, INPUT_PULLUP);
  // All of the attach interrupt statements
  attachInterrupt(digitalPinToInterrupt(8), switch1Pressed, RISING);
  attachInterrupt(digitalPinToInterrupt(7), switch2Pressed, RISING);
}

void loop() {
  run_state_logic();
}

// Interrupt Service Routine (ISR) for Switch 1
void switch1Pressed() {
  switch1_state = true;
  Serial.print("We're in the mainframe");
}

// Interrupt Service Routine (ISR) for Switch 2
void switch2Pressed() {
  switch2_state = true;
}

void flash_logic() {
  if (flashes < 3) {                       // As long as 2 complete flash cycles have not been done
    if (time_elapsed >= interval) {  // if a 4th of a second has passed
      startMillis = currentMillis;
      flash_on = !flash_on;
      if (flash_on) {
        analogWrite(green_led, max_brightness);
      } else {
        flashes += 1;
        analogWrite(green_led, 0);
      }
    }
  } else {
    flashes = 0;
    flash_state = false;
  }
}


// dims green LED and then flashes twice
void run_state_logic() {
  int fadeAmount = 1;
  startMillis = millis();
  currentMillis = 0;
  int onDuration = 0;
  int offDuration = 0;
  while (run_state) {
    currentMillis = millis();
    time_elapsed = currentMillis - startMillis;
    if (flash_state) {
      flash_logic();
    }
  }
  // while (run_state) {
  //   //set pin brightness
  //   analogWrite(green_led, green_brightness);
  //   //lessen brightness
  //   green_brightness = green_brightness - fadeAmount;
  //   delay(100);  // delay for 10 ms - divides evenly into 6 seconds over 51 quantized dims
  //   //check if light is off
  //   if (green_brightness <= 0) {
  //     digitalWrite(green_led, HIGH);
  //     delay(250);
  //     digitalWrite(green_led, LOW);
  //     delay(250);
  //     digitalWrite(green_led, HIGH);
  //     delay(250);
  //     digitalWrite(green_led, LOW);
  //     delay(250);
  //     green_brightness = 255;

  //     if (switch1_state == true) {
  //       onDuration = 50;
  //       offDuration = 50;
  //       if (currentMillis - previousMillis >= onDuration) {
  //         digitalWrite(blue_led, LOW);
  //         previousMillis = currentMillis;
  //       } else if (currentMillis - previousMillis >= offDuration) {
  //         digitalWrite(blue_led, HIGH);
  //         previousMillis = currentMillis;
  //       }

  //       if (switch2_state == false) {
  //         digitalWrite(red_led, HIGH);
  //       } else {
  //         digitalWrite(red_led, LOW);
  //       }

  //     } else {
  //       onDuration = 500;
  //       offDuration = 500;
  //       digitalWrite(red_led, LOW);
  //       if (currentMillis - previousMillis >= onDuration) {
  //         digitalWrite(blue_led, LOW);
  //         previousMillis = currentMillis;
  //       } else if (currentMillis - previousMillis >= offDuration) {
  //         digitalWrite(blue_led, HIGH);
  //         previousMillis = currentMillis;
  //       }
  //     }
  //   }
  // }
}
