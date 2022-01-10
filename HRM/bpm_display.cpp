/*
 * Display BPM rate on Arduino MKR RGB display.
 */

#include <ArduinoGraphics.h>
#include <Arduino_MKRRGB.h>

#include "bpm_display.h"
#include "color_ranges.h"

int BPMDisplayClass::begin() {
  // initialize RGB shield
  MATRIX.begin();
  MATRIX.brightness(20);
  return 0;
}

/*
 * draw bpm numbers
 */
void BPMDisplayClass::drawBPM(int bpm) {
  // clear the screen
  MATRIX.beginDraw();
  MATRIX.background(0,0,0);
  MATRIX.clear();
  // draw the text
  int color = COLORRANGES.getColor(bpm);
  MATRIX.beginText();
  MATRIX.textFont(Font_4x6);
  MATRIX.beginText(1 + (bpm < 100 ? 4 : 0), 0, color);
  MATRIX.print(String(bpm));
  MATRIX.endText();
  // draw the bar graph
  int xMarker = COLORRANGES.normalize(bpm, 11);
  //MATRIX.beginDraw();
  MATRIX.stroke(color);
  MATRIX.line(1, 6, 11, 6);
  MATRIX.stroke(0x404040L);
  MATRIX.point(xMarker + 1, 6);
  MATRIX.endDraw();
  return;
}

/*
 * the one and only BPMDisplayClass instance
 */
BPMDisplayClass BPMDISPLAY;
