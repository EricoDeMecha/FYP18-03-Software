//
// Created by erico on 9/26/22.
//

#ifndef FYP1803_SOFTWARE_APPCONTROLLER_H
#define FYP1803_SOFTWARE_APPCONTROLLER_H

#include "Servo.h"
#include "LA_T8.h"

class AppController {
public:
    AppController();
    void start();
    void delay(chrono::milliseconds delayTime);
    // servo position
    void servo_position(Servo& servo, int angle);
    // la-t8 pos
    void lat8_operate(LA_T8& laT8, bool operate);

    ~AppController()=default;
private:
    Thread appThread;
    EventQueue appEvents;
    void fnAppController();
};


#endif //FYP1803_SOFTWARE_APPCONTROLLER_H
