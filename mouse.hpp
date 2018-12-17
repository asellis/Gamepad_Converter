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

    void GamepadKeyDown(char key);
    void GamepadKeyUp(char key);
    void GamepadJoystick(int dX, int dY);
    int MouseConvert(int d);

    unsigned long timeSinceUpdate;
    bool Updated = false;
    int count=0;
    int* xVal[5];
    int* yVal[5];

    Joystick_* Joystick;

};


#endif
