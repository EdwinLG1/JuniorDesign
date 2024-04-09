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
    digitalWrite(5, HIGH);
  } else if ((batterySensor >= 600) && (batterySensor <= 900)){ // Battery High 65%-95% (65% battery - analogy value of ~600)
    digitalWrite(4, HIGH);
  } else if((batterySensor >= 600) && (batterySensor <= 900)){  // Change numbers --> Battery Medium
    digitalWrite(3, HIGH);
  } else {                  // Battery Low, Needs Charge
    digitalWrite(2, HIGH);
  }
}
