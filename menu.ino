/* Things TODO draw on status display:

config:
    - display brightness
*/


void processLog()
{
  if (logString.length() > LOG_SIZE)
  {
    logString = logString.substring(logString.length() - LOG_SIZE);
  }
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
        case MENU_LOG:
        {
            handleButtonLog(btnID);
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
                // turn off the LEDs in case they were on
                digitalWrite(PIN_A, LOW);
                digitalWrite(PIN_B, LOW);
                digitalWrite(PIN_DOWN, LOW);
                digitalWrite(PIN_LEFT, LOW);
                digitalWrite(PIN_RIGHT, LOW);
                break; 
            }
            case MENU_CONFIG_FASTLEARN: {
                fastLearn = !fastLearn;
                // set harddrop to true and frametime to 0 to properly learn fast
                // since it does not make sense and might slow down (not sure tho), leds are disabled as well
                // while twoPiece makes learning significantly slower, it remains an option
                // to use with fastLearning, since it makes sense
                doHardDrop = true;
                frameTime = 0;
                if (fastLearn)
                    ledsEnabled = false;
                else
                    ledsEnabled = true;

                break; 
            }
            case MENU_CONFIG_TWO_PIECE: {
                twoPiece = !twoPiece;
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

// button handler in log menu
void handleButtonLog(int btnID)
{
    // down
    if (btnID == BTN_WHEEL_DOWN) {
        // scroll log up
    }

    // up
    if (btnID == BTN_WHEEL_UP) {
        // scroll log down
    }

    // press
    if (btnID == BTN_WHEEL_PRESS) {
        // there is only a back button, so just go back to main menu
        currentMenu = MENU_MAIN;
        selectionID = MENU_MAIN_LOG;
    }
}

// draws menu based on currentMenu
void drawMenu()
{
    if (currentMenu == MENU_MAIN)
        drawMainMenu();

    if (currentMenu == MENU_CONFIG)
        drawConfigMenu();

    if (currentMenu == MENU_LOG)
        drawLogMenu();
    
    infoDisplay.display();
}  

// draws main menu
void drawMainMenu()
{
    infoDisplay.setTextSize(1);
    infoDisplay.clearDisplay();

    infoDisplay.setCursor(6, 4);
    infoDisplay.print("MAIN MENU");
    infoDisplay.drawFastHLine(0,6,48,WHITE);

    if (selectionID == MENU_MAIN_CONFIG)
    {
        infoDisplay.fillRect(0,15 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 15);
    infoDisplay.print("CONFIG");
    infoDisplay.setTextColor(WHITE);

    if (selectionID == MENU_MAIN_LOG)
    {
        infoDisplay.fillRect(0,23 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 23);
    infoDisplay.print("LOG");
    infoDisplay.setTextColor(WHITE);

    if (selectionID == MENU_MAIN_AI_STATS)
    {
        infoDisplay.fillRect(0,31 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 31);
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
    infoDisplay.setCursor(1, 15);
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
    infoDisplay.setCursor(1, 23);
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
    infoDisplay.setCursor(1, 31);
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
    infoDisplay.setCursor(1, 39);
    infoDisplay.print("F-LEARN");
    infoDisplay.setCursor(35, 39);
    if (fastLearn)
        infoDisplay.print("ON");
    else
        infoDisplay.print("OFF");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_TWO_PIECE)
    {
        infoDisplay.fillRect(0,47 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 47);
    infoDisplay.print("2-PIECE");
    infoDisplay.setCursor(35, 47);
    if (twoPiece)
        infoDisplay.print("ON");
    else
        infoDisplay.print("OFF");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_PAUSED)
    {
        infoDisplay.fillRect(0,55 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 55);
    infoDisplay.print("PAUSED");
    infoDisplay.setCursor(35, 55);
    if (gamePaused)
        infoDisplay.print("YES");
    else
        infoDisplay.print("NO");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_RESETDATA)
    {
        infoDisplay.fillRect(0,72 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 72);
    infoDisplay.print("RESET DATA");
    infoDisplay.setTextColor(WHITE);


    if (selectionID == MENU_CONFIG_BACK)
    {
        infoDisplay.fillRect(0,82 -5, 48,7,WHITE);
        infoDisplay.setTextColor(BLACK);
    }
    infoDisplay.setCursor(1, 82);
    infoDisplay.print("BACK");
    infoDisplay.setTextColor(WHITE);
}

// draws log menu
void drawLogMenu()
{
    infoDisplay.setTextSize(1);
    infoDisplay.clearDisplay();

    infoDisplay.setCursor(6, 4);
    infoDisplay.print("LOG MENU");
    infoDisplay.drawFastHLine(0,6,48,WHITE);


    infoDisplay.setCursor(0, 15);
    infoDisplay.print(logString);
    infoDisplay.setTextColor(WHITE);


    infoDisplay.fillRect(0,82 -5, 48,7,WHITE);
    infoDisplay.setTextColor(BLACK);

    infoDisplay.setCursor(1, 82);
    infoDisplay.print("BACK");
    infoDisplay.setTextColor(WHITE);
}