
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

