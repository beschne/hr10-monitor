/*
 * Polar HR10 Monitor class declaration.
 *
 * (c) 2022 Benno Schneider, projects@bschneider.org
 */

#ifndef _polar_hr10_monitor_h
#define _polar_hr10_monitor_h

#include <ArduinoBLE.h>

class PolarHR10MonitorClass {
  public:
    PolarHR10MonitorClass();
    virtual ~PolarHR10MonitorClass();
    int begin();
    void end();
    void task();
    unsigned int getHeartRate();

  private:
    enum state_t { Idle, Scanning, Subscribed };
    state_t _state = Idle;
    void taskIdle();
    void taskScanning();
    void taskSubscribed();
    void decodeHRMData(const byte *pValue, int length);

    BLEDevice         _hrSensor;          // heart rate sensor
    BLECharacteristic _hrmCharacteristic; // heart rate measurement

    unsigned int _bpm;

}; // PolarHR10MonitorClass

extern PolarHR10MonitorClass HR10;

#endif // _polar_monitor_h
