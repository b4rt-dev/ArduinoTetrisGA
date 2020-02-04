#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "globals.h"
#include "display.h"
#include "bitmaps.h"
#include "gamedata.h"

#define MINO_SIZE 5
#define SCORE_X 28 
#define SCORE_Y 2
#define LINES_X 28
#define LINES_Y 9
#define LEVEL_X 28
#define LEVEL_Y 16
#define NEXT_X 48
#define NEXT_Y 6
#define BOARD_X 7
#define BOARD_Y 128 -3 -MINO_SIZE

int minoSize = MINO_SIZE;
int minoRow = 0;
int minoCol = 0;

void drawGameTetromino() 
{
  if (tetCurrent != T_NONE) 
  {
    for (r=0; r<tetRows; r++) 
    {
      for ( c=0; c<tetCols; c++) 
      {
        if (tetData[c + tetCols * r + tetDataSize * tetRotation]) 
        {
          minoRow = tetRow + r;
          minoCol = tetCol + c;
          if (minoRow < ROWS_VISIBLE) 
          {
            display.drawBitmap(BOARD_X + minoCol * minoSize, BOARD_Y - minoRow * minoSize, MINO, minoSize, minoSize, WHITE);
          }
        }
      }
    }
  }
}


void drawGameMinos() 
{
  for (uint8_t row=0; row < ROWS_VISIBLE; row++)
  {
    if (!dontDrawFilledRows || (dontDrawFilledRows && !boardRowsToRemove[row])) 
    {
      for (uint8_t col=0; col < COLS; col++)
      {
        if (boardMap[row][col] == true)
        {
          display.drawBitmap(BOARD_X + col * minoSize, BOARD_Y - row * minoSize, MINO, minoSize, minoSize, WHITE);
        }
      }
    }
  }
}

void drawNumber(char num[], int numLength, int posX, int poxY) {
  int numPosX = posX;
  for(int i=0; i<numLength; i++) {
    if (num[i] == '\0') break;
    switch(num[i]) {
      case '1': display.drawBitmap(numPosX, poxY, N1, 2, 5, 1, 0); break;
      case '2': display.drawBitmap(numPosX, poxY, N2, 3, 5, 1, 0); break;
      case '3': display.drawBitmap(numPosX, poxY, N3, 3, 5, 1, 0); break;
      case '4': display.drawBitmap(numPosX, poxY, N4, 3, 5, 1, 0); break;
      case '5': display.drawBitmap(numPosX, poxY, N5, 3, 5, 1, 0); break;
      case '6': display.drawBitmap(numPosX, poxY, N6, 3, 5, 1, 0); break;
      case '7': display.drawBitmap(numPosX, poxY, N7, 3, 5, 1, 0); break;
      case '8': display.drawBitmap(numPosX, poxY, N8, 3, 5, 1, 0); break;
      case '9': display.drawBitmap(numPosX, poxY, N9, 3, 5, 1, 0); break;
      default: display.drawBitmap(numPosX, poxY, N0, 3, 5, 1, 0);
    }
    numPosX +=  (num[i] == '1') ? 3 : 4;
  }
}

void drawGameScoreLinesAndLevel() {
  // Score to array
  char scoreList[10];
  sprintf(scoreList, "%ld", score); //ltoa(val, buffer, 10);
  drawNumber(scoreList, sizeof(scoreList), SCORE_X, SCORE_Y);
  
  // Lines to array
  char linesList[5];
  sprintf(linesList, "%d", lines);
  drawNumber(linesList, sizeof(linesList), LINES_X, LINES_Y);
  
  // Level to array
  char leveList[5];
  sprintf(leveList, "%d", level);
  drawNumber(leveList, sizeof(leveList), LEVEL_X, LEVEL_Y);
}

void drawGameNextTetromino() {
  switch(tetNext) {
    case T_I: display.drawBitmap(NEXT_X, NEXT_Y, I, 6, 12, 1, 0); break;
    case T_J: display.drawBitmap(NEXT_X, NEXT_Y, J, 8, 9, 1, 0); break;
    case T_L: display.drawBitmap(NEXT_X, NEXT_Y, L, 8, 9, 1, 0); break;
    case T_O: display.drawBitmap(NEXT_X, NEXT_Y, O, 8, 6, 1, 0); break;
    case T_S: display.drawBitmap(NEXT_X, NEXT_Y, S, 9, 6, 1, 0); break;
    case T_T: display.drawBitmap(NEXT_X, NEXT_Y, T, 9, 6, 1, 0); break;
    case T_Z: display.drawBitmap(NEXT_X, NEXT_Y, Z, 9, 6, 1, 0); break;
    default: break;
  }
}

void drawGameBackground() {
  display.drawBitmap(0, 0, GAME_BG, GAME_WIDTH, GAME_HEIGHT, WHITE);
}


void drawGame() {
  drawGameBackground();
  drawGameScoreLinesAndLevel();
  drawGameMinos();
  drawGameTetromino();
  drawGameNextTetromino();
}



#endif
