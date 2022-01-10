/*
 * Display BPM rate on Arduino MKR RGB display.
 * 
 * https://www.arduino.cc/reference/en/libraries/arduino_mkrrgb/
 * https://www.arduino.cc/en/Reference/ArduinoGraphics
 */

#include <ArduinoGraphics.h>
#include <Arduino_MKRRGB.h>

#include "display.h"
#include "color_ranges.h"
#include "rgb_codes.h"

int DisplayClass::begin() {
  // initialize RGB shield
  MATRIX.begin();
  MATRIX.brightness(20);
  return 0;
}

/*
 * Display heart rate number and bar graph.
 */
void DisplayClass::displayHeartRate(unsigned int heartRate) {
  MATRIX.beginDraw();
  // clear the region used for the numbers and the bar graph
  MATRIX.fill(colBlack);
  MATRIX.stroke(colBlack);
  MATRIX.rect(1, 0, 11, 5);
  MATRIX.stroke(colBlack); 
  MATRIX.line(1, 6, 11, 6);
  if (heartRate > 0) {
    // draw the numbers
    int color = COLORRANGES.getColor(heartRate);
    MATRIX.beginText();
    MATRIX.textFont(Font_4x6);
    MATRIX.beginText(1 + (heartRate < 100 ? 4 : 0), 0, color);
    MATRIX.print(String(heartRate));
    MATRIX.endText();
    // draw the bar graph
    int xMarker = COLORRANGES.normalize(heartRate, 11);
    MATRIX.stroke(color);
    MATRIX.line(1, 6, 11, 6);
    MATRIX.stroke(colWhite);
    MATRIX.point(xMarker + 1, 6);
  } else {
    // draw 2 lines to mark zero heart rate
    MATRIX.stroke(colGray);
    MATRIX.line(5, 2,  7, 2);
    MATRIX.line(9, 2, 11, 2);    
  }
  MATRIX.endDraw();
  return;
}

/*
 * the one and only BPMDisplayClass instance
 */
DisplayClass DISP; // we cannot name it DISPLAY!
