//
// Created by erico on 9/26/22.
//

#ifndef FYP1803_SOFTWARE_APPCONTROLLER_H
#define FYP1803_SOFTWARE_APPCONTROLLER_H

#include "Servo.h"
#include "LA_T8.h"
#include "HX711.h"
#include "DS1820.h"
#include <vector>
#include <algorithm>

#define FULL_VALVE_TURN 90.0
#define T_MIN 5 // minimum time step
#define ToMs(X) (X*1000)

class AppController {
public:
    AppController();
    void start();
    void delay(chrono::milliseconds delayTime);
    // servo position
    void servo_position(Servo& servo, int angle);
    // la-t8 pos
    void lat8_operate(LA_T8& laT8, bool operate);
    void lat8_eject_t(LA_T8& laT8, chrono::milliseconds);
    // weight
    void queue_weight(HX711 &hx711);
    float get_current_weight() const { return current_weight; }
    // ds18b20
    void queue_temp(DS1820 &ds18b20);
    float get_current_temperature() const { return current_temperature; }
    // getters and setters
    void set_weight_flag(bool set) { is_weight_set = set;}
    void set_temp_flag(bool set) { is_temp_set = set; }

    bool get_weight_flag() const { return is_weight_set; }
    bool get_temp_flag() const { return is_temp_set; }
    // experiment
    void fill_up_param_vecs(int& n_steps,int& t_steps);
    int get_current_step() const { return current_step; }
    void next_step(Servo& servo , DS1820& ds18b20, LA_T8& laT8, HX711& hx711);
    void stop_experiment(Servo& servo, LA_T8& laT8);
    ~AppController()=default;
private:
    Thread appThread;
    EventQueue appEvents;
    void fnAppController();
    // weight
    void read_weight(HX711& hx711);
    // ds18b20
    void read_temperature(DS1820& ds18b20);
private:
    bool is_weight_set{};
    bool is_temp_set{};
    std::vector<int> servo_angles;
    std::vector<int> vec_t_steps;
    float current_weight{};
    float current_temperature{};
    int current_step{};
};


#endif //FYP1803_SOFTWARE_APPCONTROLLER_H