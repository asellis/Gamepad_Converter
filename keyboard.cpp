#include "keyboard.hpp"

// Define PS3 Keys
// Letter keys should be lower case
// Uppercase keys represent Control Keys
// S = left shift

// Shape Buttons
#define PS3_X       ' '
#define PS3_Sqr     'r'
#define PS3_Tri     'q'
#define PS3_Cir     'c'

// D-Pad
#define PS3_DU       '1'
#define PS3_DD       '2'
#define PS3_DL       '3'
#define PS3_DR       '4'

// Left Joystick
#define PS3_LJoyU    'w'
#define PS3_LJoyD    's'
#define PS3_LJoyL    'a'
#define PS3_LJoyR    'd'
#define PS3_LJoyZ    'S'

// Right Joystick (only for button)
#define PS3_RJoyZ    'f'

// L2 and R2
#define PS3_L2       't'
#define PS3_R2       'g'

// Start and Select
#define PS3_Start    'j'
#define PS3_Sel      'h'

// Button mappings to PS3 Keys
#define PS3_XMap     1
#define PS3_SqrMap   0
#define PS3_TriMap   3
#define PS3_CirMap   2

#define PS3_LJoyZMap 10
#define PS3_RJoyZMap 11

#define PS3_L2Map    6
#define PS3_R2Map    7

#define PS3_StartMap 9
#define PS3_SelMap   8

KbdParser::KbdParser(Joystick_* j)
{
  Joystick = j;
}

void KbdParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

  Serial.print(" >");
  PrintHex<uint8_t>(key, 0x80);
  Serial.print("< ");

  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

void KbdParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.print("DN ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  if (c)
    OnKeyPressed(c);

  char k = char(tolower((char)c));
  GamepadKeyDown(k);
}

void KbdParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.println("LeftShift changed");
    if(afterMod.bmLeftShift == 1)
      GamepadKeyDown('S');
    else
      GamepadKeyUp('S');
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.println("RightGUI changed");
  }

}

void KbdParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.print("UP ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);
  char k = char(tolower((char)c));
  GamepadKeyUp(k);
}

void KbdParser::OnKeyPressed(uint8_t key)
{
  Serial.print("ASCII: ");
  Serial.println((char)key);
}

void KbdParser::GamepadKeyDown(char key)
{
  switch(key)
  {
    case PS3_X:
    {
      Serial.println("PS3_X");
      //Gamepad.press(2);
      Joystick->pressButton(PS3_XMap);
      break;
    }
    case PS3_Sqr:
    {
      Serial.println("PS3_Sqr");
      //Gamepad.press(1);
      Joystick->pressButton(PS3_SqrMap);
      break;
    }
    case PS3_Tri:
    {
      Serial.println("PS3_Tri");
      //Gamepad.press(4);
      Joystick->pressButton(PS3_TriMap);
      break;
    }
    case PS3_Cir:
    {
      Serial.println("PS3_Cir");
      //Gamepad.press(3);
      Joystick->pressButton(PS3_CirMap);
      break;
    }

    case PS3_DU:
    {
      Serial.println("PS3_DU");
      //Gamepad.dPad1(1);
      Joystick->setHatSwitch(0,0);
      break;
    }
    case PS3_DD:
    {
      Serial.println("PS3_DD");
      //Gamepad.dPad1(5);
      Joystick->setHatSwitch(0,180);
      break;
    }
    case PS3_DL:
    {
      Serial.println("PS3_DL");
      //Gamepad.dPad1(7);
      Joystick->setHatSwitch(0,270);
      break;
    }
    case PS3_DR:
    {
      Serial.println("PS3_DR");
      //Gamepad.dPad1(3);
      Joystick->setHatSwitch(0,90);
      break;
    }

    case PS3_LJoyU:
    {
      Serial.println("PS3_LJoyU");
      //Gamepad.yAxis(-32700);
      Joystick->setYAxis(-127);
      joyLUp = true;
      break;
    }
    case PS3_LJoyD:
    {
      Serial.println("PS3_LJoyD");
      //Gamepad.yAxis(32700);
      Joystick->setYAxis(127);
      joyLDown = true;
      break;
    }
    case PS3_LJoyL:
    {
      Serial.println("PS3_LJoyL");
      //Gamepad.xAxis(-32700);
      Joystick->setXAxis(-127);
      joyLLeft = true;
      break;
    }
    case PS3_LJoyR:
    {
      Serial.println("PS3_LJoyR");
      //Gamepad.xAxis(32700);
      Joystick->setXAxis(127);
      joyLRight = true;
      break;
    }
    case PS3_LJoyZ:
    {
      Serial.println("PS3_LJoyZ");
      //Gamepad.press(11);
      Joystick->pressButton(PS3_LJoyZMap);
      break;
    }
    case PS3_RJoyZ:
    {
      Serial.println("PS3_RJoyZ");
      //Gamepad.press(12);
      Joystick->pressButton(PS3_RJoyZMap);
      break;
    }

    case PS3_L2:
    {
      Serial.println("PS3_L2");
      //Gamepad.press(7);
      Joystick->pressButton(PS3_L2Map);
      break;
    }
    case PS3_R2:
    {
      Serial.println("PS3_R2");
      //Gamepad.press(8);
      Joystick->pressButton(PS3_R2Map);
      break;
    }

    case PS3_Start:
    {
      Serial.println("PS3_Start");
      //Gamepad.press(10);
      Joystick->pressButton(PS3_StartMap);
      break;
    }
    case PS3_Sel:
    {
      Serial.println("PS3_Sel");
      //Gamepad.press(9);
      Joystick->pressButton(PS3_SelMap);
      break;
    }
  }
  //Gamepad.write();
  Joystick->sendState();
}


