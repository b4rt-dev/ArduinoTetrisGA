/* AI.ino
Contains functions for the AI playing the game (so not the genetic algorithm).
*/

// Removes filled rows on given board
void AIremoveFilledRowsOnBoard(bool board[ROWS][COLS]) 
{
    for (int row=0; row < ROWS; row++)
    {
        int mc = 0; // mino count
        for (int col=0; col < COLS; col++)
        {
            if (board[row][col]) 
                mc++;
        }
        if (mc == COLS) 
        {
            for (int row2=row; row2 < ROWS; row2++)
            {
                for (int col=0; col < COLS; col++)
                {
                    if (row2 != ROWS-1) 
                    {
                        board[row2][col] = board[row2+1][col];
                    } 
                    else 
                    {
                        board[row2][col] = false;
                    }
                }
            }
            row--;
        }
    }
}

// Places given tetromino on given board at given position and rotation
void AIplaceOnBoard(bool board[ROWS][COLS], Tetromino piece, int tr, int tc, int ttr) 
{
    int ptetRows;          // number of rows in tetrominos
    int ptetCols;          // number of columns in tetrominos
    int ptetDataSize;      // size of tetrominos
    const bool *ptetData;  // pointer to data of tetrominos

    switch(piece) 
    {
      case T_I: ptetRows = 4; ptetCols = 4; ptetData = t_i; break;
      case T_J: ptetRows = 3; ptetCols = 3; ptetData = t_j; break;
      case T_L: ptetRows = 3; ptetCols = 3; ptetData = t_l; break;
      case T_O: ptetRows = 3; ptetCols = 4; ptetData = t_o; break;
      case T_S: ptetRows = 3; ptetCols = 3; ptetData = t_s; break;
      case T_T: ptetRows = 3; ptetCols = 3; ptetData = t_t; break;
      case T_Z: ptetRows = 3; ptetCols = 3; ptetData = t_z; break;
      default: break;
    }
    ptetDataSize = ptetRows * ptetCols;


    int mr = 0;
    int mc = 0;
    for (int r=0; r<ptetRows; r++) 
    {
        for (int c=0; c<ptetCols; c++) 
        {
            if (ptetData[c + ptetCols * r + ptetDataSize * ttr]) 
            {
                mr = tr + r; // mino row
                mc = tc + c; // mino col
                if (mr >= 0 && mr < ROWS && mc >= 0 && mc < COLS) // sanity check, should not be needed
                {
                    board[mr][mc] = true;
                }
            }
        }
    }
}


