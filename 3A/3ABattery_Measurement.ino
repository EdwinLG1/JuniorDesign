// Battery Power Management Measuring System
void setup() {
	pinMode(2, OUTPUT); // Red LED
	pinMode(3, OUTPUT); // Yellow LED
	pinMode(4, OUTPUT); // Green LED
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
  Serial.begin(9600);
}

void loop(){
  batteryVoltage();
}

void batteryVoltage(){
	int batterySensor = analogRead(A3);
  Serial.println(batterySensor);
  if((batterySensor >= 900) && (batterySensor <= 1023)){
    digitalWrite(4, HIGH);
  }
}
