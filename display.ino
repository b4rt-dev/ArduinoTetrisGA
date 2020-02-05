

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
    infoDisplay.setCursor(0,4);
    infoDisplay.print("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    infoDisplay.display();
}
