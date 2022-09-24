//
// Created by erico on 9/20/22.
//

#include "ServoController.h"

static float clamp(float value, float min, float max) {
    if(value < min) {
        return min;
    } else if(value > max) {
        return max;
    } else {
        return value;
    }
}

ServoController::ServoController(PinName pin, float range, float degrees) : _pwm(pin) {
    _range = range;
    _degrees = degrees;
    write(0.5);// middle position
}

void ServoController::write(float percent) {
    float offset = _range * 2.0 * (percent - 0.5);
    _pwm.pulsewidth(0.0015 + clamp(offset, -_range, _range));
    _p = clamp(percent, 0.0, 1.0);
}

void ServoController::position(float degrees) {
    float offset = _range * (degrees / _degrees);
    _pwm.pulsewidth(0.0015 + clamp(offset, -_range, _range));
}

float ServoController::read() {
    return _p;
}

ServoController& ServoController::operator= (float percent) {
    write(percent);
    return *this;
}

ServoController& ServoController::operator= (ServoController& rhs) {
    write(rhs.read());
    return *this;
}

ServoController::operator float() {
    return read();
}

