

void setupDisplay() {
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    display.setRotation(1);
    display.clearDisplay();

    // reduce brightness
    display.sh1106_command(0x81);
    display.sh1106_command(50);

    Wire.setClock(400000); // set I2C speed to 400KHz (max for SH1106 display) to increase FPS
}

