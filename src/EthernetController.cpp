//
// Created by erico on 10/18/22.
//

#include "EthernetController.h"

EthernetController::EthernetController():eth_thread(osPriorityLow, 4 * 1024, nullptr, "ethController") {
}

void EthernetController::start() {
    eth_thread.start(callback(this, &EthernetController::fnEthController));
}

void EthernetController::fnEthController() {
    eth_events.dispatch_forever();
}

void EthernetController::loop() {
    eth_events.call_every(200ms, this, &EthernetController::_loop);
}

void EthernetController::network_init() {
    log("Started networking\n");
    wiz.init(mac_addr);
    if(wiz.connect(NET_TIMEOUT_MS) != 0){
        log("DHCP Failed!!\n");
        is_net_connected = false;
        return;
    }
    is_net_connected  = true;
    log("IP: %s\n" ,wiz.getIPAddress());
}

void EthernetController::sock_connect() {
    log("Establishing TCP connection");
    if(socket.connect(HOST, PORT, NET_TIMEOUT_MS) != 0){
        log("Failed to establish TCP connection!!\n");
        is_sock_connected = false;
        return;
    }
    is_sock_connected = true;
    socket.set_blocking(false);
    log("Socked connected\n");
}

void EthernetController::disconnect() {
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    wiz.disconnect();
    log("Disconnected\n");
}

void EthernetController::_loop() {
    if(!is_net_connected){
        // queue connection
        eth_events.call(callback(this, &EthernetController::network_init));
    }
    if(!is_sock_connected){
        eth_events.call(callback(this, &EthernetController::sock_connect));
    }
}




