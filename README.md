hr10-monitor
============

Arduino sketch to monitor the **Polar&reg; HR10 heart rate sensor** with an **Arduino MKR WiFi 1010** board on an **Arduino MKR RGB** LED matrix shield of size 12x7 LEDs.

![Ardurino MKR WiFi 1010 with MKR RGB shield](illustration.png?raw=true)

This is a multi source file Arduino sketch. It allows to decouple not related functions into separate files and thus re-using the code in other projects as well.

The monitoring code in `polar_hr10_monitor.cpp` implements a finite-state machine (**FSM**) pattern. This allows a precisely defined behaviour based on distinct states. The code becomes robust while staying clearly arranged while doing multiple tasks like communicating with the sensor and blinking concurrently.

Display
-------

The matrix display shows the heart rate in beats per minute (bpm) as small 3x5 numbers (**N**) and as a bar graph (**G**). Numbers and bars are coloured according to the bpm ranges defined in `color_ranges.cpp`. Within the bar a single white dot shows the rate within the given bpm rate to estimate when to leave the range.

The (**P**) LED in the upper left corner pulses in the speed of the received heart rate.

```
   1  2  3  4  5  6  7  8  9  10 11 12
1  P  .  .  N  .  N  N  N  .  N  N  N
2  .  .  .  N  .  N  .  N  .  N  .  N
3  .  .  .  N  .  N  N  N  .  N  N  N
4  .  .  .  N  .  N  .  N  .  N  .  N
5  .  .  .  N  .  N  N  N  .  N  N  N
6  .  .  .  .  .  .  .  .  .  .  .  .
7  .  G  G  G  G  G  G  G  G  G  G  G
```

References
----------
- Arduino MKR WiFi 1010:<br/>
  https://docs.arduino.cc/hardware/mkr-wifi-1010
- Arduino MKR RGB Shield:<br/>
  https://store.arduino.cc/products/arduino-mkr-rgb-shield
- Official Android and iOS SDK for Polar&reg; sensors.<br/>
  https://github.com/polarofficial/polar-ble-sdk
- BLE on Arduino with Polar&reg; hardware. Straight forward Arduino code to receive data from a Polar&reg; HR10 sensor.<br/>
  https://github.com/SensorsIot/Bluetooth-BLE-on-Arduino-IDE
- Swift code for decoding the Polar&reg; HR7 sensor data.<br/>
  https://github.com/Fle.oft/Polar-H7-HRM
