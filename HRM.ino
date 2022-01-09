/*
   Heart Rate Monitor, v2.0

   (c) 2022 Benno Schneider

   This sketch for Arduino MKR WiFi 1010 monitors a Polar Heart Rate Sensor H10
   using Bluetooth Low Energy (BLE).

*/

#include "color_ranges.h"
#include "rgb_codes.h"
#include "bpm_display.h"
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
  BPMDISPLAY.begin();
  
  // initialize Polar HR10 monitor
  if (!HR10.begin()) {
    Serial.print("Starting the HR10 monitor failed!");
    while (1); 
  }
}

void loop() {
  // communicate with Polar HR10 heart rate monitor
  HR10.task();
}
