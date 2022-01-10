/*
 *  Polar HR10 Monitor class implementation.
 *
 * (c) 2022 Benno Schneider, projects@bschneider.org
 *
 *  https://www.arduino.cc/en/Reference/ArduinoBLE
 */

#include "polar_hr10_monitor.h"
#include "bpm_display.h"

static const char* bleHRServiceeUuid    = "180d"; // heart rate service
static const char* bleHRMeasurementUuid = "2a37"; // heart rate measurement characteristic

static const byte hrFormatMask       = 0x01;
static const byte energyExpendedMask = 0x08;
static const byte rrIntervalMask     = 0x10;

/*
 *  Constructor
 */
PolarHR10MonitorClass::PolarHR10MonitorClass() {
  state = Idle;
}

/*
 *  Destructor
 */
PolarHR10MonitorClass::~PolarHR10MonitorClass() {}

/*
 *  Setup the monitor
 */
int PolarHR10MonitorClass::begin() {
  // initialize BLE
  if (!BLE.begin()) {
    return 0;
  }
}

/*
 * End the monitor
*/
void PolarHR10MonitorClass::end() {
  BLE.end();
  state = Idle;
  return;
}

/*
 * Task called from loop(). This is a finite state machine
 */
void PolarHR10MonitorClass::task() {
  switch (state) {
    case Idle:
      taskIdle();
      break;
    case Scanning:
      taskScanning();
      break;
    case Subscribed:
      taskSubscribed();
      break;
    default:
      // something went wrong
      break;
  }
}

/*
 *  Idle task - sensor is not connected and we need to scan for it
*/
void PolarHR10MonitorClass::taskIdle() {
  // start scanning for heart rate sensor
  // Serial.println("Scanning for heart rate sensor");
  BLE.scanForUuid(bleHRServiceeUuid);
  state = Scanning;
}

/*
 *   Scanning task - check if sensor is found and subscribe to characteristics
 */
void PolarHR10MonitorClass::taskScanning() {
  _hrSensor = BLE.available();
  if (_hrSensor) {
    Serial.println(_hrSensor.localName() + " found");
    // TODO: check if this is a Polar HR10 sensor
    BLE.stopScan();
    state = Idle; // we need to re-start scanning in case something goes wrong
    // connect to sensor
    if (!_hrSensor.connect()) {
      Serial.println("Failed to connect!");
      return;
    }
    // discover peripheral attributes
    if (_hrSensor.discoverService(bleHRServiceeUuid)) {
      Serial.println("Service discovered.");
    } else {
      Serial.println("Attribute discovery failed! Disconnect.");
      _hrSensor.disconnect();
      return;
    }
    // retrieve heart rate measurement characteristic
    _hrmCharacteristic = _hrSensor.characteristic(bleHRMeasurementUuid);
    // subscribe to heart rate measurement characteristic
    if (!_hrmCharacteristic) {
      Serial.println("No heart rate measurement characteristic found!");
      _hrSensor.disconnect();
      return;
    } else if (!_hrmCharacteristic.canSubscribe()) {
      Serial.println("Heart rate measurement is not subscribable!");
      _hrSensor.disconnect();
      return;
    } else if (!_hrmCharacteristic.subscribe()) {
      Serial.println("Subscription failed!");
      _hrSensor.disconnect();
      return;
    } else {
      Serial.println("Subscribed");
      state = Subscribed;
    }
  } else {
    // Serial.println("Sensor not (yet) available");
  }
}

/*
 * Read heart rate measurement if avaliable
 */
void PolarHR10MonitorClass::taskSubscribed() {
  if (_hrSensor.connected()) {
    if (_hrmCharacteristic.valueUpdated()) {
      // Serial.println("HRM value has been updated");
      decodeHRMData(_hrmCharacteristic.value(), _hrmCharacteristic.valueLength());
    }
  } else {
    Serial.println("Sensor not connected!");
    state = Idle;
  }
}

/*
 * Decode heart rate measurement.
 *
 * https://github.com/FleXoft/Polar-H7-HRM/blob/master/HRM/ViewController.swift
 */
void PolarHR10MonitorClass::decodeHRMData(const byte *pValue, int length) {
  unsigned int  bpm;
  int offset = 1;
  if (length >= 2) {
    if ((pValue[0] & hrFormatMask) == 0) {
      // Serial.print("8-bit heart rate ");
      bpm = (unsigned int)(pValue[offset]);
      offset += 1;
    } else {
      // Serial.print("16-bit heart rate ");
      bpm = (unsigned int)pValue[offset+1] << 8;
      bpm |= (unsigned int)pValue[offset];
      offset += 2;
    }
  }
  Serial.println(String(bpm));
  BPMDISPLAY.drawBPM(bpm);
}

/*
 *  the one and only PolarHR10Class instance
 */
PolarHR10MonitorClass HR10;
