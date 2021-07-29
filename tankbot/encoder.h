#ifndef ENCODERS_H
#define ENCODERS_H

// This is automatically included in "main" functions but not otherwise, allows use of specific Arduino functions and types
#include <Arduino.h>

// From motor documentation - https://gitnova.com/#/Robot/Engine/9vMotor/9vmotor
// Code wheel parameters: 2 pulses / turn

class HallSensor {
  
  private:
    // variables
    byte HS_S1;
    byte HS_S2;

  public:
    // variables
    unsigned int count;
    
    //functions
    HallSensor(byte HS_S1, byte HS_S2);
    void initHallSensor();
};

#endif
