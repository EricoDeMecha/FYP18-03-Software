//
// Created by erico on 10/18/22.
//

#ifndef FYP18_03_ETHERNET_H
#define FYP18_03_ETHERNET_H

#include "mbed.h"
#include "../logger/log.h"

#include "EthernetInterface.h"
#include "eth_messages.h"
#include "ReadBufferFixedSize.h"
#include "WriteBufferFixedSize.h"
#include "TCPSocketConnection.h"

#define NET_TIMEOUT_MS 200
#define HOST "192.168.88.83"
#define PORT 1883
#define BUFFER_SIZE 50

class Ethernet {
public:
    Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst);
    ~Ethernet()=default;
    void network_init();
    void socket_connect();
    void disconnect();
    void send_status();
    void read_status();
    bool get_net_conn_flag() const { return is_net_connected; }
    bool get_sock_conn_flag() const { return is_sock_connected; }
    void maintain_connection();
    // status wrappers
    void st_set_temperature(float& temperature){ status.set_temperature(temperature); }
    void st_set_windspeed(float& wind_speed){ status.set_windspeed(wind_speed); }
    void st_set_humidity(float& humidity){ status.set_humidity(humidity);}
private:
    EthernetInterface wiz;
    uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
    bool is_net_connected{};
    bool is_sock_connected{};
    TCPSocketConnection socket;
    unsigned long uptime_sec{};
    int result{};

    ::EmbeddedProto::ReadBufferFixedSize<BUFFER_SIZE> read_buffer;
    ::EmbeddedProto::WriteBufferFixedSize<BUFFER_SIZE> write_buffer;
    Status status;
};


#endif //FYP18_03_ETHERNET_H
