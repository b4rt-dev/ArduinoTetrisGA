////////////////////////////////////
// SCORE
////////////////////////////////////
void scoreAddDropPoints() {
  score += 1;
}


// increases score based on the number of lines cleared at the same time
// is not affected by level to keep scores linear
void scoreAddClearRowsPoints(uint8_t clearedLines) {
  switch(clearedLines) {
    case 1: score += 40; break;
    case 2: score += 100; break;
    case 3: score += 300; break;
    case 4: score += 1200; break;
    default: break;
  }
}


////////////////////////////////////
// BOARD
////////////////////////////////////
void clearBoard() {
  for (uint8_t row=0; row < ROWS; row++){
    for (uint8_t col=0; col < COLS; col++){
        boardMap[row][col] = false;
    }
  }
}

boolean haveRowsToRemove() {
  boolean have = false;
  for (uint8_t row=0; row < ROWS; row++){
    int mc = 0; // mino count
    for (uint8_t col=0; col < COLS; col++){
      if (boardMap[row][col]) mc++;
    }
    if (mc == COLS) {
      boardRowsToRemove[row] = true;
      have = true;
    } else {
      boardRowsToRemove[row] = false;
    }
  }
  return have;
}

uint8_t boardRemoveFilledRows() {
  uint8_t removeRows = 0;
  for (uint8_t row=0; row < ROWS; row++){
    int mc = 0; // mino count
    for (uint8_t col=0; col < COLS; col++){
      if (boardMap[row][col]) mc++;
    }
    if (mc == COLS) {
      removeRows++;
      for (uint8_t row2=row; row2 < ROWS; row2++){
        for (uint8_t col=0; col < COLS; col++){
          if (row2 != ROWS-1) {
            boardMap[row2][col] = boardMap[row2+1][col];
          } else {
            boardMap[row2][col] = false;
          }
        }
      }
      row--;
    }
  }
  return removeRows;
}

void boardFillRow(uint8_t fillRow) {
  for (uint8_t col=0; col < COLS; col++){
    boardMap[fillRow][col] = true;
  }
}


////////////////////////////////////
// GENERATE TETROMINO
////////////////////////////////////
void shuffleBag() 
{
  for (int x = 0; x < 5; x++) // shuffle five times
  {
    Tetromino bagCopy[7];
    memcpy(&bagCopy, &bag, sizeof(bag));
    
    int index = 0;
    int index_arr[7];
    for (int i = 0; i < 7; i++)
    {
      index_arr[i] = 0;
    }
    for (int i = 0; i < 7; i++) 
    {
      do 
      {
        srand(generation + randomSeedPiece);
        index = rand() % 7;
        randomSeedPiece++;
      }
      while (index_arr[index] != 0);
      index_arr[index] = 1;
      memcpy(&bag[i], &bagCopy[index], sizeof(bag[i]));
    }
  }

  //for(int j = 0; j < 7; j++) { Serial.print(bag[j]); Serial.print(" "); } Serial.println("");
}

void nextTetromino() {
  tetCurrent = bag[bagNextIndex];
  bagNextIndex++;
  if (bagNextIndex == 7) {
    bagNextIndex = 0;
    shuffleBag();
  }
  tetNext = bag[bagNextIndex];
  //tetCurrent = T_I; // hack
  switch(tetCurrent) {
      case T_I: tetRows = 4; tetCols = 4; tetData = t_i; break;
      case T_J: tetRows = 3; tetCols = 3; tetData = t_j; break;
      case T_L: tetRows = 3; tetCols = 3; tetData = t_l; break;
      case T_O: tetRows = 3; tetCols = 4; tetData = t_o; break;
      case T_S: tetRows = 3; tetCols = 3; tetData = t_s; break;
      case T_T: tetRows = 3; tetCols = 3; tetData = t_t; break;
      case T_Z: tetRows = 3; tetCols = 3; tetData = t_z; break;
      default: break;
  }
  tetCol = 3; 
  tetRow = 17; 
  tetRotation = 0;
  tetDataSize = tetRows * tetCols;
}

////////////////////////////////////
// MOVE/ROTATE/LAND TETROMINO
////////////////////////////////////

