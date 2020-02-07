

void setupDisplay() {
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    display.setRotation(1);
    display.clearDisplay();

    // reduce brightness
    display.sh1106_command(0x81);
    display.sh1106_command(50);

    Wire.setClock(400000); // set I2C speed to 400KHz (max according to spec for SH1106 display) to increase FPS

    infoDisplay.begin();
    infoDisplay.setContrast(63); // 63 seems to work fine for my display
    infoDisplay.invertDisplay(1); // invert because we swapped BLACk and WHITE definitions
    infoDisplay.setRotation(1);
    infoDisplay.clearDisplay();

    // test print TODO delete this eventually
    infoDisplay.setFont(&Picopixel);
    infoDisplay.setTextSize(1);
    infoDisplay.setTextColor(WHITE);
    infoDisplay.display();

    drawMenu();
}


// button handler
void handleButton(int btnID) {
    switch (currentMenu)
    {
        case MENU_MAIN:
        {
            handleButtonMain(btnID);
            break;
        }
        case MENU_CONFIG: 
        {
            handleButtonConfig(btnID);
            break;
        }
        default: break;
    }

    // only redraw menu when a button is handled
    drawMenu();

    // TODO save everything in permanent storage
}


// button handler in main menu
void handleButtonMain(int btnID)
{
    // down
    if (btnID == BTN_WHEEL_DOWN) {
        selectionID++;
        if (selectionID == MENU_MAIN_ITEMS) // wrap
            selectionID = 0;
    }

    // up
    if (btnID == BTN_WHEEL_UP) {
        selectionID--;
        if (selectionID == -1) // wrap
            selectionID = MENU_MAIN_ITEMS -1;
    }

    // press
    if (btnID == BTN_WHEEL_PRESS) {
        switch(selectionID) {
            case MENU_MAIN_CONFIG: {
                currentMenu = MENU_CONFIG;
                break; 
            }
            case MENU_MAIN_LOG: {
                currentMenu = MENU_LOG;
                break; 
            }
            case MENU_MAIN_AI_STATS: {
                currentMenu = MENU_AI_STATS;
                break; 
            }
            default: break;
        }
    }
}


// button handler in config menu
void handleButtonConfig(int btnID)
{
    // down
    if (btnID == BTN_WHEEL_DOWN) {
        selectionID++;
        if (selectionID == MENU_CONFIG_ITEMS) // wrap
            selectionID = 0;
    }

    // up
    if (btnID == BTN_WHEEL_UP) {
        selectionID--;
        if (selectionID == -1) // wrap
            selectionID = MENU_CONFIG_ITEMS -1;
    }

    // press
    if (btnID == BTN_WHEEL_PRESS) {
        switch(selectionID) {
            case MENU_CONFIG_HARDDROP: {
                doHardDrop = !doHardDrop;
                break; 
            }
            case MENU_CONFIG_DELAY: {
                switch(frameTime) {
                    case 0 : frameTime = 15; break;
                    case 15: frameTime = 30; break;
                    case 30: frameTime = 60; break;
                    case 60: frameTime = 0 ; break;
                    default: frameTime = 0 ; break;
                }
                break; 
            }
            case MENU_CONFIG_LEDS: {
                ledsEnabled = !ledsEnabled;
                // also turn off the LEDs in case they were on
                digitalWrite(PIN_A, LOW);
                digitalWrite(PIN_B, LOW);
                digitalWrite(PIN_DOWN, LOW);
                digitalWrite(PIN_LEFT, LOW);
                digitalWrite(PIN_RIGHT, LOW);
                break; 
            }
            case MENU_CONFIG_FASTLEARN: {
                fastLearn = !fastLearn;
                break; 
            }
            case MENU_CONFIG_PAUSED: {
                gamePaused = !gamePaused;
                break; 
            }
            case MENU_CONFIG_RESETDATA: {
                // TODO implement when permanent storage is implemented
                break; 
            }
            case MENU_CONFIG_BACK: {
                currentMenu = MENU_MAIN;
                selectionID = MENU_MAIN_CONFIG;
                break; 
            }
            default: break;
        }
    }
}

// draws menu based on currentMenu
void drawMenu()
{
    if (currentMenu == MENU_MAIN)
        drawMainMenu();

    if (currentMenu == MENU_CONFIG)
        drawConfigMenu();
    
    infoDisplay.display();
}  

// draws main menu
void drawMainMenu()
{
    infoDisplay.setTextSize(1);
    infoDisplay.clearDisplay();

    infoDisplay.setCursor(2, 4);
    infoDisplay.print("MAIN MENU");
    infoDisplay.drawFastHLine(0,6,48,WHITE);

    if (selectionID == MENU_MAIN_CONFIG)
    {
        infoDisplay.fillRect(0,15 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 15);
    infoDisplay.print("CONFIG");
    infoDisplay.setTextColor(WHITE);

    if (selectionID == MENU_MAIN_LOG)
    {
        infoDisplay.fillRect(0,23 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 23);
    infoDisplay.print("LOG");
    infoDisplay.setTextColor(WHITE);

    if (selectionID == MENU_MAIN_AI_STATS)
    {
        infoDisplay.fillRect(0,31 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 31);
    infoDisplay.print("AI STATS");
    infoDisplay.setTextColor(WHITE);
}


// draws config menu
void drawConfigMenu()
{
    infoDisplay.setTextSize(1);
    infoDisplay.clearDisplay();

    infoDisplay.setCursor(2, 4);
    infoDisplay.print("CONFIG MENU");
    infoDisplay.drawFastHLine(0,6,48,WHITE);

    if (selectionID == MENU_CONFIG_HARDDROP)
    {
        infoDisplay.fillRect(0,15 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 15);
    infoDisplay.print("H-DROP");
    infoDisplay.setCursor(35, 15);
    if (doHardDrop)
        infoDisplay.print("ON");
    else
        infoDisplay.print("OFF");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_DELAY)
    {
        infoDisplay.fillRect(0,23 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 23);
    infoDisplay.print("DELAY");
    infoDisplay.setCursor(35, 23);
    switch(frameTime)
    {
        case 0 : infoDisplay.print("NO"); break;
        case 15: infoDisplay.print("LO"); break;
        case 30: infoDisplay.print("MID"); break;
        case 60: infoDisplay.print("HI"); break;
        default: break;
    }
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_LEDS)
    {
        infoDisplay.fillRect(0,31 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 31);
    infoDisplay.print("LEDS");
    infoDisplay.setCursor(35, 31);
    if (ledsEnabled)
        infoDisplay.print("ON");
    else
        infoDisplay.print("OFF");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_FASTLEARN)
    {
        infoDisplay.fillRect(0,39 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 39);
    infoDisplay.print("F-LEARN");
    infoDisplay.setCursor(35, 39);
    if (fastLearn)
        infoDisplay.print("ON");
    else
        infoDisplay.print("OFF");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_PAUSED)
    {
        infoDisplay.fillRect(0,47 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 47);
    infoDisplay.print("PAUSED");
    infoDisplay.setCursor(35, 47);
    if (gamePaused)
        infoDisplay.print("YES");
    else
        infoDisplay.print("NO");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_RESETDATA)
    {
        infoDisplay.fillRect(0,64 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 64);
    infoDisplay.print("RESET DATA");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_BACK)
    {
        infoDisplay.fillRect(0,82 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(0, 82);
    infoDisplay.print("BACK");
    infoDisplay.setTextColor(WHITE);
}