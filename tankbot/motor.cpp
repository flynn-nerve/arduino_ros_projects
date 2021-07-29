#include "motor.h"

Motor::Motor(byte M_Fwd, byte M_Rev) {
  // Init any values for use here
  this->M_Fwd = M_Fwd;
  this->M_Rev = M_Rev;
  initMotor();
}

void Motor::initMotor() {
  pinMode(M_Fwd, OUTPUT);
  pinMode(M_Rev, OUTPUT);
  vel = 0;
  vel_cmd = 0;
  stopMotor();
}

void Motor::stopMotor() {
  analogWrite(M_Fwd, 0);
  analogWrite(M_Rev, 0);
}

// Drive the motor
void Motor::driveMotor() {
  vel_cmd = max(vel, -1);
  vel_cmd = min(vel, 1);
  if (vel > 0) {
    vel_cmd = abs(vel_cmd);
    vel_cmd = map(vel_cmd, 0, 1, 0, 255);
    analogWrite(M_Fwd, vel_cmd);
    analogWrite(M_Rev, 0);
  } else {
    vel_cmd = map(vel_cmd, 0, 1, 0, 255);
    vel_cmd = abs(vel_cmd);
    analogWrite(M_Rev, vel_cmd);
    analogWrite(M_Fwd, 0);
  }
}
