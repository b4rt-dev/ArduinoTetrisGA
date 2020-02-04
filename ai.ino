void AIplaceOnBoard(bool testMap[ROWS][COLS], int8_t tr, int8_t tc, uint8_t ttr) {
    int amr = 0;
    int amc = 0;
  for (r=0; r<tetRows; r++) {
     for (c=0; c<tetCols; c++) {
       if (tetData[c + tetCols * r + tetDataSize * ttr]) {
          amr = tr + r; // mino row
          amc = tc + c; // mino col
          if (amr >= 0 && amr < ROWS && amc >= 0 && amc < COLS) // sanity check, should not be needed
            testMap[amr][amc] = true;
       }
     }
   }
}

bool AIplaceInvalid(bool testMap[ROWS][COLS], int8_t tr, int8_t tc, uint8_t ttr) { // row/col/rotation
    int amr = 0;
    int amc = 0;
    for (r=0; r<tetRows; r++) //tetRows should be correct, since we calculate for current piece
    {
        for (c=0; c<tetCols; c++) //tetColss should be correct, since we calculate for current piece
        {
            if (tetData[c + tetCols * r + tetDataSize * ttr]) 
            {
                amr = tr + r; // mino row
                amc = tc + c; // mino col

                // check this BEFORE using these values as index for boardMap
                if (amr < 0 || amc < 0 || amc >= COLS)
                {
                    return true;
                }
                if (testMap[amr][amc]) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void generateAllPossiblePlacements() 
{
    
    // clear position list by setting invalid numbers
    // since 0, 0, 0 could be a valid position
    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        possiblePositions[i].row = -99;
        possiblePositions[i].col = -99;
        possiblePositions[i].rot = -99;
    }

    int posCounter = 0;

    for (int row = -4; row < ROWS + 4; row++) 
    {
        for (int col = -4; col < COLS + 4; col++) 
        {
            for (int rot = 0; rot < 4; rot++) 
            {
                if (!AIplaceInvalid(boardMap, row, col, rot) && AIplaceInvalid(boardMap, row-1, col, rot))
                {

                    // check if place can be reached by just falling from above
                    boolean rubbleAbove = false;
                    for (int higherRow = row; higherRow < ROWS-4; higherRow++)
                    {
                        if (AIplaceInvalid(boardMap, higherRow, col, rot))
                        {
                          rubbleAbove = true;
                        }
                    }
                    if (!rubbleAbove)
                    {
                        // valid placement, so store it in the poslist
                        possiblePositions[posCounter].row = row;
                        possiblePositions[posCounter].col = col;
                        possiblePositions[posCounter].rot = rot;
                        posCounter++;
                    }

                }
            }
        }
    }
}



/*

bool testMap[ROWS][COLS];
    //create board with piece
    memcpy(testMap, boardMap, ROWS*COLS*sizeof(int));

 memcpy(testMap, boardMap, ROWS*COLS*sizeof(int));
                    
                    AIplaceOnBoard(testMap, row, col, rot);

                    for (int x = ROWS-1; x >= 0; x--) {
                      for (int y = 0; y < COLS; y++) {
                          Serial.print(testMap[x][y]);
                      }
                      Serial.println();
                    }


*/

int scoreMaxHeight(bool testMap[ROWS][COLS]) {

/*
    for (int x = ROWS-1; x >= 0; x--) {
      for (int y = 0; y < COLS; y++) {
          Serial.print(testMap[x][y]);
      }
      Serial.println();
    }
*/

    int max = 0;
    for (int col = 0; col < COLS; col++) 
    {
        int highestRow = 0;
        for (int row = 0; row < ROWS; row++) 
        {
            if (testMap[row][col]) 
            {

                if (row +1 > highestRow) // +1 because the bottom row is row zero
                { 
                    highestRow = row +1; 
                }
            }
        }
        if (highestRow > max){
            max = highestRow;
        }

    }
    return max;
}

void calculateScores(double scores[POSLIST_SIZE])
{
    bool testMap[ROWS][COLS];

    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        scores[i] = -DBL_MAX; // set minimum score by default
        if (possiblePositions[i].row != -99) // if valid position
        {
            // copy of board for calculation purposes
            
            memcpy(testMap, boardMap, ROWS*COLS*sizeof(bool));

            AIplaceOnBoard(testMap, possiblePositions[i].row, possiblePositions[i].col, possiblePositions[i].rot);

            scores[i] = -1 * scoreMaxHeight(testMap);
            
        }
    }
}

// select pos with highest score
int selectBestPlacement(double scores[POSLIST_SIZE]) {
  double highestScore = -DBL_MAX;
  int bestPosIndex = 0;
  for (int i = 0; i < POSLIST_SIZE; i++)
  {
    if (possiblePositions[i].row != -99)
    {
      if (scores[i] > highestScore)
      {
        highestScore = scores[i];
        bestPosIndex = i;
      }
    }
  }
  return bestPosIndex;
}


void calculateNextPlacement() 
{

    generateAllPossiblePlacements();

/*
    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        // check if position is valid
        if (possiblePositions[i].row != -99)
        {
            Serial.println(possiblePositions[i].col);
            Serial.println(possiblePositions[i].row);
            Serial.println(possiblePositions[i].rot);
            Serial.println();
        }
        
    }
*/

    double scores[POSLIST_SIZE];
    calculateScores(scores);

/*
    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        Serial.println(scores[i]);
    }
    Serial.println(scores[selectBestPlacement(scores)]);

*/

    //calculate minimum

    int bestPosIndex = selectBestPlacement(scores);
    aiTargetRow = possiblePositions[bestPosIndex].row;
    aiTargetCol = possiblePositions[bestPosIndex].col;
    aiTargetRot = possiblePositions[bestPosIndex].rot;

/*
    Serial.println(aiTargetRow);
    Serial.println(aiTargetCol);
    Serial.println(aiTargetRot);
*/
}


void doAImovement()
{
    // reset button presses
    setButton(BTN_LEFT, false);
    setButton(BTN_RIGHT, false);
    setButton(BTN_DOWN, false);
    setButton(BTN_B, false);
    setButton(BTN_A, false);

    // keep track if we changed anything
    bool adjusted = false;

    //TODO add fix for not being able to rotate after hugging the wall
    if (tetCol > aiTargetCol)
    {
        setButton(BTN_LEFT, true);
        adjusted = true;
    }
    if (tetCol < aiTargetCol)
    {
        setButton(BTN_RIGHT, true);
        adjusted = true;
    }
    if (tetRotation != aiTargetRot) // TODO check values of rotation to determine A or B press
    {
        setButton(BTN_A, true);
        adjusted = true;
    }

    // TODO harddrop if ajusted = false;




}