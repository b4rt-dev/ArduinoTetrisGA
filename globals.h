#ifndef GLOBALS_H
#define GLOBALS_H

#define GAME_WIDTH 64
#define GAME_HEIGHT 128

// States
//TODO remove unwanted states
#define STATE_SPLASH            0
#define STATE_HOME              1
#define STATE_GAME_START        2
#define STATE_GAME_PLAYING      3
#define STATE_GAME_PAUSE        4
#define STATE_GAME_OVER         5

// State of the game
byte gameState = STATE_GAME_START;

#endif
