#include "globals.h"

ServoController servo(PC_8,0.17,60);//calibration for an MG996R Servo motor
DS1820 ds18b20(PD_2); // data pin for ds18b20
LA_T8 la_t8(PD_12, PD_14); // PD_12 is an EJECT relay and PD_14 is a RETRACT relay switch
Hx711 hx7111(PD_9, PD_11,50682624,10);