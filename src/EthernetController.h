//
// Created by erico on 10/9/22.
//

#ifndef FYP18_03_ETHERNETCONTROLLER_H
#define FYP18_03_ETHERNETCONTROLLER_H

#include "mbed.h"
#include "EthernetInterface.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"

#define NET_TIMEOUT_MS 2000

class EthernetController {
public:
    EthernetController(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset);
private:
    EthernetInterface wiz;
    MQTTNetwork mqttNetwork;
    MQTT::Client<MQTTNetwork, Countdown> client;
    Watchdog &wd;
};


#endif //FYP18_03_ETHERNETCONTROLLER_H
