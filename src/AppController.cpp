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

void AppController::lat8_eject_t(LA_T8 &laT8, chrono::milliseconds t_time) {// eject for a certain number of seconds
    lat8_operate(laT8, true);
    delay(t_time);
    lat8_operate(laT8, false);
}

void AppController::fill_up_param_vecs(int &n_steps, float& t_steps) {
    // servo_angles
    servo_angles.reserve(n_steps);
    float step_size = FULL_VALVE_TURN/n_steps;
    std::generate(servo_angles.begin(), servo_angles.end(), [n=0.0f, &step_size] () mutable {return n+=step_size; });
    std::reverse(servo_angles.begin(), servo_angles.end());
    // lat8_actuation times
    vec_t_steps.reserve(n_steps);
    std::generate(vec_t_steps.begin(), vec_t_steps.end(),
                  [n= t_steps]() mutable {
                      n -= ToMs(T_STEPS_INC);
                      return n < ToMs(1.5) ? ToMs(1.5) : n;
                  });
    std::reverse(vec_t_steps.begin(), vec_t_steps.end());
}

void AppController::read_weight(HX711 &hx711) {
    if(hx711.isReady()){
        current_weight  = hx711.read();
        is_weight_set = true;
    }
}

void AppController::queue_weight(HX711 &hx711) {
    appEvents.call(callback(this, &AppController::read_weight), hx711);
}

void AppController::read_temperature(DS1820 &ds18b20) {
    if(ds18b20.isPresent()) {
        ds18b20.startConversion();
        current_temperature = ds18b20.read();
        is_temp_set = true;
    }
}

void AppController::queue_temp(DS1820 &ds18b20) {
    appEvents.call(callback(this, &AppController::read_temperature), ds18b20);
}
