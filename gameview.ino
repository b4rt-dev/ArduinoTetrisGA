
void drawInputs() 
{
  bool changed = false;

  infoDisplay.clearDisplay();
  if (buttonPressed(BTN_A))
  {
    infoDisplay.setCursor(0,4);
    infoDisplay.print("A");
    changed = true;
  }
  if (buttonPressed(BTN_B))
  {
    infoDisplay.setCursor(5,4);
    infoDisplay.print("B");
    changed = true;
  }
  if (buttonPressed(BTN_LEFT))
  {
    infoDisplay.setCursor(10,4);
    infoDisplay.print("L");
    changed = true;
  }
  if (buttonPressed(BTN_RIGHT))
  {
    infoDisplay.setCursor(15,4);
    infoDisplay.print("R");
    changed = true;
  }
  if (buttonPressed(BTN_DOWN))
  {
    infoDisplay.setCursor(20,4);
    infoDisplay.print("D");
    changed = true;
  }

  if (changed)
  {
    //infoDisplay.display();
  }
}

