/*
 * Heart Rate Monitor, v2.0
 *
 * (c) 2022 Benno Schneider, projects@bschneider.org
 *
 * This sketch for Arduino MKR WiFi 1010 monitors 
 * a Polar(R) Heart Rate Sensor H10
 * using Bluetooth Low Energy (BLE).
 */

#include "color_ranges.h"
#include "rgb_codes.h"
#include "display.h"
#include "polar_hr10_monitor.h"

void setup() {
  // initialize serial debugging
  Serial.begin(9600);
  while(!Serial); // remove if running w/o serial connection

  // Set BPM ranges with colors
  COLORRANGES.addRange( 50, colGray);   // low activity
  COLORRANGES.addRange( 80, colBlue );  // fat burning
  COLORRANGES.addRange(112, colGreen);  // training
  COLORRANGES.addRange(129, colYellow); // power training
  COLORRANGES.addRange(145, colRed);    // heart rate too high!
  COLORRANGES.setMaximum(180);          // maximum value to monitor

  // Intialize RGB display
  DISP.begin();

  // initialize Polar HR10 monitor
  if (!HR10.begin()) {
    Serial.print("Starting the HR10 monitor failed!");
    while (1);
  }
}

void loop() {
  static unsigned int currentHeartRate = (unsigned int)-1;
  // communicate with Polar HR10 heart rate monitor
  HR10.task();
  // get heart rate and display if changed
  unsigned int newHeartRate = HR10.getHeartRate();
  if (newHeartRate != currentHeartRate) {
    currentHeartRate = newHeartRate;
    Serial.println(String(currentHeartRate)); // serial output only when changed
    DISP.displayHeartRate(currentHeartRate);
  }
  // refresh heart rate dot
  DISP.refreshHeartRateDot(currentHeartRate);
}
