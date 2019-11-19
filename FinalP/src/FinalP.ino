/*
 * Project FinalP
 * Description:
 * Author:
 * Date:
 */
const  int nutrual =0.075*255;
const int min =0.05 *255;
const int max = 0.1 * 255;
int tempSensor = A0;
double temperatureC = 0.0;

int servoAction(String message){
analogWrite(D0,minturn,50);
if (Time.now()>(waitingtime+60)){
  analogWrite(D0,nutrual,50);
  waitingtime=Time.now();
}  
}

void setup() {
  Serial.begin(9600);
  pinMode(tempSensor, AN_INPUT);
 
  Particle.function("translator",servoAction);
  pinMode(D0,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

double voltage = analogRead(tempSensor)/4095.0*3.3;
temperatureC = 104.6*voltage - 54.4;
  
analogWrite(D0,90,50);

}