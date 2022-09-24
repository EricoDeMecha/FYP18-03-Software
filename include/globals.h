#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include  "mbed.h"
#include "ServoController.h"
#include "DS1820.h"
#include "LA_T8.h"
#include "Hx711.h"

extern ServoController servo;
extern DS1820 ds18b20;
extern LA_T8 la_t8;
extern Hx711 hx711;
#endif