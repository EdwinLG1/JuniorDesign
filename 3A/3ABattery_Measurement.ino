// Battery Power Management Measuring System
void setup() {
	pinMode(2, OUTPUT); // Red LED
	pinMode(3, OUTPUT); // Yellow LED
	pinMode(4, OUTPUT); // Green LED 1
  pinMode(5, OUTPUT); // Green LED 2
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  Serial.begin(9600);
}

void loop(){
  batteryVoltage();
}

void batteryVoltage(){
	int batterySensor = analogRead(A3);
  Serial.println(batterySensor);
  if((batterySensor >= 900) && (batterySensor <= 1023)){ // Battery Full
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH); // Both green LEDs on
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  } else if ((batterySensor >= 600) && (batterySensor <= 900)){ // Battery High 66% -95% (65% battery - analogy value of ~600)
    digitalWrite(4, HIGH); // 1 Green LED on
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  } else if((batterySensor >= 300) && (batterySensor <= 600)){  // Battery Medium 33% - 66%
    digitalWrite(3, HIGH); // Yellow LED on
    digitalWrite(2, LOW);
  } else {                  // Battery Low, Needs Charge <33%
    digitalWrite(2, HIGH); // Red LED on
  }
}
