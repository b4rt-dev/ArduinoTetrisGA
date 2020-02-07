
void stateGameStart() {
  setNewGameData();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying() {
  updateGame();
  doAImovement();
  drawGame();
  drawStats();

  if (gameEnded) {
    gameState = STATE_GA_UPDATE;
    
    invertDisplay(); // reduce burn in
  }
}

void stateGAupdate() {
  //TODO
  gameState = STATE_GAME_START;
}

