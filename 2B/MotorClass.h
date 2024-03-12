#ifndef MotorClass_h
#define MotorClass_h

#include "Arduino.h"

class MotorClass {
  public:
    MotorClass(int forward_pin, int backward_pin);
    void MotorClass::goForward(int speed);
    void MotorClass::goBackward(int speed);
    void MotorClass::Stop(int speed);
  private:
    int _f_pin;
    int _b_pin;
    int _OFF ;
}
