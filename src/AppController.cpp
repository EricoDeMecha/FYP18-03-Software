//
// Created by erico on 9/26/22.
//

#include "AppController.h"

AppController::AppController() :
        appThread(osPriorityAboveNormal, 4 * 1024, nullptr, "appController") {}

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

void AppController::fill_up_param_vecs(int &n_steps, int &t_steps) {
    if (n_steps == 0) {
        return;
    }
    // servo_angles
    servo_angles.resize(n_steps, 0);
    int step_size = static_cast<int>(FULL_VALVE_TURN / n_steps);
    std::generate(servo_angles.begin(), servo_angles.end(), [n = 0, &step_size]() mutable { return n += step_size; });
    // lat8_actuation times
    vec_t_steps.resize(n_steps, 0);
    int t_size = static_cast<int>((ToMs(t_steps) - ToMs(T_MIN)) / n_steps);
    std::generate(vec_t_steps.begin(), vec_t_steps.end(),
                  [n = ToMs(t_steps), &t_size]() mutable {
                      n -= t_size;
                      return n < ToMs(T_MIN) ? ToMs(T_MIN) : n;
                  });
    // current_step
    current_step = 0;
}

void AppController::read_weight(HX711 &hx711) {
    if (hx711.isReady()) {
        current_weight = hx711.read();
        is_weight_set = true;
    }
}

void AppController::queue_weight(HX711 &hx711) {
    appEvents.call(callback(this, &AppController::read_weight), hx711);
}

void AppController::read_temperature(DS1820 &ds18b20) {
    if (ds18b20.isPresent()) {
        ds18b20.startConversion();
        current_temperature = ds18b20.read();
        is_temp_set = true;
    }
}

void AppController::queue_temp(DS1820 &ds18b20) {
    appEvents.call(callback(this, &AppController::read_temperature), ds18b20);
}

void AppController::next_step(Servo &servo, DS1820 &ds18b20, LA_T8 &laT8, HX711 &hx711) {
    // queue the next experiment event
    if (static_cast<std::vector<int>::size_type>(current_step) >= (servo_angles.size())) {
        return;
    }
    servo_position(servo, servo_angles.at(current_step));
    // current time
    current_time = vec_t_steps.at(current_step);
    // delay
    chrono::milliseconds t_eject = chrono::milliseconds(current_time);
    lat8_eject_t(laT8, t_eject);
    // read the temperature
    queue_temp(ds18b20);
    // read the weight
    queue_weight(hx711);
    // increment current_step
    current_step += 1;
}

void AppController::stop_experiment(Servo &servo, LA_T8 &laT8) {
    servo_position(servo, 0);
    lat8_operate(laT8, false);
    vec_t_steps.clear();
    servo_angles.clear();
    current_step = 0;
}

void AppController::eth_maintain(Ethernet& eth_ctrl, const char* host, int port) {
    if(host != nullptr){
        appEvents.call(callback(&eth_ctrl, &Ethernet::maintain_connection),host, port);
        delay((chrono::milliseconds)(NET_TIMEOUT_MS*2));
    }
}

void AppController::eth_send(Ethernet& eth_ctrl) {
    if(eth_ctrl.is_connected()){
        appEvents.call(callback(&eth_ctrl, &Ethernet::send_status));
    }
}

void AppController::eth_receive(Ethernet& eth_ctrl) {
    if(eth_ctrl.is_connected()){
        appEvents.call(callback(&eth_ctrl, &Ethernet::read_status));
        is_sock_data_received = true;
    }
}

void AppController::send_dummy_data(Ethernet &eth_ctrl) {
    float temperature = 5.0 * ((float)rand() / (float) RAND_MAX) + 20.0; //random number between 20.0 and 25.0
    float humidity = 30.0 * ((float)rand() / (float) RAND_MAX) + 50.0; //random number between 50.0 and 80.0
    float windspeed = 20.0 * ((float)rand() / (float) RAND_MAX); //random number between 0 and 20.0

    eth_ctrl.st_set_humidity(humidity);
    eth_ctrl.st_set_temperature(temperature);
    eth_ctrl.st_set_windspeed(windspeed);
}

void AppController::set_data(Ethernet& eth_ctrl) {
    appEvents.call(callback(this, &AppController::send_dummy_data), eth_ctrl);
}


