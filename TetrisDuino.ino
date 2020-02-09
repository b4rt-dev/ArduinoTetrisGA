/* TODO
Change datatypes: sync int, uint8_t and int8_t
*/

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
//
// to vastly increase the FPS on the OLED display without going out of spec with the I2C clock speed (400KHz)
// I modified the library to use a double buffer and only send the page that differs between the two buffers
// since most of the time only about two of the eight pages differ and need to be sent
// the I2C clock can easily be overclocked to further increase speed, but the display has still a locked frame rate
// and therefore looks kinda ugly (and too fast to see what happens) imo, so I did not do that.

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
#define PIN_WHEEL_DOWN  39
#define PIN_WHEEL_PRESS 38
#define PIN_WHEEL_UP    37

#define BTN_WHEEL_DOWN  0
#define BTN_WHEEL_PRESS 1
#define BTN_WHEEL_UP    2

// pins for leds
#define PIN_LEFT    26
#define PIN_DOWN    32
#define PIN_RIGHT   27
#define PIN_B       33
#define PIN_A       25

#define BTN_COUNT   5
#define BTN_LEFT    0
#define BTN_DOWN    1
#define BTN_RIGHT   2
#define BTN_B       3
#define BTN_A       4

bool ledsEnabled = true;

uint8_t btnStates[BTN_COUNT];       // button states, latched from btnPressed
uint8_t btnPressed[BTN_COUNT];      // virtual button pressed states for AI
uint8_t btnPressedPrev[BTN_COUNT];  // previous virtual button pressed states for AI, used for LEDs

// previous states of button to detect 'rising/falling edge'
int scrollWheelDownPrev   = 1;
int scrollWheelUpPrev     = 1;
int scrollWheelPressPrev  = 1;


////////////////////////////////////
// GAME DATA
////////////////////////////////////
#define ROWS_VISIBLE 20
#define ROWS 22
#define COLS 10
#define MAX_ROTATIONS 50  // to prevent player for delaying indefinitly by spinning
                          //  should not be a problem for the current AI implementation though

uint32_t score = 0;       // score of current game
uint32_t highscore = 0;   // score of game with the highest score (TODO implement this)
uint32_t lines = 0;       // number of cleared lines of current game
uint32_t highlines = 0;   // number of cleared lines of the game with the highest number of cleard lines (TODO implement this)
uint32_t level = 0;       // level of current game
uint32_t highlevel = 0;   // level of game with the highest level (TODO implement this)

uint32_t rotationCount = 0;   // number of rotations for current piece
bool boardMap[ROWS][COLS];    // representation of game board/map
                              //  row 0/0 == bottom left(row 0 bottom / top visible 19)

const uint32_t fallLockDelay = 2;  // in frames / resets on successuful rotation or shifting
uint32_t actionFrameCount = 0;     // used in things that need to count frames

// variables for row removal/blinking animation
bool boardRowsToRemove[ROWS] = {
  false, false, false, false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, false, false, false
  }; // to keep track of full rows to remove
const int8_t boardRowsRemoveInterval = 10;
int8_t boardRowsRemoveBlinkFrameCount = 0;
const int8_t boardRowsRemoveBlinkInterval = 1;
bool dontDrawFilledRows = false;

// tetriminos variables (TODO change uint8_t to int8_t)
int32_t tetCol = 4;        // current column, can be negative
int32_t tetRow = 17;       // current row, can be negative
uint32_t tetRotation = 0;  // current rotation
uint32_t tetRows = 3;       // number of rows in tetrominos
uint32_t tetCols = 3;       // number of columns in tetrominos
uint32_t tetDataSize = tetRows * tetCols; // size of tetrominos
Tetromino tetCurrent;     // current tetrominos piece
Tetromino tetNext;        // next tetrominos piece
const bool *tetData;      // pointer to data of current tetrominos
uint32_t bagNextIndex = 0;
Tetromino bag[] = {T_I,  T_J,  T_L,  T_O,  T_S,  T_T,  T_Z };

// flags
bool removeRowsAnimation = false;
bool endFillAnimation = false;     // game end fill animation
bool gameEnded = false;

// random number generator
// used to get the same "random" piece sequence for every game with the same randomSeedBase (generation)
unsigned long randomSeedBase = 37; // TODO set this to generation number * some high prime number
unsigned long randomSeedPiece = 0; // increases each shuffle by one


