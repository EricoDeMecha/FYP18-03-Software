#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "Servo.h"
#include "LA_T8.h"
#include "DS1820.h"
#include "HX711.h"
//#include "Ethernet.h"
#include "Connection.h"
#include "AppController.h"

extern Servo servo;
extern LA_T8 laT8;
extern AppController appController;
extern DS1820 ds18b20;
extern HX711 hx711;
//extern Ethernet eth;
extern Connection conn;
#endif