#include "mouse.hpp"

// PS3 Mapping

// L1 and R1
#define PS3_L1     'R'
#define PS3_R1     'L'

// Button mappings to PS3 Keys
#define PS3_L1Map  4
#define PS3_R1Map  5


MouseParser::MouseParser(Joystick_* j)
{
  Joystick = j;
}

void MouseParser::OnMouseMove(MOUSEINFO *mi)
{
  // Prints the change in motion of the mouse and updates the gamepad
  Serial.print("dx=");
  Serial.print(mi->dX, DEC);
  Serial.print(" dy=");
  Serial.println(mi->dY, DEC);

  // Gives a slight delay so that all mouse mo      //Gamepad.press(5);tion updates are within same time
  // The first few mouse updates would be fast, then slow down due to taking a little
  //  bit of time to update the game controller
  if(Updated)
  {
    Serial.println(micros()-timeSinceUpdate);
    timeSinceUpdate = micros();
    GamepadJoystick(mi->dX,mi->dY);
  }
  else
    timeSinceUpdate = micros();
  Updated = true;

};
void MouseParser::OnLeftButtonUp  (MOUSEINFO *mi)
{
  // Executes left mouse button release
  Serial.println("L Butt Up");
  GamepadKeyUp('L');
};
void MouseParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  // Executes left mouse button press
  Serial.println("L Butt Dn");
  GamepadKeyDown('L');
};
void MouseParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  // Executes right mouse button release
  Serial.println("R Butt Up");
  GamepadKeyUp('R');
};
void MouseParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  // Executes right mouse button press
  Serial.println("R Butt Dn");
  GamepadKeyDown('R');
};
void MouseParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  // Executes middle mouse button release
  // Not associated with any PS3 keys
  Serial.println("M Butt Up");
};
void MouseParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  // Executes middle mouse button press
  // Not associated with any PS3 keys
  Serial.println("M Butt Dn");
};

void MouseParser::GamepadKeyDown(char key)
{
  // Updates gamepad for key press
  switch(key)
  {
    case PS3_L1:
    {
      Serial.println("PS3_L1");
      Joystick->pressButton(PS3_L1Map);
      break;
    }
    case PS3_R1:
    {
      Serial.println("PS3_R1");
      Joystick->pressButton(PS3_R1Map);
      break;
    }
  }
  Joystick->sendState();
}

void MouseParser::GamepadKeyUp(char key)
{
  // Updates gamepad for key release
  switch(key)
  {
    case PS3_L1:
    {
      Serial.println("PS3_L1 Released");
      Joystick->releaseButton(PS3_L1Map);
      break;
    }
    case PS3_R1:
    {
      Serial.println("PS3_R1 Released");
      Joystick->releaseButton(PS3_R1Map);
      break;
    }
  }
  Joystick->sendState();
}

void MouseParser::GamepadJoystick(int dX, int dY)
{
  //unsigned long timeDif = micros()-timeSinceUpdate;
  //Serial.println(timeDif);
  int x, y;
  x = MouseConvert(dX);
  y = MouseConvert(dY);;
  Joystick->setZAxis(x);
  Joystick->setRzAxis(y);
  Joystick->sendState();

}

int MouseParser::MouseConvert(int d)
{
  // Converts the dX or dY input to correspond better to the joystick of the PS3
  int out = d;

  //out = 127*(2/M_PI)*atan(d);
  //out = (d/abs(d))*127;
  if(out>0)
  {
    out = 12*sqrt((out)+2);
  }
  else if(out<0)
  {
    out = -12*sqrt((out*-1)+2);
  }

  if(out>127)
    out = 127;
  else if(out<-127)
    out = -127;
  return out;
}

void MouseParser::CheckUpdate()
{
  // Checks the mouse delay and updates every 50 milliseconds
  if(Updated && micros()-timeSinceUpdate>=50000)
  {
    Serial.println("Reset");
    Joystick->setZAxis(0);
    Joystick->setRzAxis(0);
    Updated = false;
    Joystick->sendState();
  }
}
