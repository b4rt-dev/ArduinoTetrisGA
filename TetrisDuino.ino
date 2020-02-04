

#define byte uint8_t
 

//#include <avr/pgmspace.h>
#include "globals.h"
#include "display.h"
#include "bitmaps.h"
//#include "home.h"
#include "gameview.h"
#include "gamedata.h"
#include "gametetrominos.h"
#include "game.h"
#include "controls.h"

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] = {
  stateGameOver,
  stateGameOver,
  stateGameStart,
  stateGamePlaying,
  stateGamePause,
  stateGameOver
};

const unsigned long eachFrameMillis = 1000 / FPS; // FPS
unsigned long nextFrameStart = 0;


void setup() { 
  Serial.begin(115200);

  delay(10);
  randomSeed(analogRead(0));
  
  setupDisplay();
  setupControls();
  
}

void loop() {
  
  if (nextFrame()) {
    updateControls();
    switch(gameState) {
      case 0: stateGameOver(); break;
      case 1: stateGameOver(); break;
      case 2: stateGameStart(); break;
      case 3: stateGamePlaying(); break;
      case 4: stateGamePause(); break;
      case 5: stateGameOver(); break;
      default: break;
    }
    //((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
    display.display();
    display.clearDisplay();
  }
}

// Just draw as fast as possible (I2C is bottleneck here)
boolean nextFrame() {
  return true;
}
