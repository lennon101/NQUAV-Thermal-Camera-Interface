# JoystickShield

JoystickShield is an [Arduino](http://arduino.cc) library that can be used with [JoystickShield](http://www.sparkfun.com/products/9760).

The library supports both event based (callback) mode and the normal mode. Refer to the examples to find out how to use the library in both modes.

The library supports the following events:

*   All 8 directions of Joystick (Up, RightUp, Right, RightDown, Down, LeftDown, Left and LeftUp)
*   plus amplitude of joystick (position) for each axis (in % from -100% to 100% per axis)
*   Button presses: 4 main button press (Up, Right, Down, Left), Joystick and special buttons F and E
*   Buttons are not mutually exclusive - more than one can be pressed at a time
*   calibrate Joystick function

## Examples

The library has two examples sketches which explain the modes

*   SimpleExample - Shows the normal way of using the library
*   CallbackExample - Shows how to use the library in callback mode.

## Explanation

Explanation/documentation of the library can be found at its [homepage](http://hardwarefun.com/projects/joystick-shield)

## License

The source code of this library and the examples are released under "THE BEER-WARE" license.

I would, however, consider it a great courtesy if you could email me and tell me about your project and how this code was used, just for my own continued personal gratification :)

You can also find other ways to [make me happy](http://sudarmuthu.com/if-you-wanna-thank-me), if you liked this project.

## Note

More details about the library can be found at its [homepage](http://hardwarefun.com/projects/joystick-shield).
