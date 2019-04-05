# Gamepad Converter
This project is for converting mouse and keyboard input to a gamepad output.  The project is tailored toward playing PS3 games with a mouse and keyboard.

# Video
[![Video](https://i.ytimg.com/vi/E7YJm7XsTjs/hqdefault.jpg?sqp=-oaymwEjCPYBEIoBSFryq4qpAxUIARUAAAAAGAElAADIQj0AgKJDeAE=&rs=AOn4CLBaRyN_mt21ozxYtTNK2-raNsOy1Q)](https://youtu.be/E7YJm7XsTjs)

# Setup
Required Components:
-Arduino Leonardo (can use others, but is a hassel)
-USB Host Shield
-USB Hub (trickey to get one that works, currently using a Belking USB2 one)

Software:
You will need 2 libraries:
-[Joystick](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0)
-[USB Host Shield 2.0](https://github.com/felis/USB_Host_Shield_2.0/tree/master/examples)

If you want to change the layout of commands, open either keyboard.cpp or mouse.cpp.  In these files there will be lines such as #define PS3_X 'f'.  You can change the letter value accordingly, however for letter keys use lowercase.
