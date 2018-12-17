// A class to register keyboard input
// Relies on USB Host Shield 2.0 Library

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <stdlib.h>
#include <Arduino.h>
#include <hidboot.h>
#include <usbhub.h>

#include <Joystick.h>

//#include "HID-Project.h"  // For controller

class KbdParser : public KeyboardReportParser
{
  public:
    KbdParser(Joystick_* j);
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);
    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);

    void GamepadKeyDown(char key);
    void GamepadKeyUp(char key);

    // Bool values to not reset joystick if a key is still pressed
    // For left joystick
    bool joyLUp = false;
    bool joyLDown = false;
    bool joyLLeft = false;
    bool joyLRight = false;

    Joystick_* Joystick;
};


#endif
