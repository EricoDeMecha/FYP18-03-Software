//
// Created by erico on 9/20/22.
//

#ifndef FYP1803_SOFTWARE_SERVOCONTROLLER_H
#define FYP1803_SOFTWARE_SERVOCONTROLLER_H

#include "mbed.h"

//#define RANGE 0.0005  // Pulsewidth range from center (1.5ms) to maximum/minimum position in seconds
#define RANGE 0.17
//#define DEGREES 45    // Angle from centre to maximum/minimum position in degrees
#define DEGREES 60

class ServoController {

public:
    /** Create a servo object connected to the specified PwmOut pin
     *
     * @param pin PwmOut pin to connect to
     */
    ServoController(PinName pin, float range = RANGE, float degrees = DEGREES);

    /** Set the servo position, normalised to it's full range
     *
     * @param percent A normalised number 0.0-1.0 to represent the full range.
     */
    void write(float percent);

    /**  Read the servo motors current position
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    float read();

    /** Set the servo position
     *
     * @param degrees Servo position in degrees
     */
    void position(float degrees);

    /**  Shorthand for the write and read functions */
    ServoController& operator= (float percent);
    ServoController& operator= (ServoController& rhs);
    operator float();

protected:
    PwmOut _pwm;
    float _range;
    float _degrees;
    float _p;
};


#endif //FYP1803_SOFTWARE_SERVOCONTROLLER_H
