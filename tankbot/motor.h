#ifndef MOTOR_H
#define MOTOR_H

// This is automatically included in "main" functions but not otherwise, allows use of specific Arduino functions and types
#include <Arduino.h>

class Motor {

  private:
    // variables
    byte M_Fwd;
    byte M_Rev;

  public:
    // variables
    float vel;
    float vel_cmd;
    
    //functions
    Motor(byte M_Fwd, byte M_Rev);
    void initMotor();
    void stopMotor();
    void driveMotor();
};

#endif
