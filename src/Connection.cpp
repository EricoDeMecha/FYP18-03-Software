//
// Created by erico on 11/16/22.
//

#include "Connection.h"
/*#pragma push_macro("LOG")
#undef LOG*/

Connection::Connection(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst):
                                                    wiz(mosi, miso, sclk, cs, rst){
    mqttNetwork = new MQTTNetwork(&wiz);
    socket = new TCPSocketConnection();
    client = new MQTT::Client<MQTTNetwork, Countdown>(*mqttNetwork);
}

void Connection::network_init() {
#ifdef LOG
    LOG("Started networking\n");
#endif
    wiz.init(mac_addr, IP, IP_MASK, IP_GATEWAY);
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


void Connection::mqtt_init() {
#ifdef LOG
    LOG("Connecting to MQTT Broker....\n");
#endif
    MQTTPacket_connectData  conn_data = MQTTPacket_connectData_initializer;
    conn_data.keepAliveInterval = 20;
    conn_data.cleansession = 1;
    conn_data.clientID.cstring = (char*)"black_f407ve";

    MQTT::connackData connack_data{};

    if(client->connect(conn_data, connack_data) != 0){
#ifdef LOG
        LOG("MQTT connection failed!\n");
#endif
        is_mqtt_connected = false;
        return;
    }
#ifdef LOG
    LOG("MQTT connects OK\n");
#endif
    // TODO: publish and subscribe to topics
}

void Connection::maintain_connection(const char *broker_ip , int port) {
    is_net_connected = (strcmp(wiz.getIPAddress(),"0.0.0.0") != 0);
    is_sock_connected = socket->is_connected();
    is_mqtt_connected = client->isConnected();
    if(!is_net_connected){
        network_init();
    }
    if(!is_sock_connected){
        socket_connect(broker_ip, port);
    }
    if(!is_mqtt_connected){
        mqtt_init();
    }
}

void Connection::disconnect() {
    client->disconnect();
    socket->close();
    // Bring down the ethernet interface
    wiz.disconnect();
#ifdef LOG
    LOG("Disconnected\n");
#endif
}

void Connection::socket_connect(const char* host, int port) {
#ifdef  LOG
    LOG("Initiating socket connection...\n");
#endif
    if(socket->connect(host, port, NET_TIMEOUT_MS) != 0){
#ifdef  LOG
        LOG("Failed to create TCP socket connection\n");
#endif
        is_sock_connected = false;
    }else{
#ifdef  LOG
        LOG("TCP socket connected\n");
#endif
        is_sock_connected = true;
    }
}


/*#pragma pop_macro("LOG")*/




