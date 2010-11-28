/*
 * Thermometer - read temperature using an LM35 sensor and display it on a PCD8544 LCD.
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


#include <PCD8544.h>


static const char sensorPin = 0;
static const char ledPin = 13;
static const char samples = 10;

/* A custom "degrees" symbol... */
static const byte DEGREES_CHAR = 1;
static const byte degrees_glyph[] = { 0x00, 0x07, 0x05, 0x07, 0x00 };

/* A bitmap graphic (10x2) of a thermometer... */
static const byte THERMO_WIDTH = 10;
static const byte THERMO_HEIGHT = 2;
static const byte thermometer[] = { 0x00, 0x00, 0x48, 0xfe, 0x01, 0xfe, 0x00, 0x02, 0x05, 0x02,
                                    0x00, 0x00, 0x62, 0xff, 0xfe, 0xff, 0x60, 0x00, 0x00, 0x00};

static PCD8544 lcd;


void setup() {
  lcd.begin();
  
  /* Register the custom symbol... */
  lcd.createChar(DEGREES_CHAR, degrees_glyph);
  
  pinMode(ledPin, OUTPUT);
}


void loop() {
  digitalWrite(ledPin, HIGH);

  float temp = 0;
  
  /* Read the temperature a few times and average the results... */
  for (int i = 0; i < samples; i++) {
    temp += (5.0 * analogRead(sensorPin) * 100.0) / 1024.0;
    delay(10);
  }
  temp /= samples;

  /* Draw the thermometer bitmap at position (0,1)... */
  lcd.setCursor(0, 1);
  lcd.drawBitmap(thermometer, THERMO_WIDTH, THERMO_HEIGHT);
  
  /* Print the temperature (using the custom "degrees" symbol)... */
  lcd.print(" ");
  lcd.print(temp, 1);
  lcd.print(" \001C");

  digitalWrite(ledPin, LOW);  
  delay(500);
}


/* EOF - TempSensor.pde */

