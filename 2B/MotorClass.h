#ifndef MotorClass_h
#define MotorClass_h

#include "Arduino.h"

class MotorClass {
  public:
    MotorClass(int forward_pin, int backward_pin);
    void MotorClass::goForward(int speed);
    void MotorClass::goBackward(int speed);
    void MotorClass::Stop();
  private:
    int _forward_pin;
    int _backward_pin;
    int _OFF ;
};

#endif
