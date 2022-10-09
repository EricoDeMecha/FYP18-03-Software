//
// Created by erico on 10/9/22.
//

#include "EthernetController.h"

EthernetController::EthernetController(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset): wiz(mosi, miso, sclk, cs, reset), mqttNetwork(&wiz), client(mqttNetwork, NET_TIMEOUT_MS), wd(Watchdog::get_instance()) {
}

