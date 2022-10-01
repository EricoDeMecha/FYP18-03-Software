//
// Created by erico on 9/26/22.
//

#ifndef FYP1803_SOFTWARE_APPCONTROLLER_H
#define FYP1803_SOFTWARE_APPCONTROLLER_H

#include "Servo.h"
#include "LA_T8.h"
#include "HX711.h"
#include "DS1820.h"

class AppController {
public:
    AppController();
    void start();
    void delay(chrono::milliseconds delayTime);
    // servo position
    void servo_position(Servo& servo, int angle);
    // la-t8 pos
    void lat8_operate(LA_T8& laT8, bool operate);
    // experiment
    void start_experiment(Servo& servo, LA_T8& laT8, DS1820& ds1820, HX711& hx711, int& n_steps, float& t_steps);
    ~AppController()=default;
private:
    Thread appThread;
    EventQueue appEvents;
    void fnAppController();
};


#endif //FYP1803_SOFTWARE_APPCONTROLLER_H
