//
// Created by erico on 9/26/22.
//

#include "AppController.h"

AppController::AppController() :
                appThread(osPriorityAboveNormal, 4*1024, nullptr, "appController")
                {}

void AppController::start() {
    appThread.start(callback(this, &AppController::fnAppController));
}

void AppController::delay(chrono::milliseconds delayTime) {
    appEvents.call(thread_sleep_for, delayTime.count());
}

void AppController::fnAppController() {
    appEvents.dispatch_forever();
}

void AppController::servo_position(Servo &servo, int angle) {
    appEvents.call(callback(&servo, &Servo::write), angle);
}

void AppController::lat8_operate(LA_T8 &laT8, bool operate) {
    appEvents.call(callback(&laT8, &LA_T8::operate), operate);
}