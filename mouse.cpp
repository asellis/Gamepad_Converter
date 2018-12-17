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
  Serial.print("dx=");
  Serial.print(mi->dX, DEC);
  Serial.print(" dy=");
  Serial.println(mi->dY, DEC);

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
  Serial.println("L Butt Up");
  GamepadKeyUp('L');
};
void MouseParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  Serial.println("L Butt Dn");
  GamepadKeyDown('L');
};
void MouseParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  Serial.println("R Butt Up");
  GamepadKeyUp('R');
};
void MouseParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  Serial.println("R Butt Dn");
  GamepadKeyDown('R');
};
void MouseParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  Serial.println("M Butt Up");
};
void MouseParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  Serial.println("M Butt Dn");
};

void MouseParser::GamepadKeyDown(char key)
{
  switch(key)
  {
    case PS3_L1:
    {
      Serial.println("PS3_L1");
      //Gamepad.press(5);
      Joystick->pressButton(PS3_L1Map);
      break;
    }
    case PS3_R1:
    {
      Serial.println("PS3_R1");
      //Gamepad.press(6);
      Joystick->pressButton(PS3_R1Map);
      break;
    }
  }
  //Gamepad.write();
  Joystick->sendState();
}

void MouseParser::GamepadKeyUp(char key)
{
  switch(key)
  {
    case PS3_L1:
    {
      Serial.println("PS3_L1 Released");
      //Gamepad.release(5);
      Joystick->releaseButton(PS3_L1Map);
      break;
    }
    case PS3_R1:
    {
      Serial.println("PS3_R1 Released");
      //Gamepad.release(6);
      Joystick->releaseButton(PS3_R1Map);
      break;
    }
  }
  //Gamepad.write();
  Joystick->sendState();
}

void MouseParser::GamepadJoystick(int dX, int dY)
{
  //unsigned long timeDif = micros()-timeSinceUpdate;
  //Serial.println(timeDif);
  int x, y;
  x = MouseConvert(dX);
  y = MouseConvert(dY);;
  //Gamepad.zAxis(x);
  //Gamepad.rzAxis(y);
  Joystick->setZAxis(x);
  Joystick->setRzAxis(y);
  //Gamepad.write();
  Joystick->sendState();

}

int MouseParser::MouseConvert(int d)
{
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
  if(Updated && micros()-timeSinceUpdate>=50000)
  {
    Serial.println("Reset");
    Joystick->setZAxis(0);
    Joystick->setRzAxis(0);
    //Gamepad.zAxis(0);
    //Gamepad.rzAxis(0);
    Updated = false;
    //Gamepad.write();
    Joystick->sendState();
  }
}
