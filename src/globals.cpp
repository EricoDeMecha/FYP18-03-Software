#include "globals.h"


Servo servo(PC_8);//calibration for an MG996R Servo motor
LA_T8 laT8(PE_6, PC_13);
DS1820 ds18b20(PE_2);
HX711 hx711(255.0f, PB_10, PE_15, 64, 21.0f);     // avdd Volts, sck pin, dout pin, gain
Ethernet eth(PC_12, PC_11, PC_10, PA_15, PC_7);
AppController appController;