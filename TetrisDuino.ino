////////////////////////////////////
// GENERAL INCLUDES
////////////////////////////////////
#include <EEPROM.h>
#include <float.h>


////////////////////////////////////
// CONSTANT DATA
////////////////////////////////////
// Add tetrominos definitions
#include "gametetrominos.h"

// Add bitmap data
#include "bitmaps.h"


////////////////////////////////////
// DISPLAYS
////////////////////////////////////
// the SH1106 library is from https://github.com/nhatuan84/esp32-sh1106-oled
// it is the modified Adafruit library for SH1106 and works perfectly on the TTGO-Eight
// the resolution is 128x64.
// in order to make the library work at the same time as the 5510 library, you have to do
// two things:
// - comment out the lines typedef volatile uint8_t PortReg; and typedef uint8_t PortMask;
//    in Adafruit_SH1106.h
// - synchronize the definition of BLACK and WHITE in Adafruit_SH1106.h and Adafruit_PCD8544.h
//    (for example, swap values of BLACK and WHITE in Adafruit_PCD8544.h)

// the Tetris game is displayed on the OLED display (display)
// the AI/GA info is displayed on the 5510 LCD (infoDisplay)
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_PCD8544.h>
#include <Fonts/Picopixel.h>

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);
Adafruit_PCD8544 infoDisplay = Adafruit_PCD8544(0, 4, 2, 15, 13); // using software SPI

bool evenGameNumber = true; // for inverting the display every other game

// Game size on display
#define GAME_WIDTH 64
#define GAME_HEIGHT 128


////////////////////////////////////
// GAME STATES
////////////////////////////////////
#define STATE_GAME_START        0
#define STATE_GAME_PLAYING      1
#define STATE_GA_UPDATE         2

byte gameState = STATE_GAME_START; // current state of the game


////////////////////////////////////
// BUTTONS
////////////////////////////////////
#define PIN_WHEEL_DOWN  37
#define PIN_WHEEL_PRESS 38
#define PIN_WHEEL_UP    39

#define BTN_COUNT   5
#define BTN_LEFT    0
#define BTN_DOWN    1
#define BTN_RIGHT   2
#define BTN_B       3
#define BTN_A       4

uint8_t btnStates[BTN_COUNT];
uint8_t btnPressed[BTN_COUNT]; // virtual button pressed states for AI


// Game data
#define ROWS_VISIBLE 20
#define ROWS 22
#define COLS 10
#define MAX_ROTATIONS 50  // to prevent player for delaying indefinitly by spinning

long score = 0;
long highscore = 0;
long lines = 0;
long level = 0;

int rotationCount = 0;  // number of rotations for current piece
boolean boardMap[ROWS][COLS]; // row 0/0 == bottom left(row 0 bottom / top visible 19)

const uint8_t fallLockDelay = 11; // in frames / resets on successuful rotation or shifting
uint8_t actionFrameCount = 0;
boolean fallFast = false;
boolean fallFastEnabled = true;

boolean boardRowsToRemove[ROWS] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
const int8_t boardRowsRemoveInterval = 10;
int8_t boardRowsRemoveBlinkFrameCount = 0;
const int8_t boardRowsRemoveBlinkInterval = 1;
boolean dontDrawFilledRows = false; // for blink animation blah...

int8_t tetCol = 4; // position
int8_t tetRow = 17;// position
int8_t tetRows = 3; // array size
int8_t tetCols = 3;
uint8_t tetDataSize = tetRows * tetCols;
uint8_t tetRotation = 0;
Tetromino tetCurrent;
Tetromino tetNext;
const bool *tetData;
int8_t r = 0; // za loops
int8_t c = 0;
int8_t mr = 0; // mino row
int8_t mc = 0; // mino col

boolean removeRowsAnimation = false;
boolean endFillAnimation = false; // game end fill animation
boolean gameEnded = false;

int bagNextIndex = 0;
Tetromino bag[] = {T_I,  T_J,  T_L,  T_O,  T_S,  T_T,  T_Z };

// Game view
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



// AI
typedef struct {
    int row;
    int col;
    int rot;
} position;

#define POSLIST_SIZE 60
position possiblePositions[POSLIST_SIZE] = {};

int aiTargetRow = 0;
int aiTargetCol = 0;
int aiTargetRot = 0;




void setup() { 
  Serial.begin(115200);

  // set scroll wheel buttons as inputs
  pinMode(PIN_WHEEL_UP, INPUT);
  pinMode(PIN_WHEEL_PRESS, INPUT);
  pinMode(PIN_WHEEL_DOWN, INPUT);

  delay(10);
  randomSeed(analogRead(0));
  
  setupDisplay();
  setupControls();
  
}

void loop() {
  
  if (nextFrame()) {
    updateControls();
    switch(gameState) {
      case STATE_GAME_START:    stateGameStart();   break;
      case STATE_GAME_PLAYING:  stateGamePlaying(); break;
      case STATE_GA_UPDATE:     stateGAupdate();    break;
      default: break;
    }
    display.display();
    display.clearDisplay();
    drawInputs();
  }
}

// Just draw as fast as possible for now (I2C is bottleneck here)
bool nextFrame() {
  return true;
}
