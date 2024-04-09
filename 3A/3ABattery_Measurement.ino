// Battery Power Management Measuring System
void setup( ) {
	pinMode(2, OUTPUT)
	pinMode(3, OUTPUT)
	pinMode(4, OUTPUT)
	digitalWrite(2, LOW)
	digitalWrite(3, LOW)
	digitalWrite(4, LOW)
}

void batteryVoltage(){
	int batterySensor = analogRead(A3)
}
