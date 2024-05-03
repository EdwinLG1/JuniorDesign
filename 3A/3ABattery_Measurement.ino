// m in this case means motor 
// motor 1 is left, motor 2 is right when looking at bot from the back
#include "MotorClass.h"

// Analog Ouput pins for forward and backward movement
MotorClass Motor1(5,6);
MotorClass Motor2(9,10);

int counter = 0;
// Battery Power Management Measuring System
void setup() {
	pinMode(13, OUTPUT); // Red LED
	pinMode(12, OUTPUT); // Yellow LED
	pinMode(8, OUTPUT); // Green LED 2
  pinMode(7, OUTPUT); // Green LED 1
	digitalWrite(13, LOW);
	digitalWrite(12, LOW);
	digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  Serial.begin(9600);
}
void loop(){
  batteryVoltage();
  counter++;
  // if (counter % 100 == 0) {
  //   Motor1.goForward(255);
  //   Motor2.goForward(245);
  //   counter = 0;
  //   delay(10);
  // }
  Motor1.stop();
  Motor2.stop();
}
void batteryVoltage(){
	int batterySensor = analogRead(A5);
  Serial.println(batterySensor);
  if((batterySensor >= 900) && (batterySensor <= 1023)){ // Battery Full
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH); // Both green LEDs on
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else if ((batterySensor >= 600) && (batterySensor <= 900)){ // Battery High 66% -95% (65% battery - analogy value of ~600)
    digitalWrite(8, HIGH); // 1 Green LED on
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(2, LOW);
  } else if((batterySensor >= 300) && (batterySensor <= 600)){  // Battery Medium 33% - 66%
    digitalWrite(12, HIGH); // Yellow LED on
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW); 
  } else {                  // Battery Low, Needs Charge <33%
    digitalWrite(13, HIGH); // Red LED on
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(12, LOW);
  }
}
