//
// Created by erico on 10/18/22.
//

#ifndef FYP18_03_ETHERNETCONTROLLER_H
#define FYP18_03_ETHERNETCONTROLLER_H

#include "mbed.h"
#include "log.h"
#include "eth_messages.h"
#include "ReadBufferFixedSize.h"
#include "WriteBufferFixedSize.h"
#include "globals.h"

#define NET_TIMEOUT_MS 2000
#define HOST "192.168.88.83"
#define PORT 1883

constexpr uint32_t BUFFER_SIZE = 50;
::EmbeddedProto::ReadBufferFixedSize<BUFFER_SIZE> read_buffer;
::EmbeddedProto::WriteBufferFixedSize<BUFFER_SIZE> write_buffer;
Status status;

class EthernetController {
public:
    EthernetController();
    void start();
    void fnEthController();
    void loop();

    void network_init();
    void sock_connect();
    void disconnect();
private:
    void _loop();
private:
    EventQueue eth_events;
    Thread eth_thread;
    uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
    bool is_net_connected{};
    bool is_sock_connected{};
    TCPSocketConnection socket;
};


#endif //FYP18_03_ETHERNETCONTROLLER_H
