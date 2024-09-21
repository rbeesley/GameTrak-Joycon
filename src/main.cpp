#include <Arduino.h>
#include <Button.h>
#include <Joystick.h>

#include "Axis.h"

//#define SERIAL_DEBUG true

/////////////////////////////////
//// Pin Definitions
// X = RIGHT-LEFT
// Y = FRONT-BACK
// Z = IN-OUT
// L = Left Controller
// R = Right Controller
// FOOT = Foot Switch
///////////////////////////////// Arduino Pins
static const int PIN_X_L = 18;  // A0
static const int PIN_Y_L = 19;  // A1
static const int PIN_Z_L = 8;   // D8/A8
static const int PIN_X_R = 20;  // A2
static const int PIN_Y_R = 21;  // A3
static const int PIN_Z_R = 9;   // D9/A9
static const int PIN_FOOT = 7;  // D7
// static const int PIN_PLUG = 6;  // D6/A6
/////////////////////////////////

Joystick_ Joystick(0x01, JOYSTICK_TYPE_JOYSTICK, 1, 0, true, true, true, true, true, true, false, false, false, false, false);

// Initialize Pin Definitions
Axis xlAxis(PIN_X_L, INPUT, 0, 1023, false); // Left X Axis
Axis ylAxis(PIN_Y_L, INPUT, 0, 1023, true);  // Left Y Axis - Inverted
Axis zlAxis(PIN_Z_L, INPUT, 0, 1023, false); // Left Z Axis
Axis xrAxis(PIN_X_R, INPUT, 0, 1023, true);  // Right X Axis - Inverted
Axis yrAxis(PIN_Y_R, INPUT, 0, 1023, false); // Right Y Axis
Axis zrAxis(PIN_Z_R, INPUT, 0, 1023, false); // Right Z Axis

Button footSwitch(PIN_FOOT, true); // Foot Switch - Grounded when pressed

// In the PS2 conversion I created, the plug is always seated,
// so the plug switch is always open and there's no value in sending this state
// Button plugSwitch(PIN_PLUG, true); // Plug continuity Switch - Grounded when plug is seated, open when plug is not seated

// Main Program
void setup()
{
  RXLED1;

#if defined(SERIAL_DEBUG)
  // Wait for Serial to become available
  Serial.begin(115200);
#endif

  // Need to acquire the initial state of the foot switch
  footSwitch.update();

  // Initialize Joystick Library
  Joystick.begin();

  Joystick.setXAxisRange(xlAxis.getMinimum(), xlAxis.getMaximum());
  Joystick.setYAxisRange(ylAxis.getMinimum(), ylAxis.getMaximum());
  Joystick.setZAxisRange(zlAxis.getMinimum(), zlAxis.getMaximum());
  Joystick.setRxAxisRange(xrAxis.getMinimum(), xrAxis.getMaximum());
  Joystick.setRyAxisRange(yrAxis.getMinimum(), yrAxis.getMaximum());
  Joystick.setRzAxisRange(zrAxis.getMinimum(), zrAxis.getMaximum());

  Joystick.setButton(0, footSwitch.isPressed() ? 1 : 0);

  RXLED0;
};

bool RXLED = false;
int count = 0;
void loop()
{
  Joystick.setXAxis(xlAxis.read());
  Joystick.setYAxis(ylAxis.read());
  Joystick.setZAxis(zlAxis.read());
  Joystick.setRxAxis(xrAxis.read());
  Joystick.setRyAxis(yrAxis.read());
  Joystick.setRzAxis(zrAxis.read());

  // Read foot switch
  if (footSwitch.update()) {
    Joystick.setButton(0, footSwitch.isPressed() ? 1 : 0);
  }

  if (++count % 128 == 0) {
    RXLED = !RXLED;
    RXLED ? (RXLED0) : (RXLED1);
    count = 0;

#if defined(SERIAL_DEBUG)
    Serial.println();
    Serial.println("      XL: " + String(xlAxis.read()) + " YL: " + String(ylAxis.read()) + " ZL: " + String(zlAxis.read()));
    Serial.println("      XR: " + String(xrAxis.read()) + " YR: " + String(yrAxis.read()) + " ZR: " + String(zrAxis.read()));
    Serial.println("    Foot: " + String(footSwitch.isPressed()));
#endif
  }

  delay(10);
};