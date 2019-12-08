// This #include statement was automatically added by the Particle IDE.
#include <Ubidots.h>
#include <HX711ADC.h>
#ifndef UBIDOTS_TOKEN
#define UBIDOTS_TOKEN "BBFF-o1XSVDciQjpdW2hoYju4tSWqrolzUW"  // Put here your Ubidots TOKEN
#endif
Ubidots ubidots(UBIDOTS_TOKEN, UBI_INDUSTRIAL, UBI_TCP);
//scale code from https://github.com/jfangrad/IOT_Scale/blob/master/Photon%20Files/scale.ino
// HX711.DOUT or hx711 clk	- pin #A1
// HX711.PD_SCK	or hx711 data - pin #A0
//vdd - pin vin
//vcc - pin 3v3
const  int nutrual =0.075*255;
const int minturn =0.05 *255;


int pinData[8][7][2] = {
{{8,1},{8,2},{8,3},{8,4},{8,5},{8,6},{8,7}},
{{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,8}}, 
{{6,1},{6,2},{6,3},{6,4},{6,5},{6,7},{6,8}},
{{5,1},{5,2},{5,3},{5,4},{5,6},{5,7},{5,8}},
{{4,1},{4,2},{4,3},{4,5},{4,6},{4,7},{4,8}},
{{3,1},{3,2},{3,4},{3,5},{3,6},{3,7},{3,8}},
{{2,1},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8}},
{{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8}}
};

int photonMap [] = {0, D7, D6, D5, D4, D3, D2, D1, D0};
int rowNum;
int colNum;

HX711ADC scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library
double timestart =0;
double timestop =0;
int count =0;

void turnOn(int row, int col){
  setAllToInput();
  int highPin = photonMap[pinData[row][col][0]];
  int lowPin = photonMap[pinData[row][col][1]];
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  digitalWrite(highPin, HIGH);
  digitalWrite(lowPin, LOW);
}


void setAllToInput(){
  for(int i = 1; i < 9; i ++){
    pinMode(photonMap[i], INPUT_PULLUP);
  }
}

int servoAction(String message){
analogWrite(A5,minturn,50);
lightshow();
}  

void lightshow (){
  for(int i = 0; i < 57; i++){
      turnOn(rowNum, colNum);
      rowNum++;
      if(rowNum > 7){
        colNum++;
        rowNum = 0;
      }
      if(colNum >6){
        colNum = 0;
      }
      delay(50);
  }
  analogWrite(A5,nutrual,50);
}


void setup() {
    // Put initialization like pinMode and begin functions here.
  rowNum = 0;
  colNum = 0;
  setAllToInput();
  Serial.begin(9600);
  Particle.function("translator",servoAction);
  pinMode(A5,OUTPUT);
  analogWrite(A5,nutrual,50);
  //Serial.println("HX711 Demo");
  scale.begin();
  scale.set_scale(2350.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

}

void loop() {
double weight =(scale.read());
Serial.println(weight);
  if( weight<0){
      if (count == 0){
          timestart = Time.now();
          count ++;
      }
  }
  if (weight>0 && count>0 ){
          timestop= Time.now();
  }
  if (timestart>0 && timestop >0 ){
      double foodtime = timestop -timestart;
      ubidots.add("Food_out_Time", foodtime);
      Serial.println(foodtime);
  }
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if(bufferSent){
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  scale.power_down();			        // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
}
