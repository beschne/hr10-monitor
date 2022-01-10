/*
 * BPM display class declaration.
 *
 * (c) 2022 Benno Schneider, projects@bschneider.org
 */

#ifndef _display_h
#define _display_h

class DisplayClass {
  public:
    int begin();
    void displayHeartRate(unsigned int bpm);
};

extern DisplayClass DISP;

#endif // _display_h
