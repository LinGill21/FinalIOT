/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "c:/Users/S529464/Documents/photon/FinalP/src/FinalP.ino"
/*
 * Project FinalP
 * Description:
 * Author:
 * Date:
 */

void setup();
void servoAction(String message);
void loop();
#line 8 "c:/Users/S529464/Documents/photon/FinalP/src/FinalP.ino"
Servo myservo;
int analogPin = A5;
void setup() {
  Serial.begin(9600);
  pinMode(analogPin, AN_INPUT);
  myservo.attach(D0);
  Particle.function("foodTime",servoAction);
}
void servoAction(String message){
myservo.write(90);
int time = Time.now();
if (Time.now()>(time+60)){
myservo.write(0);
}  
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
//int value;
//value = analogRead(analogPin);
//Serial.println(value);
myservo.write(90);
delay(1000);
}