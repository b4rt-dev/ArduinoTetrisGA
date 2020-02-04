#ifndef CONTROLS_H
#define CONTROLS_H

#define BTN_COUNT   5
#define BTN_LEFT    0
#define BTN_DOWN    1
#define BTN_RIGHT   2
#define BTN_B       3
#define BTN_A       4

#define BTN_LEFT_PIN    10
#define BTN_DOWN_PIN    11
#define BTN_RIGHT_PIN   12
#define BTN_B_PIN       13
#define BTN_A_PIN       14

uint8_t btnPins[BTN_COUNT];
uint8_t btnStates[BTN_COUNT];
uint8_t btnPressed[BTN_COUNT]; //virtual button pressed states for AI

void setupControls() {
  btnPins[BTN_LEFT] = BTN_LEFT_PIN;
  btnPins[BTN_DOWN] = BTN_DOWN_PIN;
  btnPins[BTN_RIGHT] = BTN_RIGHT_PIN;
  btnPins[BTN_B] = BTN_B_PIN;
  btnPins[BTN_A] = BTN_A_PIN;

  for (uint8_t thisButton = 0; thisButton < BTN_COUNT; thisButton++) {
        pinMode(btnPins[thisButton], INPUT_PULLUP);
        btnStates[thisButton] = 0;
        btnPressed[thisButton] = 0;
  }
}


/*
//old version for when buttons were used
void updateControlsManual() {
  for (uint8_t thisButton = 0; thisButton < BTN_COUNT; thisButton++) {
        if (digitalRead(btnPins[thisButton]) == LOW) {
            btnStates[thisButton]++;
        } else {
            if (btnStates[thisButton] == 0)
                continue;
            if (btnStates[thisButton] == 0xFF)//if previously released
                btnStates[thisButton] = 0; //set to idle
            else
                btnStates[thisButton] = 0xFF; //button just released
        }
    }
}*/

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

boolean buttonPressed(uint8_t button) {
    if (btnStates[button] == 1) {
        return true;
    } else {
        return false;
    }
}




boolean buttonRepeat(uint8_t button, uint8_t period) {
    if (period <= 1) {
        if ((btnStates[button] != 0xFF) && (btnStates[button]))
            return true;
    } else {
        if ((btnStates[button] != 0xFF) && ((btnStates[button] % period) == 1))
            return true;
    }
    return false;
}

uint8_t buttonTimeHeld(uint8_t button){
    if(btnStates[button] != 0xFF) {
        return btnStates[button];
    } else {
        return 0;
    }
}

boolean buttonPressedAny() {
  return (buttonPressed(BTN_LEFT) || buttonPressed(BTN_DOWN) || buttonPressed(BTN_RIGHT) || buttonPressed(BTN_B) || buttonPressed(BTN_A));
}

#endif
