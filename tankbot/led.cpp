#include "led.h"

LED::LED(byte pin) {
  // Init any values for use here
  this->pin = pin;
  initLED();
}

void LED::initLED() {
  pinMode(pin, OUTPUT);
  LEDoff();
}

void LED::LEDoff() {
  digitalWrite(pin, LOW);
}

// Drive the motor
void LED::LEDflash(int dur) {
  digitalWrite(pin, HIGH);
  delay(dur);
  digitalWrite(pin, LOW);
}
