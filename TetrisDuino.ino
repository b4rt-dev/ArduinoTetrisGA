
#include "globals.h"
#include "display.h"
#include "bitmaps.h"
#include "gameview.h"
#include "gamedata.h"
#include "gametetrominos.h"
#include "game.h"
#include "controls.h"

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
      //TODO remove unwanted gamestates
      case 0: stateGameOver(); break;
      case 1: stateGameOver(); break;
      case 2: stateGameStart(); break;
      case 3: stateGamePlaying(); break;
      case 4: stateGamePlaying(); break;
      case 5: stateGameOver(); break;
      default: break;
    }
    //((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
    display.display();
    display.clearDisplay();
  }
}

// Just draw as fast as possible for now (I2C is bottleneck here)
bool nextFrame() {
  return true;
}
