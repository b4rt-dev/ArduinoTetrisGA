
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
      case STATE_GAME_START:    stateGameStart();   break;
      case STATE_GAME_PLAYING:  stateGamePlaying(); break;
      case STATE_GA_UPDATE:     stateGAupdate();    break;
      default: break;
    }
    display.display();
    display.clearDisplay();
  }
}

// Just draw as fast as possible for now (I2C is bottleneck here)
bool nextFrame() {
  return true;
}
