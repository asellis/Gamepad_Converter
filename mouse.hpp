// A class to register mouse input
// Relies on USB Host Shield 2.0 Library

#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <stdlib.h>
#include <Arduino.h>
#include <hidboot.h>
#include <usbhub.h>

#include <Joystick.h>

//#include "HID-Project.h"  // For controller

class MouseParser : public MouseReportParser
{
  public:
    MouseParser(Joystick_* j);
    void CheckUpdate();
    
  protected:
    void OnMouseMove(MOUSEINFO *mi);
    void OnLeftButtonUp(MOUSEINFO *mi);
    void OnLeftButtonDown(MOUSEINFO *mi);
    void OnRightButtonUp(MOUSEINFO *mi);
    void OnRightButtonDown(MOUSEINFO *mi);
    void OnMiddleButtonUp(MOUSEINFO *mi);
    void OnMiddleButtonDown(MOUSEINFO *mi);

    void GamepadKeyDown(char key);          // Updates the gamepad for mouse button press
    void GamepadKeyUp(char key);            // Updates the gamepad for mouse button release
    void GamepadJoystick(int dX, int dY);   // Updates the gamepad for mouse movement
    int MouseConvert(int d);                // Converts the mouse movent into a fluid joystick value

    // Used to give a small delay between mouse movement updates
    unsigned long timeSinceUpdate;          
    bool Updated = false;

    Joystick_* Joystick;

};


#endif
