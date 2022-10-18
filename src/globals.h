#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Servo.h"
#include "LA_T8.h"
#include "DS1820.h"
#include "HX711.h"
#include "AppController.h"

#include <deque>
#define MAX_LOGS 13

extern Servo servo;
extern LA_T8 laT8;
extern AppController appController;
extern DS1820 ds18b20;
extern HX711 hx711;
/*MQTT*/
extern bool connected_mqtt;
extern std::deque<std::string> logs;
#endif