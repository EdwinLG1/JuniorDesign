#include "Arduino.h"
#include "MotorClass.h"

MotorClass::MotorClass(int forward_pin, int backward_pin){
  pinMode(forward_pin, OUTPUT);
  pinMode(backward_pin, OUTPUT);
  _f_pin = forward_pin;
  _b_pin = backward_pin;
  _OFF = 0;
}

void MotorClass::goForward(int speed){
  analogWrite(_f_pin, speed);
  analogWrite(_b_pin, OFF);
}

void MotorClass::goBackward(int speed){
  analogWrite(_f_pin, speed);
  analogWrite(_b_pin, OFF);
}

void MotorClass::Stop(int speed){
  analogWrite(_f_pin, OFF);
  analogWrite(_b_pin, OFF);
}
