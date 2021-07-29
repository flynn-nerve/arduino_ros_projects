#include "encoder.h"

HallSensor::HallSensor(byte HS_S1, byte HS_S2) {
  this->HS_S1 = HS_S1;
  this->HS_S2 = HS_S2;
  count = 0;
}

void HallSensor::initHallSensor() {
  pinMode(HS_S1, INPUT);
  pinMode(HS_S2, INPUT);
}