////////////////////////////////////
// GAME VIEW
////////////////////////////////////
#define MINO_SIZE 5
#define SCORE_X   28 
#define SCORE_Y   2
#define LINES_X   28
#define LINES_Y   9
#define LEVEL_X   28
#define LEVEL_Y   16
#define NEXT_X    52
#define NEXT_Y    8
#define BOARD_X   7
#define BOARD_Y   128 -3 -MINO_SIZE

unsigned long nextFrameStart = 0;
int frameTime = 0;

bool gamePaused = false;


////////////////////////////////////
// AI
////////////////////////////////////
typedef struct {
    int row;
    int col;
    int rot;
} position; // definition of a position

#define POSLIST_SIZE 60 // maximum size of list of positions
#define KEEP_BEST_SCORES 8 // amount of scores to keep during puring in dual prediction mode

position possiblePositions[POSLIST_SIZE] = {}; // create list of positions for current piece
position possibleNextPositions[POSLIST_SIZE] = {}; // create list of positions for next piece

// calculated targed positions for current tetrominos
int aiTargetRow = 0;
int aiTargetCol = 0;
int aiTargetRot = 0;

bool doHardDrop = false;
bool fastLearn = false;
bool twoPiece = true;


////////////////////////////////////
// GENETIC ALGORITHM
////////////////////////////////////




////////////////////////////////////
// MENU
////////////////////////////////////
// menu IDs
#define MENU_MAIN       0
#define MENU_CONFIG     1
#define MENU_LOG        2
#define MENU_AI_STATS   3

// number of items per menu
#define MENU_MAIN_ITEMS         3
#define MENU_CONFIG_ITEMS       8

// items id in main menu
#define MENU_MAIN_CONFIG        0
#define MENU_MAIN_LOG           1
#define MENU_MAIN_AI_STATS      2

// items id in config menu
#define MENU_CONFIG_HARDDROP    0
#define MENU_CONFIG_DELAY       1
#define MENU_CONFIG_LEDS        2
#define MENU_CONFIG_FASTLEARN   3
#define MENU_CONFIG_TWO_PIECE   4
#define MENU_CONFIG_PAUSED      5
#define MENU_CONFIG_RESETDATA   6
#define MENU_CONFIG_BACK        7

int currentMenu = MENU_MAIN;
int selectionID = 0;

unsigned long nextInputFrameStart = 0;
int nextInputFrameTime = 100;           // check input every 100ms

// logging
#define LOG_SIZE                50
String logString = "TO BE IMPLEMENTED";

unsigned long nextLogFrameStart = 0;
int nextLogFrameTime = 1000;           // update log every 1000ms


////////////////////////////////////
// SETUP
////////////////////////////////////
void setup() { 
  Serial.begin(115200); // fast serial

  delay(100);            // wait a bit
  logString.reserve(LOG_SIZE + 50);  // reserve memory for logstring operations, with 50 chars extra
  setupLEDs();
  setupDisplay();
  setupScrollWheel();
  setupControls();
}


////////////////////////////////////
// LOOP
////////////////////////////////////
void loop() {
  
  if (nextFrame()) {
    if (!gamePaused)
    {
      updateControls();
      switch(gameState) {
        case STATE_GAME_START:    stateGameStart();   break;
        case STATE_GAME_PLAYING:  stateGamePlaying(); break;
        case STATE_GA_UPDATE:     stateGAupdate();    break;
        default: break;
      }
    }

    processLog();
  }

  // use seperate timing process to check inputs once in a while
  if (timeToHandleInputs())
  {
    processInputs();
  }

  // use seperate timing to automatically update log when in log menu
  if (timeToUpdateLog())
  {
    if (currentMenu == MENU_LOG)
    {
      drawLogMenu();
      infoDisplay.display();
    }
  }
}

// returns true when it is time to draw/process the next frame
bool nextFrame() {
  unsigned long now = millis();
  if (now < nextFrameStart) {
    return false;
  }
  nextFrameStart = millis() + frameTime; 
  return true;
}

// returns true when it is time to handle/process inputs
bool timeToHandleInputs() {
  unsigned long now = millis();
  if (now < nextInputFrameStart) {
    return false;
  }
  nextInputFrameStart = millis() + nextInputFrameTime; 
  return true;
}


// returns true when it is time to update and redraw the log
bool timeToUpdateLog() {
  unsigned long now = millis();
  if (now < nextLogFrameStart) {
    return false;
  }
  nextLogFrameStart = millis() + nextLogFrameTime; 
  return true;
}