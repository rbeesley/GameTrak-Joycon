#include "Axis.h"

#include "1euroFilter.h"

// [Hz]
// An estimate of the frequency in Hz of the signal (> 0), if timestamps are not available.
const float FREQUENCY = 60; // Measured as 58.5-58.9 actual

// [Hz] Needs to be tuned.
// Min cutoff frequency in Hz (> 0). Lower values allow to remove more jitter.
const float MINCUTOFF = 1.0;

// Needs to be tuned.
// Parameter to reduce latency (> 0).
const float BETA      = 0.001;

// [Hz] Change this parameter only if you know what you are doing.
// Used to filter the derivates. 1 Hz by default.
const float DCUTOFF   = 1.0;

Axis::Axis(uint8_t pin, uint8_t mode, uint32_t _axisMinimum = 0, uint32_t _axisMaximum = UINT32_MAX, bool inverted = false)
        :
    _pin(pin),
    _mode(mode),
    _axisMinimum(_axisMinimum),
    _axisMaximum(_axisMaximum),
    _inverted(inverted),
    _filter(FREQUENCY, MINCUTOFF, BETA, DCUTOFF)
{
    pinMode(_pin, _mode);
    _start_time = micros();
}

Axis::~Axis()
{
}

uint32_t Axis::read()
{
    float elapsed_time = 1E-6 * (micros() - _start_time); // in seconds
    float filtered_analog = _filter.filter(static_cast<float>(analogRead(_pin)), elapsed_time);

    return constrain(_inverted ? _axisMaximum - filtered_analog : filtered_analog, _axisMinimum, _axisMaximum);
}
