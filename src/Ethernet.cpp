//
// Created by erico on 10/18/22.
//

#include "Ethernet.h"
/*#pragma push_macro("LOG")
#undef LOG*/

Ethernet::Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst):
        wiz(mosi, miso, sclk, cs, rst)  {}

void Ethernet::network_init(const char* ip, const char* ip_mask, const char* ip_gateway) {
    m_ip = ip;
    m_ip_mask = ip_mask;
    m_ip_gateway = ip_gateway;
#ifdef LOG
    LOG("Started networking\n");
#endif
    wiz.init(mac_addr, ip, ip_mask, ip_gateway);
    if(wiz.connect(NET_TIMEOUT_MS) != 0){
#ifdef LOG
        LOG("DHCP Failed!!\n");
#endif
        is_net_connected = false;
        return;
    }
    is_net_connected  = true;
#ifdef LOG
    LOG("IP: %s\n" ,wiz.getIPAddress());
#endif
}
void Ethernet::network_init() {
    network_init(m_ip, m_ip_mask, m_ip_gateway);
}


void Ethernet::socket_connect(const char* host, int port) {
#ifdef LOG
    LOG("%Establishing TCP connection\n");
    LOG("%s->%s:%d\n",wiz.getIPAddress(),host, port);
#endif
    if(socket.connect(host, port, NET_TIMEOUT_MS) != 0){
#ifdef LOG
        LOG("Failed to establish TCP connection!!\n");
#endif
        is_sock_connected = false;
        return;
    }
    is_sock_connected = true;
//    socket.set_blocking(false);
#ifdef LOG
    LOG("Socket connected\n");
#endif
}

void Ethernet::disconnect() {
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    wiz.disconnect();
#ifdef LOG
    LOG("Disconnected\n");
#endif
}


void Ethernet::maintain_connection(const char* host, int port) {
    is_net_connected = (strcmp(wiz.getIPAddress(),"0.0.0.0") != 0);
    is_sock_connected = socket.is_connected();
    if(!is_net_connected){
        network_init();
    }
    if(!is_sock_connected){
        socket_connect(host, port);
    }
}


/*#pragma pop_macro("LOG")*/
