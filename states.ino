
void stateGameStart() {
  setNewGameData();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying() {
  updateGame();
  doAImovement();
  drawLEDs();
  
  if (!fastLearn)
  {
    drawGame();
  }

  else // skip all bottlenecking drawing
  {
    // set OLED display black
    display.invertDisplay(0);
    display.fillScreen(BLACK);
    display.display();

    // set all leds to off
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    digitalWrite(PIN_DOWN, LOW);
    digitalWrite(PIN_LEFT, LOW);
    digitalWrite(PIN_RIGHT, LOW);
  }
  

  if (gameEnded) {
    gameState = STATE_GA_UPDATE;
    
    Serial.print("Game over for chromosome ");
    Serial.print(currentChromosomeID);
    Serial.print(" on island ");
    Serial.print(currentIslandID);
    Serial.print(" with a score of ");
    Serial.println(score);

    if (!fastLearn) // we do not want to invert the display when it is off
      invertDisplay(); // reduce burn in
  }
}

void stateGAupdate() {
  //Serial.println("Updating GA");
  updateGA();
  gameState = STATE_GAME_START;
}

