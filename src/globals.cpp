#include "globals.h"


Servo servo(PC_8);//calibration for an MG996R Servo motor
LA_T8 laT8(PE_6, PC_13);
DS1820 ds18b20(PE_2);
HX711 hx711(3.2f, PD_11, PD_12, 32);    // avdd in Volts, sck pin, dout pin, gain
AppController appController;