// Martin Økter
// 07.09.2021
// SpiderRobo Control
// -In honor of Eddy The Great Inspiration

#include "spiderMove.h" //Self-made libary for moving-controll of the spider-platform

int pinList[8] = {2,7,1,6,0,3,8,9};
SpiderMove eddy(pinList);

void setup() {
  Serial.begin(9600);  
}

void loop() {
  eddy.forward();
}
