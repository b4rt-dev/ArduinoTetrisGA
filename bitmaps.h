#ifndef BITMAPS_H
#define BITMAPS_H

// 1 is 2x5px; All the other are 3x5px
const byte N0[] PROGMEM = {0x0,0x40,0x40,0x40,0x0,};
const byte N1[] PROGMEM = {0x0,0x80,0x80,0x80,0x80,};
const byte N2[] PROGMEM = {0x0,0xC0,0x0,0x60,0x0,};
const byte N3[] PROGMEM = {0x0,0xC0,0x0,0xC0,0x0,};
const byte N4[] PROGMEM = {0x40,0x40,0x0,0xC0,0xC0,};
const byte N5[] PROGMEM = {0x0,0x60,0x0,0xC0,0x0,};
const byte N6[] PROGMEM = {0x0,0x60,0x0,0x40,0x0,};
const byte N7[] PROGMEM = {0x0,0xC0,0xC0,0xC0,0xC0,};
const byte N8[] PROGMEM = {0x0,0x40,0x0,0x40,0x0,};
const byte N9[] PROGMEM = {0x0,0x40,0x0,0xC0,0x0,};

// 64x128
const byte GAME_BG[] PROGMEM = {
0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFC,0xCD,0x98,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xBA,0xAB,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFD,0xBA,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xBA,0x9B,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF9,0xCD,0xA8,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0x88,0x8C,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xDA,0xBB,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xDA,0x8D,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xDA,0xBE,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF8,0x8A,0x89,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0x8A,0x8B,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xBA,0xBB,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0x8A,0x8B,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFB,0xBA,0xBB,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF8,0x8D,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,
0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,
0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,
0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE
};


// Pixel data for next block
// 6x12
const byte I[] PROGMEM = {0xE0,0xE8,0xE0,0xE0,0xE8,0xE0,0xE0,0xE8,0xE0,0xE0,0xE8,0xE0,};
// 8x9
const byte J[] PROGMEM = {0xF8,0xFA,0xF8,0xF8,0xFA,0xF8,0xC0,0xD2,0xC0,};
// 8x9
const byte L[] PROGMEM = {0xC7,0xD7,0xC7,0xC7,0xD7,0xC7,0xC0,0xD2,0xC0,};
// 8x6
const byte O[] PROGMEM = {0xC0,0xD2,0xC0,0xC0,0xD2,0xC0,};
// 9x6
const byte S[] PROGMEM = {0xE0,0x0,0xE9,0x0,0xE0,0x0,0x3,0x80,0x4B,0x80,0x3,0x80,};
// 9x6
const byte T[] PROGMEM = {0xE3,0x80,0xEB,0x80,0xE3,0x80,0x0,0x0,0x49,0x0,0x0,0x0,};
// 9x6
const byte Z[] PROGMEM = {0x3,0x80,0x4B,0x80,0x3,0x80,0xE0,0x0,0xE9,0x0,0xE0,0x0,};

// Pixel data for each square of current and placed blocks
// 4x4
const byte MINO[] PROGMEM = {
    0xF0,0x90,0x90,0xF0
    };

#endif
