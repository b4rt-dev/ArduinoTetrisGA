void AIplaceOnBoard(bool testMap[ROWS][COLS], int8_t tr, int8_t tc, uint8_t ttr) {
    int mr = 0;
    int mc = 0;
  for (int r=0; r<tetRows; r++) {
     for (int c=0; c<tetCols; c++) {
       if (tetData[c + tetCols * r + tetDataSize * ttr]) {
          mr = tr + r; // mino row
          mc = tc + c; // mino col
          if (mr >= 0 && mr < ROWS && mc >= 0 && mc < COLS) // sanity check, should not be needed
            testMap[mr][mc] = true;
       }
     }
   }
}

bool AIplaceInvalid(bool testMap[ROWS][COLS], int8_t tr, int8_t tc, uint8_t ttr) { // row/col/rotation
    int mr = 0;
    int mc = 0;
    for (int r=0; r<tetRows; r++) //tetRows should be correct, since we calculate for current piece
    {
        for (int c=0; c<tetCols; c++) //tetColss should be correct, since we calculate for current piece
        {
            if (tetData[c + tetCols * r + tetDataSize * ttr]) 
            {
                mr = tr + r; // mino row
                mc = tc + c; // mino col

                // check this BEFORE using these values as index for boardMap
                if (mr < 0 || mc < 0 || mc >= COLS)
                {
                    return true;
                }
                if (testMap[mr][mc]) 
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

    for (int row = -4; row < ROWS_VISIBLE ; row++) 
    {
        for (int col = -4; col < COLS + 4; col++) 
        {
            for (int rot = 0; rot < 4; rot++) 
            {
                // rotation does not matter for O pieces, but because of some bug,
                // the third rotation of the O piece results in inaccurate placements
                // so we fix this by only calculating the first rotation which does not have this bug
                if (!(tetCurrent == T_O && rot != 0))
                {
                    if (posCounter < POSLIST_SIZE)
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
    }
}



int scoreMaxHeight(bool testMap[ROWS][COLS]) {
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

    double scores[POSLIST_SIZE];
    calculateScores(scores);

    //calculate minimum

    int bestPosIndex = selectBestPlacement(scores);
    aiTargetRow = possiblePositions[bestPosIndex].row;
    aiTargetCol = possiblePositions[bestPosIndex].col;
    aiTargetRot = possiblePositions[bestPosIndex].rot;

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
    if (tetRotation != aiTargetRot)
    {
        // check if it is more efficient to rotate counter clockwise
        if (aiTargetRot == tetRotation -1 || (aiTargetRot == 3 && tetRotation == 0))
        {
            setButton(BTN_B, true);
        }
        else // else prefer to rotate clockwise
        {
            setButton(BTN_A, true); 
        }
        adjusted = true;
    }

    // do hard drop if no further movements are needed
    if (!adjusted)
    {
        setButton(BTN_DOWN, true);
    }



}