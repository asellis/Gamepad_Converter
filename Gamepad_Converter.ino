// This program converts keyboard and mouse input into gamepad output for PS3
// Allows the user to play PS3 games with a mouse and keyboard over a standard game controller
// Works on Arduino Leonardo or one that has support for specifying HID interface

// Library for outputting gamepad data
#include <Joystick.h>

// Libraries for reading mouse and keyboard input
#include <hidboot.h>
#include <usbhub.h>   // This library allows the use of a USB hub to give additional USB inputs for keyboard and mouse

// Satisfy IDE, which only needs to see the include statment in the ino.
// Needed for one HID libraries
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include "keyboard.hpp"
#include "mouse.hpp"

// Creates Joystick object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 1,                 // Button Count, Hat Switch Count
  true, true, true,      // X and Y, but no Z Axis
  false, false, true,    // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

// Sets up USB hub
USB Usb;
USBHub Hub(&Usb);

// Setup for Keyboard and Mouse
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

// Setup for actions to take when keyboard or mouse is used
// Performs the corresponding actions to the Joystick (Gamepad)
KbdParser KbdPrs(&Joystick);
MouseParser MousePrs(&Joystick);




void setup() {
  // Arduino setup function that initializes the Joystick, Keyboard and Mouse
  
  //Gamepad.begin();
  
  Joystick.begin(false);

  Joystick.setXAxisRange(-127,127);
  Joystick.setYAxisRange(-127,127);
  Joystick.setZAxisRange(-127,127);
  Joystick.setRzAxisRange(-127,127);

/*
  // FOR DEBUGGING: PRINTS INPUT TO SERIAL
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
*/


  Serial.println("Start");
  
  
  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay(200);

  HidKeyboard.SetReportParser(0, &KbdPrs);
  HidMouse.SetReportParser(0, &MousePrs);


}


void loop() {
  // A loop that gets executed after setup
  // Uses library calls to check keyboard and mouse parsers which will then update the gamepad
  Usb.Task();
  MousePrs.CheckUpdate();
}
