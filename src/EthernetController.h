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
#include <deque>
#include <memory>
#include <string>
#include <stdexcept>


#define MAX_LOG 100
#define MQTT_KEEPALIVE 20
#define NET_TIMEOUT_MS 2000

class EthernetController {
public:
    EthernetController(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset);
    bool networking_init(EthernetInterface &wiz);
    bool mqtt_init(MQTTNetwork &mqttNet, MQTT::Client<MQTTNetwork, Countdown> &client);

    friend void message_handler(MQTT::MessageData& md);
    bool publish(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, char* msg_payload, bool retained = false);
private:
    EthernetInterface wiz;
    MQTTNetwork mqttNetwork;
    MQTT::Client<MQTTNetwork, Countdown> client;

    const char* mqtt_broker = "192.168.1.1";
    const int mqtt_port = 1883;
    unsigned long uptime_sec = 0;
    uint8_t conn_failures = 0;

    // publishing and subscription
    char* topic_sub = "cmnd/controller/+";
    char* topic_cmnd = "cmnd/controller/";
    char* topic_pub = "stat/controller/";
    char* topic_lwt = "stat/controller/online";
    // log  errors
    template<typename ... Args>
    void log( const std::string& format, Args ... args );
    std::deque<const char*> logs;
};


#endif //FYP18_03_ETHERNETCONTROLLER_H
