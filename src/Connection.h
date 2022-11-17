//
// Created by erico on 11/16/22.
//

#ifndef FYP18_03_CONNECTION_H
#define FYP18_03_CONNECTION_H

#include "mbed.h"
#include "MQTT/MQTTClient.h"
#include "MQTT/MQTTmbed.h"
#include "MQTT/MQTTPacket/MQTTConnect.h"
#include "MQTTNetwork.h"
#include "mbed_thread.h"
#include "EthernetInterface.h"
#include "TCPSocketConnection.h"
#include "logger/log.h"

#define NET_TIMEOUT_MS 99
#define MQTT_KEEPALIVE 20

/* Should be a secret but then again it is always offline  */
static const char*  IP = "192.168.1.15";
static const char* IP_MASK =  "255.255.255.0";
static const char* IP_GATEWAY =  "192.168.1.1";

class Connection {
public:
    Connection(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst);
    void network_init();
    void socket_connect(const char* host, int port);
    void mqtt_init();
    void maintain_connection(const char* broker_ip, int port);
    void disconnect();
    ~Connection(){
        disconnect();
        delete mqttNetwork;
        delete client;
        delete socket;
    }
    bool is_connected() const { return  is_mqtt_connected && is_net_connected ; }
private:
    EthernetInterface wiz;
    uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
    bool is_mqtt_connected{};
    bool is_net_connected{};
    bool is_sock_connected{};
    MQTTNetwork* mqttNetwork = nullptr;
    MQTT::Client<MQTTNetwork, Countdown>* client = nullptr;
    TCPSocketConnection* socket = nullptr;
private:
    friend void message_handler(MQTT::MessageData& md);

};


#endif //FYP18_03_CONNECTION_H
