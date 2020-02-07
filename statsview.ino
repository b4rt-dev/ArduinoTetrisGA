
/* Things to draw on status display:
highscore
highlines
highlevel

config:
  - enable harddrops

GA stuff:
  - current weights
  - generation
  - population size
  - etc
*/

void setupScrollWheel()
{
  // set scroll wheel buttons as inputs
  pinMode(PIN_WHEEL_UP, INPUT);
  pinMode(PIN_WHEEL_PRESS, INPUT);
  pinMode(PIN_WHEEL_DOWN, INPUT);
}

void setupLEDs()
{
  // set pins to LEDs as output
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_LEFT, OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_DOWN, OUTPUT);
  // set start by setting the LEDs low
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_LEFT, LOW);
  digitalWrite(PIN_RIGHT, LOW);
  digitalWrite(PIN_DOWN, LOW);
}


void drawInputs() 
{

  if (btnPressed[BTN_A] != btnPressedPrev[BTN_A])
  {
    if (btnPressed[BTN_A])
    {
      digitalWrite(PIN_A, HIGH);
    }
    else
    {
      digitalWrite(PIN_A, LOW);
    }
  }
 if (btnPressed[BTN_B] != btnPressedPrev[BTN_B])
  {
    if (btnPressed[BTN_B])
    {
      digitalWrite(PIN_B, HIGH);
    }
    else
    {
      digitalWrite(PIN_B, LOW);
    }
  }
  if (btnPressed[BTN_LEFT] != btnPressedPrev[BTN_LEFT])
  {
    if (btnPressed[BTN_LEFT])
    {
      digitalWrite(PIN_LEFT, HIGH);
    }
    else
    {
      digitalWrite(PIN_LEFT, LOW);
    }
  }
  if (btnPressed[BTN_RIGHT] != btnPressedPrev[BTN_RIGHT])
  {
    if (btnPressed[BTN_RIGHT])
    {
      digitalWrite(PIN_RIGHT, HIGH);
    }
    else
    {
      digitalWrite(PIN_RIGHT, LOW);
    }
  }
  if (btnPressed[BTN_DOWN] != btnPressedPrev[BTN_DOWN])
  {
    if (btnPressed[BTN_DOWN])
    {
      digitalWrite(PIN_DOWN, HIGH);
    }
    else
    {
      digitalWrite(PIN_DOWN, LOW);
    }
  }

  memcpy(btnPressedPrev, btnPressed, BTN_COUNT);
}

void checkScrollWheel()
{
  if (digitalRead(PIN_WHEEL_PRESS) == LOW)
  {
    doHardDrop = false;
  }
  else
  {
    doHardDrop = true;
  }
}

void drawStats()
{
  drawInputs();
  checkScrollWheel();
}