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
    void OnControlKeysChanged(uint8_t before, uint8_t after); // Executes when a control key such as shift is pressed
    void OnKeyDown  (uint8_t mod, uint8_t key);               // Executes when the keyboard key is pushed down
    void OnKeyUp  (uint8_t mod, uint8_t key);                 // Executes when the keyboard key is released
    void OnKeyPressed(uint8_t key);                           // Prints the key in ASCII
    void GamepadKeyDown(char key);                            // Takes in a keyboard press and updates gamepad accordingly
    void GamepadKeyUp(char key);                              // Takes in a keyboard release and updates gamepad accordingly

    // Bool values to not reset joystick if a key is still pressed
    // For left joystick
    bool joyLUp = false;
    bool joyLDown = false;
    bool joyLLeft = false;
    bool joyLRight = false;

    Joystick_* Joystick;
};


#endif