// Returns true if the given piece with the given position and rotation fits on the given board
bool AIplaceInvalid(bool board[ROWS][COLS], Tetromino piece, int tr, int tc, int ttr) 
{
    int ptetRows;          // number of rows in tetrominos
    int ptetCols;          // number of columns in tetrominos
    int ptetDataSize;      // size of tetrominos
    const bool *ptetData;  // pointer to data of tetrominos

    switch(piece) 
    {
      case T_I: ptetRows = 4; ptetCols = 4; ptetData = t_i; break;
      case T_J: ptetRows = 3; ptetCols = 3; ptetData = t_j; break;
      case T_L: ptetRows = 3; ptetCols = 3; ptetData = t_l; break;
      case T_O: ptetRows = 3; ptetCols = 4; ptetData = t_o; break;
      case T_S: ptetRows = 3; ptetCols = 3; ptetData = t_s; break;
      case T_T: ptetRows = 3; ptetCols = 3; ptetData = t_t; break;
      case T_Z: ptetRows = 3; ptetCols = 3; ptetData = t_z; break;
      default: break;
    }
    ptetDataSize = ptetRows * ptetCols;

    int mr = 0;
    int mc = 0;
    for (int r=0; r<ptetRows; r++) //tetRows should be correct, since we calculate for current piece
    {
        for (int c=0; c<ptetCols; c++) //tetColss should be correct, since we calculate for current piece
        {
            if (ptetData[c + ptetCols * r + ptetDataSize * ttr]) 
            {
                mr = tr + r; // mino row
                mc = tc + c; // mino col

                // check this BEFORE using these values as index for boardMap
                if (mr < 0 || mc < 0 || mc >= COLS)
                {
                    return true;
                }
                if (board[mr][mc]) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}


// Generates and returns list of all possible valid placements of current piece on current board
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
                        if (!AIplaceInvalid(boardMap, tetCurrent, row, col, rot) && AIplaceInvalid(boardMap, tetCurrent, row-1, col, rot))
                        {

                            // check if place can be reached by just falling from above
                            boolean rubbleAbove = false;
                            for (int higherRow = row; higherRow < ROWS-4; higherRow++)
                            {
                                if (AIplaceInvalid(boardMap, tetCurrent, higherRow, col, rot))
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


// Returns the height of heighest column on the given board
int scoreMaxHeight(bool board[ROWS][COLS]) 
{
    int max = 0;
    for (int col = 0; col < COLS; col++) 
    {
        int highestRow = 0;
        for (int row = 0; row < ROWS; row++) 
        {
            if (board[row][col]) 
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


// Returns the number of full rows on the given board
int scoreLinesCleared(bool board[ROWS][COLS]) 
{
    int lines = 0;
    for (int row = 0; row < ROWS; row++)
    {
        bool fullLine = true;
        for (int col = 0; col < COLS; col++) 
        {
            if (!board[row][col])
            {
                fullLine = false;
            }
        }
        if (fullLine)
        {
            lines++;
        }
    }
    return lines;
}
    

// Returns the number of holes on the given board
int scoreHoles(bool board[ROWS][COLS])
{
    int holes = 0;
    // calculate holes for each column
    for (int col = 0; col < COLS; col++) 
    {
        int colHoles = 0;
        bool foundBlock = false;
        // go from top to bottom
        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col]) 
            {
                foundBlock = true;
            } 
            else 
            {
                // only count the empty space as hole if there was a block found above
                if (foundBlock) 
                {
                    colHoles++;
                }
            }
        }
        holes = holes + colHoles;
    }
    return holes;
}


// Calculate the scores of all valid positions in possiblePositions
// and store the scores in the given array
void calculateAllScores(double scores[POSLIST_SIZE])
{
    bool testMap[ROWS][COLS];

    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        scores[i] = -DBL_MAX; // set minimum score by default
        if (possiblePositions[i].row != -99) // if valid position
        {
            // copy of board for calculation purposes
            memcpy(testMap, boardMap, ROWS*COLS*sizeof(bool));
            // place the piece on the board
            AIplaceOnBoard(testMap, tetCurrent, possiblePositions[i].row, possiblePositions[i].col, possiblePositions[i].rot);
            // calculate the score
            scores[i] = calculateScore(testMap);
        }
    }
}


// Returns the score of the given board
// applies weights on subscores
double calculateScore(bool board[ROWS][COLS])
{
    return
        -1 * scoreMaxHeight(board) +
        3 * scoreLinesCleared(board) +
        -1.5 * scoreHoles(board)
        ;
}


// Returns the index of the given array of scores
// with the heighest score value
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

// almost a Java like function name...
position selectBestPlacementUsingNextPiece(double currentScores[POSLIST_SIZE]) 
{
    // to keep track of the position with the highest score
    double highestScore = -DBL_MAX;
    // position with the highest score
    position bestPosition = {-99, -99, -99};

    // for all positions of current piece
    for (int currentPos = 0; currentPos < POSLIST_SIZE; currentPos++)
    { 
        // if it is a valid position
        if (possiblePositions[currentPos].row != -99)
        {

            // place current piece on board so we can calculate the placement and score of the next piece
            bool testMap[ROWS][COLS];
            memcpy(testMap, boardMap, ROWS*COLS*sizeof(bool));
            AIplaceOnBoard(testMap, tetCurrent, possiblePositions[currentPos].row, possiblePositions[currentPos].col, possiblePositions[currentPos].rot);
            AIremoveFilledRowsOnBoard(testMap); // also remove the possible cleared lines with the current tetrominos

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
                        if (!(tetNext == T_O && rot != 0))
                        {
                            if (posCounter < POSLIST_SIZE)
                            {
                                if (!AIplaceInvalid(testMap, tetNext, row, col, rot) && AIplaceInvalid(testMap, tetNext, row-1, col, rot))
                                {

                                    // check if place can be reached by just falling from above
                                    boolean rubbleAbove = false;
                                    for (int higherRow = row; higherRow < ROWS-4; higherRow++)
                                    {
                                        if (AIplaceInvalid(testMap, tetNext, higherRow, col, rot))
                                        {
                                          rubbleAbove = true;
                                        }
                                    }
                                    if (!rubbleAbove) // valid placement
                                    {
                                        // calculate the score of the current placement

                                        double score = -DBL_MAX; // set minimum score by default
                                        
                                        // copy of board for calculation purposes
                                        bool doubleTestMap[ROWS][COLS];
                                        memcpy(doubleTestMap, testMap, ROWS*COLS*sizeof(bool));
                                        AIplaceOnBoard(doubleTestMap, tetNext, row, col, rot);

                                        // calculate score and add score of current piece
                                        // TODO add weight to one of these scores?
                                        score = calculateScore(doubleTestMap) + currentScores[currentPos];

                                        if (score > highestScore)
                                        {
                                            highestScore = score;

                                            bestPosition.row = possiblePositions[currentPos].row;
                                            bestPosition.col = possiblePositions[currentPos].col;
                                            bestPosition.rot = possiblePositions[currentPos].rot;
                                        }

                                        posCounter++;
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bestPosition;
}


// Returns heighest value in scores array, and write the index in index
double heighestValidScore(double scores[POSLIST_SIZE], int &index)
{
    double heighest = -DBL_MAX;
    index = 0;
    for (int i = 0; i < POSLIST_SIZE; i ++)
    {
        if (scores[i] > heighest)
        {
            heighest = scores[i];
            index = i;
        }
    }
    return heighest;
}


// Keep remove the worst scores. Threshold defined in
void pruneWorstScores(double scores[POSLIST_SIZE])
{
    double prunedScores[POSLIST_SIZE];
    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        prunedScores[i] = -DBL_MAX;
    }

    for (int i = 0; i < KEEP_BEST_SCORES; i++)
    {
        int index = 0;
        double heighest = heighestValidScore(scores, index);
        prunedScores[index] = heighest;
        scores[index] = -DBL_MAX;
    }

    memcpy(scores, prunedScores, sizeof(prunedScores));

    // update possiblePositions list
    for (int i = 0; i < POSLIST_SIZE; i++)
    {
        if (scores[i] == -DBL_MAX)
        {
            possiblePositions[i].row = -99;
            possiblePositions[i].col = -99;
            possiblePositions[i].rot = -99;
        }
    }
}


void calculateNextPlacement() 
{
    generateAllPossiblePlacements();

    double currentScores[POSLIST_SIZE];
    calculateAllScores(currentScores);

    // use next piece in calculation
    if (twoPiece)
    {
        pruneWorstScores(currentScores);

        position bestPosition = selectBestPlacementUsingNextPiece(currentScores);

        aiTargetRow = bestPosition.row;
        aiTargetCol = bestPosition.col;
        aiTargetRot = bestPosition.rot;
    }
    else // do not use next piece in calculation
    {
        int bestPosIndex = selectBestPlacement(currentScores);
        aiTargetRow = possiblePositions[bestPosIndex].row;
        aiTargetCol = possiblePositions[bestPosIndex].col;
        aiTargetRot = possiblePositions[bestPosIndex].rot;
    }
}


// Presses virtual buttons of the tetris game 
// based on the calculated best position of the current piece
void doAImovement()
{
    // reset button presses
    setButton(BTN_LEFT, false);
    setButton(BTN_RIGHT, false);
    setButton(BTN_DOWN, false);
    setButton(BTN_B, false);
    setButton(BTN_A, false);

    // if movement might be needed (to prevent any button being held during line clear animations)
    if (!(tetCol == aiTargetCol && tetRow == aiTargetRow && tetRotation == aiTargetRot))
    {
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
        if (!adjusted && doHardDrop)
        {
            setButton(BTN_DOWN, true);
        }
    }

}