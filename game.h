#ifndef GAME_H
#define GAME_H

#include "gameview.h"
#include "controls.h"

bool evenGameNumber = true;

void stateGameStart() {
  setNewGameData();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying() {
  updateGame();
  drawGame();
  if (gameEnded) {
    gameState = STATE_GA_UPDATE;

    // invert the screen to reduce burn in
    if (evenGameNumber)
    {
      display.invertDisplay(1);
    }
    else
    {
      display.invertDisplay(0);
    }
    evenGameNumber = !evenGameNumber;
    
  }
}

void stateGAupdate() {
  //TODO
  gameState = STATE_GAME_START;
}



#endif
