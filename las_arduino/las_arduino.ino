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

int numDisplays = 8;
int textX = 0;
int stringIndex = 0;
int lenTweet = 26;

char tweetValue[4];    // incoming storage of tweet
int lastTweetCount = 0; // keep track of number of tweets
char tweetText[141];
char bridgeTweet[141];
int currChar = 1;

int currTextChar = 0;

boolean debugMode = false;
String t = "";
String startString = " Waiting............... *** ";


boolean displayHandle = false;
int tweetCounter = 0;

//-------------------------------------------
void setup() {
  Bridge.begin();    // initialise Bridge
  Serial.begin(9600);
  while (!Serial) {

  }

  matrix.begin(HT1632_COMMON_16NMOS);

  // set up for text display
  matrix.setTextSize(1.5);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs

  // start with string for waiting
  
  startString.toCharArray(tweetText, 141);


  for (int i = 0; i < 35; i++ ) {
    t += nextChar();
  }
}

//-------------------------------------------
void loop() {
  // if new tweet came in
  /*if ( tweets != lastTweetCount ) {
    matrix.clearScreen();
    for (int i = 0; i < numDisplays * 24; i += 6) {
      matrix.fillRect(0, 0, 24 * numDisplays, 16, 0);
      matrix.setCursor(i, 4);
      matrix.print("***");
      matrix.writeScreen();
    }

    textX = numDisplays * 24;
    lastTweetCount = tweets;
  }

  */

  // scroll width of one character
  for (int tX = 0; tX > -6; tX--) {
    matrix.fillRect(0, 0, 24 * numDisplays, 16, 0);
    matrix.setCursor(tX, 4);

    matrix.print(t);
    matrix.writeScreen();
    delay(1);
  }
  Serial.println(t);
  // progress through char array
  t = t.substring(1);
  t += nextChar();
}

//-------------------------------------------
char nextChar() {
  currChar++;

  // if completed buffer and not displaying handle
  if (currChar > lenTweet && !displayHandle) {
    currChar = 0;
    tweetCounter++;
    // if number of tweets have gone by
    if ( tweetCounter > 1 ) {
      lenTweet = 20;
      String handle = " @LowAnimalSpirit *** ";
      handle.toCharArray( tweetText, 141 );

      tweetCounter = 0;
      displayHandle = true;

      Serial.println("---------display handle---------");
    }
  }
  // if completed buffer and displaying handle
  if (currChar > lenTweet && displayHandle) {
    currChar = 0;
    tweetCounter++;
    // if number of tweets have gone by
    if ( tweetCounter > 0 ) {
      // clear text in buffer
      for (int i = 0; i < 141; i++) {
        tweetText[i] = ' ';
      }

      Serial.println("---------reading in next tweet---------");
      // read in waiting tweet
      Bridge.get("text", tweetText, 141);
      Bridge.get("tweets", tweetValue, 4);
      lenTweet = atoi(tweetValue) - 1;
      Serial.println(tweetValue);
      Serial.println(lenTweet);
      if( lenTweet < 2 ){
          startString.toCharArray(tweetText, 141);
          lenTweet = 26;
      }
      tweetCounter = 0;
      displayHandle = false;
    }
  }
  return tweetText[currChar];
}

