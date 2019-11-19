/*
 * Project FinalP
 * Description:
 * Author:
 * Date:
 */
const  int nutrual =0.075*255;
const int min =0.05 *255;
const int max = 0.1 * 255;

void setup() {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  analogWrite(D0,min,50);
  delay(500);
  analogWrite(D0,nutrual,50);
  delay(500);
  analogWrite(D0,max,50);
  delay (500);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

analogWrite(D0,90,50);

}