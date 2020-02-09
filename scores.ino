// Returns the height difference between the heighest and lowest column on the given board
int scoreHeightDifference(bool board[ROWS][COLS]) 
{
    int max = 0;
    for (int col = 0; col < COLS; col++) 
    {
        int colHeight = 0;
        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col]) 
            {
                colHeight = row +1; 
                break;
            }
        }
        if (colHeight > max){
            max = colHeight;
        }
    }
    
    int min = ROWS;
    for (int col = 0; col < COLS; col++) 
    {
        int colHeight = 0;
        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col]) 
            {
                colHeight = row +1; 
                break;
            }
        }
        if (colHeight < min){
            min = colHeight;
        }
    }

    return max - min;
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


// Returns the number of wells with a depth >= 2
int scoreBigWells(bool board[ROWS][COLS])
{
    int bigWells = 0;

    // calculate well depth for each column
    for (int col = 0; col < COLS; col++) 
    {
        // get height of column
        int colHeight = 0;    

        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col]) 
            {
                colHeight = row + 1;    // row + 1 because the bottom row is 0 
                break;
            } 
        }

        // get height of column left of it
        int lColHeight = 0;

        if (col == 0) // col -1 (outside board) is ROWS high
            lColHeight = ROWS;
        else
        {
            for (int row = ROWS-1; row >= 0; row--) 
            {
                if (board[row][col-1]) 
                {
                    lColHeight = row + 1;    // row + 1 because the bottom row is 0 
                    break;
                } 
            }
        }
        

        // get height of column right of it
        int rColHeight = 0;

        if (col == COLS -1) // col COL (outside board) is ROWS high
            rColHeight = ROWS;
        else
        {
            for (int row = ROWS-1; row >= 0; row--) 
            {
                if (board[row][col+1]) 
                {
                    rColHeight = row + 1;    // row + 1 because the bottom row is 0 
                    break;
                } 
            }
        }

        // if the current column is a big well
        if (lColHeight > colHeight+1 && rColHeight > colHeight+1)
        {
            bigWells++;
        }

    }

    return bigWells;
}


// Returns the max horizontal distances between any hole
int scoreMaxHorHoleDistance(bool board[ROWS][COLS])
{
    int holeDistance = 0;

    int leftHole = COLS-1;
    int rightHole = 0;
    
    // calculate holes for each column
    for (int col = 0; col < COLS; col++) 
    {
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
                    if (col < leftHole)
                        leftHole = col;
                    if (col > rightHole)
                        rightHole = col;
                    break;
                }
            }
        }
    }

    if (leftHole > rightHole) // if no hole was found
        holeDistance = 0;
    else
    {
        holeDistance = rightHole - leftHole; // returns 0 if only one hole if found
    }

    return holeDistance;
}


// Returns the sum of height differences between adjacent columns
int scoreBumpiness(bool board[ROWS][COLS]) 
{
    int bumpiness = 0;

    for (int col = 0; col < COLS-1; col++) // COLS-1 because the most right column has no column to its right
    {

        // get height of column
        int colHeight = 0;
        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col]) 
            {
                colHeight = row +1; 
                break;
            }
        }
        
        // get height of column right adjacent column
        int rColHeight = 0;
        for (int row = ROWS-1; row >= 0; row--) 
        {
            if (board[row][col+1]) 
            {
                rColHeight = row +1; 
                break;
            }
        }

        bumpiness += abs(colHeight - rColHeight);

    }

    return bumpiness;
}