
/* Things to draw on status display:
highscore
highlines
highlevel

GA stuff
*/





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



void drawStats()
{
  drawInputs();
}