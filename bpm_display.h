/*
 * BPM display class declaration
 */

#ifndef _bpm_display_h
#define _bpm_display_h

class BPMDisplayClass {
  public:
    int begin();
    void drawBPM(int bpm);
};

extern BPMDisplayClass BPMDISPLAY;

#endif // _bpm_display_h
