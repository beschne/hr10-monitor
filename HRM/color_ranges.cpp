/*
 * Color ranges class implementation to be used with
 * BPM ranges and assigned display colors.
 *
 * (c) 2022 Benno Schneider, projects@bschneider.org
 */
#include <Arduino.h> // needed for Serial

#include "color_ranges.h"

/*
 * Constructor
 */
ColorRangesClass::ColorRangesClass() {}

/*
 * Destructor
 */
ColorRangesClass::~ColorRangesClass() {}

/*
 * add range with color
 */
int ColorRangesClass::addRange(int lowerLimit, unsigned long color) {
  // add new range to array of ranges
  if (_rangesCount >= MAXRANGES) {
    Serial.println("No space left in color ranges array!");
    return 0;
  }
  _ranges[_rangesCount].lowerLimit = lowerLimit;
  _ranges[_rangesCount].color      = color;
  _rangesCount++;
  // remove all upper limits and sort
  for (int i = 0; i < _rangesCount; i++) {
    _ranges[i].upperLimit = 0;
  }
  // sort the ranges array
  if (_rangesCount > 1) {
    for (int i = 0; i < _rangesCount - 1; i++) {
      int min = i; for (int j = i + 1; j < _rangesCount; j++) {
        if (_ranges[j].lowerLimit < _ranges[min].lowerLimit) {
          min = j;
          Range temp = _ranges[i]; _ranges[i] = _ranges[min]; _ranges[min] = temp;
        }
      }
    }
  }
  // set the upper limits
  for (int i = 0; i < _rangesCount - 1; i++) {
    _ranges[i].upperLimit = _ranges[i+1].lowerLimit - 1;
  }
  _ranges[_rangesCount - 1].upperLimit = _maxLimit;
  return _rangesCount;
}

/*
 * set mximum value
 *
 * we store thsi and add it to the last range evry time a range is added
 */
int ColorRangesClass::setMaximum(int v) {
  _maxLimit = v;
  if (_rangesCount > 0) {
    _ranges[_rangesCount - 1].upperLimit = v;
  }
  return _rangesCount;
}

/*
 * get color for value
 */
unsigned long ColorRangesClass::getColor(int v) {

  ColorRangesClass::Range* r = getRange(v);
  if (r != NULL) return r->color;
  return NULL;
}

/*
 * normalize a bpm value within range for bar graph
 */
int ColorRangesClass::normalize(int v, int scale) {
  ColorRangesClass::Range* r = getRange(v);
  int n = 0;
  if (r != NULL) {
    n = scale * (v - r->lowerLimit) / (r->upperLimit - r->lowerLimit);
  }
  return n;
}

/*
 * get range for given bpm
 */
ColorRangesClass::Range* ColorRangesClass::getRange(int v) {
  ColorRangesClass::Range* range = NULL;
  for (int i = 0; i < _rangesCount; i++) {
    ColorRangesClass::Range* r = &ColorRangesClass::_ranges[i];
    if ((v >= r->lowerLimit) && (v <= r->upperLimit)) {
      range = r;
      break;
    }
  }
  return range;
}

/*
 *  the one and only PBPMRangesClass instance
 */
ColorRangesClass COLORRANGES;

/*
 * dump ranges array to Serial console - for debugging only
 */
void ColorRangesClass::dumpRanges() {
  Range* r = &_ranges[0];
  for (int i = 0; i < _rangesCount; i++, r++) {
    Serial.println(String(r->lowerLimit) + " - " + String(r->upperLimit) + ": " + String(r->color, HEX));
  }
}
