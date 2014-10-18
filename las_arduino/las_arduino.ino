#include "HT1632.h"
#include <Bridge.h>

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

// use this line for single matrix
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

String tweet = "Phabulous sistine says chapel  *** ";
int numDisplays = 2;
int textX = 0;
int stringIndex = 0;

char tweetValue[4];    // incoming storage of tweet
int lastTweetCount = 0; // keep track of number of tweets
unsigned long lastBubble;
char tweetText[141];

void setup() {
  Bridge.begin();    // initialise Bridge

  if (debugMode) {
    // we don't want Serial when deployed
    // it will make the microcontroller hang
    // waiting for a response
    Serial.begin(9600);
    while ( !Serial );
  }


  matrix.begin(HT1632_COMMON_16NMOS);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();

  // set up for text display
  matrix.setTextSize(1.5);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
}

void loop() {
  // Read command output
  Bridge.get("tweets", tweetValue, 4);
  Bridge.get("text", tweetText, 141);
  int tweets = atoi(tweetValue);

  String tempString = tweet.substring(stringIndex, stringIndex + (2 * numDisplays));
  int tweetLength = tweet.length();

  matrix.fillRect(0, 0, 24 * numDisplays, 16, 0);
  matrix.setCursor(textX, 4);
  matrix.print(tweetText);
  matrix.writeScreen();

  // increment/decrement counters
  textX--;                 // go to next position
  textX = textX % (tweetLength + (numDisplays * 48)); // don't go off the end

  delay(300);
}

