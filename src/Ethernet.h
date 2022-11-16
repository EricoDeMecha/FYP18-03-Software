//
// Created by erico on 10/18/22.
//

#ifndef FYP18_03_ETHERNET_H
#define FYP18_03_ETHERNET_H

#include "mbed.h"
#include "../logger/log.h"

#include "EthernetInterface.h"
#include "TCPSocketConnection.h"

#define NET_TIMEOUT_MS 99
/* Should be a secret but then again it is always offline  */
static const char*  IP = "192.168.1.15";
static const char* IP_MASK =  "255.255.255.0";
static const char* IP_GATEWAY =  "192.168.1.1";

/*Create socket connection (that is all)*/
class Ethernet {
public:
    Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst);
    ~Ethernet()=default;
    /* Network initialization is defined for static connections */
    void network_init(const char* ip, const char* ip_mask, const char* ip_gateway);
    void network_init();

    void socket_connect(const char* host, int port);
    void disconnect();
    bool is_connected() const { return is_net_connected && is_sock_connected ;}
    const char* get_ip_address(){ return wiz.getIPAddress(); }
    int get_port() {return socket.get_port();}
    auto get_socket() const { return socket; }
    void maintain_connection(const char* host, int port);
private:
    EthernetInterface wiz;
    uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
    bool is_net_connected{};
    bool is_sock_connected{};
    TCPSocketConnection socket;
    int result{};
    int bytes_read{};
private:
    const char* m_ip = IP;
    const char* m_ip_mask = IP_MASK;
    const char* m_ip_gateway = IP_GATEWAY;
};


#endif //FYP18_03_ETHERNET_H