void KbdParser::GamepadKeyUp(char key)
{
  switch(key)
  {
    case PS3_X:
    {
      Serial.println("PS3_X Released");
      //Gamepad.release(2);
      Joystick->releaseButton(PS3_XMap);
      break;
    }
    case PS3_Sqr:
    {
      Serial.println("PS3_Sqr Released");
      //Gamepad.release(1);
      Joystick->releaseButton(PS3_SqrMap);
      break;
    }
    case PS3_Tri:
    {
      Serial.println("PS3_Tri Released");
      //Gamepad.release(4);
      Joystick->releaseButton(PS3_TriMap);
      break;
    }
    case PS3_Cir:
    {
      Serial.println("PS3_Cir Released");
      //Gamepad.release(3);
      Joystick->releaseButton(PS3_CirMap);
      break;
    }

    case PS3_DU:
    {
      Serial.println("PS3_DU Released");
      //Gamepad.dPad1(0);
      Joystick->setHatSwitch(0,-1);
      break;
    }
    case PS3_DD:
    {
      Serial.println("PS3_DD Released");
      //Gamepad.dPad1(0);
      Joystick->setHatSwitch(0,-1);
      break;
    }
    case PS3_DL:
    {
      Serial.println("PS3_DL Released");
      //Gamepad.dPad1(0);
      Joystick->setHatSwitch(0,-1);
      break;
    }
    case PS3_DR:
    {
      Serial.println("PS3_DR Released");
      //Gamepad.dPad1(0);
      Joystick->setHatSwitch(0,-1);
      break;
    }

    case PS3_LJoyU:
    {
      Serial.println("PS3_LJoyU Released");
      if(!joyLDown)
      {
        //Gamepad.yAxis(0);
        Joystick->setYAxis(0);
      }
      joyLUp = false;
      break;
    }
    case PS3_LJoyD:
    {
      Serial.println("PS3_LJoyD Released");
      if(!joyLUp)
      {
        //Gamepad.yAxis(0);
        Joystick->setYAxis(0);
      }
      joyLDown = false;
      break;
    }
    case PS3_LJoyL:
    {
      Serial.println("PS3_LJoyL Released");
      if(!joyLRight)
      {
        //Gamepad.xAxis(0);
        Joystick->setXAxis(0);
      }
      joyLLeft = false;
      break;
    }
    case PS3_LJoyR:
    {
      Serial.println("PS3_LJoyR Released");
      if(!joyLLeft)
      {
        //Gamepad.xAxis(0);
        Joystick->setXAxis(0);
      }
      joyLRight = false;
      break;
    }
    case PS3_LJoyZ:
    {
      Serial.println("PS3_LJoyZ Released");
      //Gamepad.release(11);
      Joystick->releaseButton(PS3_LJoyZMap);
      break;
    }
    case PS3_RJoyZ:
    {
      Serial.println("PS3_RJoyZ Released");
      //Gamepad.release(12);
      Joystick->releaseButton(PS3_RJoyZMap);
      break;
    }

    case PS3_L2:
    {
      Serial.println("PS3_L2 Released");
      //Gamepad.release(7);
      Joystick->releaseButton(PS3_L2Map);
      break;
    }
    case PS3_R2:
    {
      Serial.println("PS3_R2 Released");
      //Gamepad.release(8);
      Joystick->releaseButton(PS3_R2Map);
      break;
    }

    case PS3_Start:
    {
      Serial.println("PS3_Start Released");
      //Gamepad.release(10);
      Joystick->releaseButton(PS3_StartMap);
      break;
    }
    case PS3_Sel:
    {
      Serial.println("PS3_Sel");
      //Gamepad.release(9);
      Joystick->releaseButton(PS3_SelMap);
      break;
    }
  }
  //Gamepad.write();
  Joystick->sendState();
}