bool tetColliding(int8_t tr, int8_t tc, uint8_t ttr) { // row/col/rotation
  int mr = 0;
  int mc = 0;
  for (int r=0; r<tetRows; r++) {
      for (int c=0; c<tetCols; c++) {
        if (tetData[c + tetCols * r + tetDataSize * ttr]) {
          mr = tr + r; // mino row
          mc = tc + c; // mino col

          // check this BEFORE using these values as index for boardMap
          if (mr < 0 || mc < 0)
          {
            return true;
          }
          if (boardMap[mr][mc] || mc >= COLS) 
          {
            return true;
          }
        }
      }
    }
    return false;
}

bool tetCanMoveLeft() { return !tetColliding(tetRow, tetCol-1, tetRotation); }

bool tetCanMoveRight() { return !tetColliding(tetRow, tetCol+1, tetRotation); }

bool tetCanMoveDown() { return !tetColliding(tetRow-1, tetCol, tetRotation); }

bool tetMoveLeft() {
  if (tetCanMoveLeft()) {
    tetCol--;
    return true;
  }
  return false;
}

bool tetMoveRight() {
  if (tetCanMoveRight()) {
    tetCol++;
    return true;
  }
  return false;
}

bool tetMoveDown() {
  if (tetCanMoveDown()) {
    tetRow--;
    return true;
  }
  return false;
}

bool tetRotate(uint8_t tetNewRotation, uint8_t tetWallKickIndex) {
  if (tetCurrent == T_I) {

    for (uint8_t i = 0; i < 5; i++) {
      if (!tetColliding(tetRow+wallKickDataI[tetWallKickIndex][i][1], tetCol+wallKickDataI[tetWallKickIndex][i][0], tetNewRotation)) {
        tetCol = tetCol+wallKickDataI[tetWallKickIndex][i][0];
        tetRow = tetRow+wallKickDataI[tetWallKickIndex][i][1];
        tetRotation = tetNewRotation;
        return true;
      }
    }
    
  } else {
    
    for (uint8_t i = 0; i < 5; i++) {
      if (!tetColliding(tetRow+wallKickData[tetWallKickIndex][i][1], tetCol+wallKickData[tetWallKickIndex][i][0], tetNewRotation)) {
        tetCol = tetCol+wallKickData[tetWallKickIndex][i][0];
        tetRow = tetRow+wallKickData[tetWallKickIndex][i][1];
        tetRotation = tetNewRotation;
        return true;
      }
    }
  }
  return false;
}

bool tetRotateRight() {

  if (tetCurrent == T_O) {
    return true;
  } else {
    int tetNewRotation = (tetRotation == 3) ? 0 : tetRotation + 1;
    switch(tetRotation) {
      case 0: return tetRotate(tetNewRotation, 0);  break;
      case 1: return tetRotate(tetNewRotation, 2);  break;
      case 2: return tetRotate(tetNewRotation, 4);  break;
      case 3: return tetRotate(tetNewRotation, 6);  break;
    }
  }
  return false;
}

bool tetRotateLeft() {
  
  if (tetCurrent == T_O) {
    return true;
  } else {
    int tetNewRotation = (tetRotation == 0) ? 3 : tetRotation - 1;
    switch(tetRotation) {
      case 0: return tetRotate(tetNewRotation, 7);  break;
      case 1: return tetRotate(tetNewRotation, 1);  break;
      case 2: return tetRotate(tetNewRotation, 3);  break;
      case 3: return tetRotate(tetNewRotation, 5);  break;
    }
  }
  return false;
}

void tetLand() {
  int mr = 0;
  int mc = 0;
  for (int r=0; r<tetRows; r++) {
     for (int c=0; c<tetCols; c++) {
       if (tetData[c + tetCols * r + tetDataSize * tetRotation]) {
          mr = tetRow + r; // mino row
          mc = tetCol + c; // mino col
          boardMap[mr][mc] = true;
       }
     }
   }
   tetCurrent = T_NONE;
}

