#include <Joystick.h>

#include <hidboot.h>
#include <usbhub.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include "keyboard.hpp"
#include "mouse.hpp"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 1,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  false, false, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

USB Usb;
USBHub Hub(&Usb);

HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

KbdParser KbdPrs(&Joystick);
MouseParser MousePrs(&Joystick);




void setup() {
  //Gamepad.begin();
  
  Joystick.begin(false);

  Joystick.setXAxisRange(-127,127);
  Joystick.setYAxisRange(-127,127);
  Joystick.setZAxisRange(-127,127);
  Joystick.setRzAxisRange(-127,127);

/*
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
  Usb.Task();
  MousePrs.CheckUpdate();

}
