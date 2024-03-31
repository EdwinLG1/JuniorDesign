#include "Arduino.h"
#include "MotorClass.h"

MotorClass::MotorClass(int forward_pin, int backward_pin){
  pinMode(forward_pin, OUTPUT);
  pinMode(backward_pin, OUTPUT);
  _forward_pin = forward_pin;
  _backward_pin = backward_pin;
  _OFF = 0;
}

void MotorClass::goForward(int speed){
  analogWrite(_forward_pin, speed);
  analogWrite(_backward_pin, _OFF);
}

void MotorClass::goBackward(int speed){
  analogWrite(_backward_pin, speed);
  analogWrite(_forward_pin, _OFF);
}

void MotorClass::stop(){
  analogWrite(_forward_pin, _OFF);
  analogWrite(_backward_pin, _OFF);
}
