#ifndef GAME_H
#define GAME_H

#include "gameview.h"
#include "controls.h"

void stateGameStart() {
  setNewGameData();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying() {
  updateGame();
  drawGame();
  if (gameEnded) {
    // TODO do GA update function
    gameState = STATE_GAME_START;
  }
}

void stateGAupdate() {
  
}

void stateGameOver() {
  drawGameOver();
  if (buttonPressedAny()) {
    gameState = STATE_HOME;
  } 
}





#endif
