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


#include <Arduino.h>


// Chip variants supported (ST7576 is experimental)...
#define CHIP_PCD8544 0
#define CHIP_ST7576  1


class PCD8544: public Print {
    public:
        // All the pins can be changed from the default values...
        PCD8544(uint8_t sclk  = 3,   /* clock       (display pin 2) */
                uint8_t sdin  = 4,   /* data-in     (display pin 3) */
                uint8_t dc    = 5,   /* data select (display pin 4) */
                uint8_t reset = 6,   /* reset       (display pin 8) */
                uint8_t sce   = 7);  /* enable      (display pin 5) */

        // Display initialization (dimensions in pixels)...
        void begin(uint8_t width=84, uint8_t height=48, uint8_t model=CHIP_PCD8544);
        void stop();

        // Erase everything on the display...
        void clear();
        void clearLine();  // ...or just the current line

        // Control the display's power state...
        void setPower(bool on);

        // For compatibility with the LiquidCrystal library...
        void display();
        void noDisplay();

        // Activate white-on-black mode...
        void setInverse(bool enabled);        // ...whole display
        void setInverseOutput(bool enabled);  // ...future writes

        // Set display contrast level (0-127)...
        void setContrast(uint8_t level);

        // Place the cursor at the start of the current line...
        void home();

        // Place the cursor at position (column, line)...
        void setCursor(uint8_t column, uint8_t line);

        // Assign a user-defined glyph (5x8) to an ASCII character (0-31)...
        void createChar(uint8_t chr, const uint8_t *glyph);

        // Write an ASCII character at the current cursor position (7-bit)...
        virtual size_t write(uint8_t chr);

        // Draw a bitmap at the current cursor position...
        void drawBitmap(const uint8_t *data, uint8_t columns, uint8_t lines);

        // Draw a chart element at the current cursor position...
        void drawColumn(uint8_t lines, uint8_t value);

    private:
        uint8_t pin_sclk;
        uint8_t pin_sdin;
        uint8_t pin_dc;
        uint8_t pin_reset;
        uint8_t pin_sce;

        // Chip variant in use...
        uint8_t model;

        // The size of the display, in pixels...
        uint8_t width;
        uint8_t height;

        // Current cursor position...
        uint8_t column;
        uint8_t line;

        // Current output mode for writes (doesn't apply to draws)...
        bool inverse_output = false;

        // User-defined glyphs (below the ASCII space character)...
        const uint8_t *custom[' '];

        // Send a command or data to the display...
        void send(uint8_t type, uint8_t data);
};


#endif  /* PCD8544_H */


/* vim: set expandtab ts=4 sw=4: */