void updateTetromino() {
  
  // move left
  if (buttonPressed(BTN_LEFT)) 
  {
    tetMoveLeft();
  }
  
  // move right
  if (buttonPressed(BTN_RIGHT)) 
  {
    tetMoveRight();
  }
  
  
  // hard drop
  if (buttonPressed(BTN_DOWN)) 
  {
    // move down until not possible anymore
    while (tetCanMoveDown())
    {
      tetMoveDown();
    }
    tetLand(); // land the tetrominos after moving all the way down
  }
  else // just move down
  {
    if (!tetCanMoveDown()) {
      actionFrameCount++;
      if (actionFrameCount >= fallLockDelay) {
          tetLand();
          actionFrameCount = 0;
      }
    } else  if (actionFrameCount >= 0) { // 0 = fallspeed delay
        tetMoveDown();
        actionFrameCount = 0;
    } else {
      actionFrameCount++;
    }
  }

  // rotate
  if (buttonPressed(BTN_A)) 
  {
    if (rotationCount < MAX_ROTATIONS)
    {
      if (tetRotateRight()) 
      {
        rotationCount++;
      }
    }
  } 
  else if (buttonPressed(BTN_B)) 
  {
    if (rotationCount < MAX_ROTATIONS)
    {
      if (tetRotateLeft()) 
      {
        rotationCount++;
      }
    }
  }
}


////////////////////////////////////
// ANIMATIONS DATA
////////////////////////////////////


boolean updateRemoveRowsAnimationData() {

  if (actionFrameCount == boardRowsRemoveInterval) {
      dontDrawFilledRows = false;
      return true;
    } else {
      actionFrameCount++;
    }
    if (boardRowsRemoveBlinkFrameCount == boardRowsRemoveBlinkInterval) {
      boardRowsRemoveBlinkFrameCount = 0;
      dontDrawFilledRows = !dontDrawFilledRows;
    } else {
      boardRowsRemoveBlinkFrameCount++;
    }
    return false;
}

boolean updateFillRowsRowsAnimationData() {

  boardFillRow(actionFrameCount);
  actionFrameCount++;
  if (actionFrameCount == ROWS_VISIBLE) {
    return true;
  }
  return false;
}


////////////////////////////////////
// MAIN LOGIC
////////////////////////////////////

void setNewGameData() {
  randomSeedPiece = 0;
  score = 0;
  lines = 0;
  level = 0;
  bagNextIndex = 0;
  rotationCount = 0;
  actionFrameCount = 0;
  endFillAnimation = false;
  removeRowsAnimation = false;
  gameEnded = false;
  // reset bag (and shuffle after) to get the same bag every game (for current generation)
  bag[0] = T_I;
  bag[1] = T_J;
  bag[2] = T_L;
  bag[3] = T_O;
  bag[4] = T_S;
  bag[5] = T_T;
  bag[6] = T_Z;
  shuffleBag();
  nextTetromino();
  clearBoard();
  calculateNextPlacement();
}

void handleFilledRows()
{
  removeRowsAnimation = false;
  uint8_t removedRows = boardRemoveFilledRows();
  scoreAddClearRowsPoints(removedRows);
  lines += removedRows;
  uint8_t newLevel = lines / 10;
  actionFrameCount = 0;
  if (newLevel != level) {
    level = newLevel;
  }
}

void updateGame() {

  
  if (tetCurrent != T_NONE && !endFillAnimation) {
    updateTetromino();
    
    if (tetCurrent == T_NONE && haveRowsToRemove()) {
      // if fastLearn is enabled, skip animation for clearing lines
      if (fastLearn)
      {
        handleFilledRows();
      }
      else
      {
        removeRowsAnimation = true;
        actionFrameCount = 0;
        boardRowsRemoveBlinkFrameCount = 0;
        dontDrawFilledRows = false;
      }
    }

  } else 
  if (removeRowsAnimation) {

     if (updateRemoveRowsAnimationData()) { // ended
      handleFilledRows();
     }
    
  } else 
  if (endFillAnimation) {

    if (updateFillRowsRowsAnimationData()) { // ended
      endFillAnimation = false;
      gameEnded = true;
      if (score > highscore) {
        highscore = score;
      }
    }

  } else 
  {
    rotationCount = 0;
    nextTetromino();
    if (tetColliding(tetRow, tetCol, tetRotation)) {
      endFillAnimation = true;
      actionFrameCount = 0;
    }
    else
    {
      //unsigned long tmp = millis();
      calculateNextPlacement(); 
      //Serial.println(millis() - tmp);
    }
  }
  
}
