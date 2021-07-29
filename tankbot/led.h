#ifndef LED_H
#define LED_H

// This is automatically included in "main" functions but not otherwise, allows use of specific Arduino functions and types
#include <Arduino.h>

class LED {

  private:
    // variables
    byte pin;

  public:
    // functions
    LED(byte pin);
    void initLED();
    void LEDoff();
    void LEDflash(int dur);
};

#endif
