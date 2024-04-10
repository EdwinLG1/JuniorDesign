/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);

  analogWrite(enableAPin1, 150); // Set speed (0 to 255)
  analogWrite(enableBPin1, 150);
}


/*
 * name:      reverseDirection
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor backward
 */
void reverseDirection() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  analogWrite(enableAPin1, 150); // Set speed (0 to 255)
  analogWrite(enableBPin1, 200);
}

void turnLeft(int duration) {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableBPin1, 150);

  delay(duration);
}
