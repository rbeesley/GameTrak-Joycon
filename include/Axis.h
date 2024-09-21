#pragma once

#include <Arduino.h>

class Axis{
private:
    uint8_t _pin;
    uint8_t _mode;
    uint32_t _axisMinimum;
    uint32_t _axisMaximum;
    bool _inverted;

public:
    Axis(uint8_t pin, uint8_t mode, uint32_t _axisMinimum, uint32_t _axisMaximum, bool inverted);
    virtual ~Axis();
    uint32_t read();

    inline void setAxisRange(int32_t minimum, int32_t maximum)
    {
        _axisMinimum = minimum;
        _axisMaximum = maximum;
    }

    inline uint32_t getMinimum()
    {
        return _axisMinimum;
    }

    inline uint32_t getMaximum()
    {
        return _axisMaximum;
    }
};