//
// Created by erico on 9/23/22.
//

#include "ui_handler.h"
#include "ui.h"

void updateGTemperature(float  g_temperature){
    char temp_buffer[10];
    lv_snprintf(temp_buffer, sizeof(temp_buffer), "%.2f", g_temperature);
    lv_label_set_text(ui_TemperatureValueLabel, temp_buffer);
}