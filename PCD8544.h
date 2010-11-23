/*
 * PCD8544 - Interface with Philips PCD8544 (or compatible) LCDs.
 *
 * Copyright (c) 2010 Carlos Rodrigues <cefrodrigues@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef PCD8544_H
#define PCD8544_H


#include "WProgram.h"


// The pins used by this library...
#define PCD8544_SCLK  3  /* clock       (display pin 2) */
#define PCD8544_SDIN  4  /* data-in     (display pin 3) */
#define PCD8544_DC    5  /* data select (display pin 4) */
#define PCD8544_RESET 6  /* reset       (display pin 8) */
#define PCD8544_SCE   7  /* enable      (display pin 5) */


// The number of possible custom glyphs...
#define CUSTOM_GLYPHS 32


class PCD8544: public Print {
    public:
        // Display initialization...
        void begin(unsigned char width=84, unsigned char height=48);
        void stop();

        // Erase everything on the display...
        void clear();
        void clearLine(unsigned char line);  // ...or just a single line
        
        // Control the display's power state...
        void setPower(bool on);

        // For compatibility with the LiquidCrystal library...
        void display() { this->setPower(true); };
        void noDisplay() { this->setPower(false); };

        // Activate inverse mode...
        void setInverse(bool inverse);

        // Place the cursor at the start of the current line...
        void home();

        // Place the cursor at position (column, line)...
        void setCursor(unsigned char column, unsigned char line);

        // Assign a custom glyph (5x8) to ASCII 0-31...
        void createChar(unsigned char position, const unsigned char *glyph);

        // Write a single glyph at the current cursor position (7-bit)...
        void write(unsigned char data);

    private:
        unsigned char width;
        unsigned char height;
        const unsigned char *glyphs[CUSTOM_GLYPHS - 1];

        void send(unsigned char type, unsigned char data);
};


#endif PCD8544_H


/* vim: set expandtab ts=4 sw=4: */
