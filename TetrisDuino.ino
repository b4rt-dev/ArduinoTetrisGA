

#define byte uint8_t
 

#include <avr/pgmspace.h>
#include "globals.h"
#include "display.h"
#include "bitmaps.h"
#include "home.h"
#include "gameview.h"
#include "gamedata.h"
#include "gametetrominos.h"
#include "game.h"
#include "controls.h"

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] = {
  stateHome,
  stateHome,
  stateGameStart,
  stateGamePlaying,
  stateGamePause,
  stateGameOver
};

const unsigned long eachFrameMillis = 1000 / FPS; // FPS
unsigned long nextFrameStart = 0;


void setup() { 
  Serial.begin(115200);

  delay(10);
  randomSeed(analogRead(45)); //3
  
  setupDisplay();
  setupControls();
  loadHighscore();
  
}

void loop() {
  if (nextFrame()) {
    updateControls();
    ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
    // audio
    display.display();
    display.clearDisplay();
    //fpsAndRamAtInterval(5);
  }
}

boolean nextFrame() {
  unsigned long now = millis();
  if (now < nextFrameStart) {
    return false;
  }
  nextFrameStart = millis() + eachFrameMillis;
  return true;  
}

uint16_t getFreeRam() {
  //from http://www.controllerprojects.com/2011/05/23/determining-sram-usage-on-arduino/
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

static inline void fpsAndRamAtInterval(const int seconds){

}

