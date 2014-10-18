#include "HT1632.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

// use this line for single matrix
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

String tweet = "Low Animal Spirit";
int numDisplays = 2;
int textX = 0;

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen(); 

  // set up for text display
  matrix.setTextSize(1.5);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
}

void loop() {
  String tempString = tweet.substring(0, 2*numDisplays);
  

  matrix.fillRect(0, 0, 24*numDisplays, 16, 0);
  matrix.setCursor(textX, 4);   
  matrix.print(tempString);
  matrix.writeScreen();

  textX++;                 // go to next position
  textX = textX%(24*numDisplays);  // don't go off the end

  delay(1000);
}


