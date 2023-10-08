#include <Arduino.h>
#include "Controller.h"

const int _baud_rate = 9600;
const int _pin_horizontal = 8;
const int _pin_vertical = 1;
const int _pin_trigger = 2;

TurretSystem::Controller _controller;

void setup() 
{
  _controller.Attach(_baud_rate, _pin_horizontal, _pin_vertical, _pin_trigger);
}

void loop() 
{
  _controller.Run();
}