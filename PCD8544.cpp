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


#include "PCD8544.h"
#include "charset.h"

#include <WProgram.h>
#include <avr/pgmspace.h>


#define PCD8544_CMD  LOW
#define PCD8544_DATA HIGH


void PCD8544::begin(unsigned char width, unsigned char height)
{
    this->width = width;
    this->height = height;

    // Sanitize the custom glyphs...
    memset(this->custom, 0, sizeof(this->custom));

    // All pins are outputs (these displays cannot be read)...
    pinMode(PCD8544_SCLK, OUTPUT);
    pinMode(PCD8544_SDIN, OUTPUT);
    pinMode(PCD8544_DC, OUTPUT);
    pinMode(PCD8544_RESET, OUTPUT);
    pinMode(PCD8544_SCE, OUTPUT);

    // Reset the controller state...
    digitalWrite(PCD8544_RESET, HIGH);
    digitalWrite(PCD8544_SCE, HIGH);
    digitalWrite(PCD8544_RESET, LOW);
    delay(100);  
    digitalWrite(PCD8544_RESET, HIGH);

    // Set the LCD parameters...
    this->send(PCD8544_CMD, 0x21);  // extended instruction set control (H=1)
    this->send(PCD8544_CMD, 0x13);  // bias system (1:48)
    this->send(PCD8544_CMD, 0xC2);  // set Vop (3.06 + 66 * 0.06 = 7V)
    this->send(PCD8544_CMD, 0x20);  // extended instruction set control (H=0)
    this->send(PCD8544_CMD, 0x09);  // all display segments on

    // Clear RAM contents...
    this->clear();

    // Activate LCD...
    this->send(PCD8544_CMD, 0x08);  // display blank
    this->send(PCD8544_CMD, 0x0c);  // normal mode (0x0d = inverse mode)
    delay(100);

    // Place the cursor at the origin...
    this->send(PCD8544_CMD, 0x80);
    this->send(PCD8544_CMD, 0x40); 
}


void PCD8544::stop()
{
    this->clear();
    this->setPower(false);
}


void PCD8544::clear()
{
    this->setCursor(0, 0);

    for (unsigned short i = 0; i < this->width * (this->height/8); i++) {
        this->send(PCD8544_DATA, 0x00);
    }

    this->setCursor(0, 0);
}


void PCD8544::clearLine(unsigned char line)
{
    this->setCursor(0, line);

    for (unsigned char i = 0; i < this->width; i++) {
        this->send(PCD8544_DATA, 0x00);
    }

    this->setCursor(0, line);
}


void PCD8544::setPower(bool on)
{
    this->send(PCD8544_CMD, on ? 0x20 : 0x24);
}


inline void PCD8544::display()
{
    this->setPower(true);
}


inline void PCD8544::noDisplay()
{
    this->setPower(false);
}


void PCD8544::setInverse(bool inverse)
{
    this->send(PCD8544_CMD, inverse ? 0x0d : 0x0c);
}


void PCD8544::home()
{
    this->send(PCD8544_CMD, 0x80);
}


void PCD8544::setCursor(unsigned char column, unsigned char line)
{
    this->send(PCD8544_CMD, 0x80 | (column % this->width));
    this->send(PCD8544_CMD, 0x40 | (line % (this->height/9 + 1))); 
}


void PCD8544::createChar(unsigned char chr, const unsigned char *glyph)
{
    // ASCII 0-31 only...
    if (chr >= ' ') {
        return;
    }
    
    this->custom[chr] = glyph;
}


void PCD8544::write(unsigned char chr)
{
    // ASCII 7-bit only...
    if (chr >= 0x80) {
        return;
    }

    const unsigned char *glyph;
    unsigned char pgm_buffer[5];

    if (chr >= ' ') {
        // Regular ASCII characters are kept in flash to save RAM...
        memcpy_P(pgm_buffer, &charset[chr - ' '], sizeof(pgm_buffer));
        glyph = pgm_buffer;
    } else {
        // Custom glyphs, on the other hand, are stored in RAM...
        if (this->custom[chr]) {
            glyph = this->custom[chr];
        } else {
            // Default to a space character if unset...
            memcpy_P(pgm_buffer, &charset[0], sizeof(pgm_buffer));
            glyph = pgm_buffer;
        }
    }

    // Output one column at a time...
    for (unsigned char i = 0; i < 5; i++) {
        this->send(PCD8544_DATA, glyph[i]);
    }

    // One column between characters...
    this->send(PCD8544_DATA, 0x00);
}


void PCD8544::send(unsigned char type, unsigned char data)
{
    digitalWrite(PCD8544_DC, type);
  
    digitalWrite(PCD8544_SCE, LOW);
    shiftOut(PCD8544_SDIN, PCD8544_SCLK, MSBFIRST, data);
    digitalWrite(PCD8544_SCE, HIGH);
}


/* vim: set expandtab ts=4 sw=4: */
