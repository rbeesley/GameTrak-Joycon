#include "Axis.h"

Axis::Axis(uint8_t pin, uint8_t mode, uint32_t _axisMinimum = 0, uint32_t _axisMaximum = UINT32_MAX, bool inverted = false)
        :
    _pin(pin),
    _mode(mode),
    _axisMinimum(_axisMinimum),
    _axisMaximum(_axisMaximum),
    _inverted(inverted)
{
    pinMode(_pin, _mode);
}

Axis::~Axis()
{
}

uint32_t Axis::read()
{
    return constrain(_inverted ? _axisMaximum - analogRead(_pin) : analogRead(_pin), _axisMinimum, _axisMaximum);
}
