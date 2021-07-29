#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <tankbot/EncoderCount.h>

#include "motor.h"
#include "encoder.h"
#include "led.h"

// Onboard LED pin (attached to Teensy board)
#define obLEDPin        13  // Attached to board
// Motor encoder pins (Motor -> Breadboard -> Teensy)
#define EncoderL_S1     16  // orange -> purple
#define EncoderL_S2     17  // blue   -> white
#define EncoderR_S1     20  // orange -> white
#define EncoderR_S2     21  // blue   -> black
// Motor Controller (PWM) pins (Teensy -> Motor Driver)
#define MotorL_OUT1     14  // yellow
#define MotorL_OUT2     15  // orange
#define MotorR_OUT1     18  // white
#define MotorR_OUT2     19  // blue

// Create necessary objects
Motor motor_L(MotorL_OUT1, MotorL_OUT2);
Motor motor_R(MotorR_OUT1, MotorR_OUT2);
HallSensor encoder_L(EncoderL_S1, EncoderL_S2);
HallSensor encoder_R(EncoderR_S1, EncoderR_S2);
LED onboardLED(obLEDPin);

// Generate a nodehandle
ros::NodeHandle nh;

// Define callback function
void cmdVelCallback(const geometry_msgs::Twist& msg) {
  motor_L.vel = msg.linear.x * (-1);
  motor_R.vel = msg.linear.x;
  motor_L.vel += msg.angular.z;
  motor_R.vel += msg.angular.z;
}

// Declare subscriber
ros::Subscriber<geometry_msgs::Twist> cmdVelSub("/cmd_vel", cmdVelCallback );

// Declare publisher and published message variable
tankbot::EncoderCount encoder_count;
ros::Publisher encoderCountPub("/encoder_count", &encoder_count);

void setup() {
  Serial.begin(57600);
  
  // Initialize ROS facilities
  nh.initNode();
  nh.advertise(encoderCountPub);
  nh.subscribe(cmdVelSub);

  // Flash LED once to indicate program is starting
  onboardLED.LEDflash(3000);

  // Attach two interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(EncoderL_S1), EL_S1_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderL_S2), EL_S2_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderR_S1), ER_S1_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderR_S2), ER_S2_ISR, RISING);

  // Allow the device a moment to finish initializing
  delay(1000);

  while (!nh.connected()){
    Serial.println("Waiting for roscore...");
    nh.spinOnce();
    delay(1000);
  }
}

void loop() {
  motor_L.driveMotor();
  motor_R.driveMotor();

  encoder_count.enc1_ticks = encoder_L.count;
  encoder_count.enc2_ticks = encoder_R.count;

  encoderCountPub.publish(&encoder_count);
  nh.spinOnce();
  delay(10);
}

void EL_S1_ISR() {
  encoder_L.count++;
}

void EL_S2_ISR() {
  encoder_L.count--;
}

void ER_S1_ISR() {
  encoder_R.count++;
}

void ER_S2_ISR() {
  encoder_R.count--;
}
