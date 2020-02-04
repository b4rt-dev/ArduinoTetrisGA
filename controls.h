#ifndef CONTROLS_H
#define CONTROLS_H

#define BTN_COUNT   5
#define BTN_LEFT    0
#define BTN_DOWN    1
#define BTN_RIGHT   2
#define BTN_B       3
#define BTN_A       4

uint8_t btnPins[BTN_COUNT];
uint8_t btnStates[BTN_COUNT];
uint8_t btnPressed[BTN_COUNT]; //virtual button pressed states for AI

void setupControls() {

  for (uint8_t thisButton = 0; thisButton < BTN_COUNT; thisButton++) {
        btnStates[thisButton] = 0;
        btnPressed[thisButton] = 0;
  }
}

//Placeholder until AI controlls input
void updateControls() {
    for (uint8_t thisButton = 0; thisButton < BTN_COUNT; thisButton++) {
        if (btnPressed[thisButton] != 0) {
            btnStates[thisButton] = 1;
        } else {
            btnStates[thisButton] = 0;
        }
    }
}

//Set virtual button (for AI)
void setButton(uint8_t button, bool pressed)
{
    if (pressed)
        btnPressed[button] = 1;
    else
        btnPressed[button] = 0;
}

bool buttonPressed(uint8_t button) {
    if (btnStates[button] == 1) {
        return true;
    } else {
        return false;
    }
}

#endif
