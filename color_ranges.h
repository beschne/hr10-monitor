/*
 * Color ranges class declaration.
 */

#ifndef _color_ranges_h
#define _color_ranges_h

#include <limits.h> // for size_t

class ColorRangesClass {
  public:
    ColorRangesClass();
    virtual ~ColorRangesClass();
    
    int           addRange(int lowerLimit, unsigned long color); 
    int           setMaximum(int);
    unsigned long getColor(int v);
    int           normalize(int v, int scale);
  
  private:
    struct Range {
      int lowerLimit;
      int upperLimit;
      unsigned long color; 
    };
    
    Range* getRange(int value);

    // fixed space for all ranges, no dynamic allocation
    static const size_t MAXRANGES = 6;
    int   _rangesCount = 0;
    Range _ranges[MAXRANGES];
    int   _maxLimit = 0;

    void dumpRanges(); // for debugging only
};

extern ColorRangesClass COLORRANGES;

#endif // _color_ranges_h
