
void setupControls() {

  for (uint8_t thisButton = 0; thisButton < BTN_COUNT; thisButton++) {
        btnStates[thisButton] = 0;
        btnPressed[thisButton] = 0;
  }
}

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
