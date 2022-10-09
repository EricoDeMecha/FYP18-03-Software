#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Servo.h"
#include "LA_T8.h"
#include "DS1820.h"
#include "HX711.h"
#include "AppController.h"
#include "EthernetController.h"

extern Servo servo;
extern LA_T8 laT8;
extern AppController appController;
extern DS1820 ds18b20;
extern HX711 hx711;
extern EthernetController ethernetController;
#endif