//
// Created by erico on 10/18/22.
//

#ifndef FYP18_03_ETHERNET_H
#define FYP18_03_ETHERNET_H

#include "mbed.h"
#include "../logger/log.h"

#include "EthernetInterface.h"
#include "proto_src/proto_msg.h"
#include "ReadBufferFixedSize.h"
#include "WriteBufferFixedSize.h"
#include "TCPSocketConnection.h"

#define NET_TIMEOUT_MS 99
#define BUFFER_SIZE 250

static const char*  IP = "192.168.1.15";
static const char* IP_MASK =  "255.255.255.0";
static const char* IP_GATEWAY =  "192.168.1.1";

class Ethernet {
public:
    Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst);
    ~Ethernet()=default;
    void network_init();
    void socket_connect(const char* host, int port);
    void disconnect();
    bool is_connected(){ return  (strcmp(wiz.getIPAddress(),"0.0.0.0") != 0) && socket.is_connected(); }
    void maintain_connection(const char* host, int port);
    // status wrappers
    void send_data();
    void read_data();
    Command& command(){ return  m_command; }
    Reply& reply(){ return m_reply; }
private:
    EthernetInterface wiz;
    uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
    bool is_net_connected{};
    bool is_sock_connected{};
    TCPSocketConnection socket;
    size_t uptime_sec{};
    int result{};

    ::EmbeddedProto::ReadBufferFixedSize<BUFFER_SIZE> read_buffer;
    ::EmbeddedProto::WriteBufferFixedSize<BUFFER_SIZE> write_buffer;

    Command m_command;
    Reply m_reply;
};


#endif //FYP18_03_ETHERNET_H
