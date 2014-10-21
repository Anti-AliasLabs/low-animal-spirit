#include "HT1632.h"
#include <Bridge.h>

#define DATA 2
#define WR   3
#define CS0  4
#define CS1  5
#define CS2  6
#define CS3  7
#define CS4  8
#define CS5  9
#define CS6  10
#define CS7  11

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS0, CS1, CS2, CS3, CS4, CS5, CS6, CS7);

String tweet = "1 2 3 4 5 6 7 8 9 0  *** ";
int numDisplays = 8;
int textX = 0;
int stringIndex = 0;

char tweetValue[4];    // incoming storage of tweet
int lastTweetCount = 0; // keep track of number of tweets
unsigned long lastBubble;
char tweetText[141];

boolean debugMode = false;


void setup() {
  /*Bridge.begin();    // initialise Bridge

  if (debugMode) {
    // we don't want Serial when deployed
    // it will make the microcontroller hang
    // waiting for a response
    Serial.begin(9600);
    while ( !Serial );
  }
*/

  matrix.begin(HT1632_COMMON_16NMOS);
/*  for (uint8_t y=0; y<matrix.height(); y++) {
    for (uint8_t x=0; x< matrix.width(); x++) {
      matrix.setPixel(x, y);
      matrix.writeScreen();
    }
    matrix.clearScreen();
  }*/

  // set up for text display
  matrix.setTextSize(1.5);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
}

void loop() {
  // Read command output
  //Bridge.get("tweets", tweetValue, 4);
  //Bridge.get("text", tweetText, 141);
  //int tweets = atoi(tweetValue);

  String tempString = tweet.substring(stringIndex, stringIndex + (2 * numDisplays));
  int tweetLength = tweet.length();

  matrix.fillRect(0, 0, 24 * numDisplays, 16, 0);
  matrix.setCursor(textX, 4);
  matrix.print(tweet);
  matrix.writeScreen();

  // increment/decrement counters
  textX--;                 // go to next position
  textX = textX % (tweetLength + (numDisplays * 48)); // don't go off the end

  delay(100);
}

