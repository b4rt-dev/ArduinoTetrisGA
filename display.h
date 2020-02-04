#ifndef MENU_H
#define MENU_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// The SH1106 library is from https://github.com/nhatuan84/esp32-sh1106-oled
// It is the modified Adafruit library for SH1106 and works perfectly on the TTGO-Eight
// The resolution is 128x64.

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);


void setupDisplay() {
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    display.setRotation(1);
    display.clearDisplay();
    Wire.setClock(400000); // set I2C speed to 400KHz (max for SH1106 display) to increase FPS
}


#endif
