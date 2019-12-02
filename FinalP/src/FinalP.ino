/*
 * Project FinalP
 * Description:
 * Author:
 * Date:
 */

int servoAction(String message){
analogWrite(D0,minturn,50);
if (Time.now()>(waitingtime+60)){
  analogWrite(D0,nutrual,50);
  waitingtime=Time.now();
}  
}

void setup() {
  Serial.begin(9600);
  Particle.function("translator",servoAction);
  pinMode(D0,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
Serial.println("working");
}
