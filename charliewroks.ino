


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

void setup() {
  // Put initialization like pinMode and begin functions here.
  rowNum = 0;
  colNum = 0;
  setAllToInput();
}

void loop() {

  // The core of your code will likely live here.
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