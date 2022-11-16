//
// Created by erico on 11/16/22.
//

#include "Connection.h"
/*#pragma push_macro("LOG")
#undef LOG*/

Connection::Connection(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst): wiz(mosi, miso, sclk, cs, rst) {}

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
void message_handler(MQTT::MessageData& md) {
    // MQTT callback function
    MQTT::Message &message = md.message;
    char topic[md.topicName.lenstring.len + 1];
    sprintf(topic, "%.*s", md.topicName.lenstring.len, md.topicName.lenstring.data);
    char* payload = new char[message.payloadlen + 1];
    sprintf(payload, "%.*s", message.payloadlen, (char*)message.payload);
    // printf("%ld: DEBUG: Received: %s Msg: %s qos %d, retained %d, dup %d, packetid %d\n", uptime_sec, topic, payload, message.qos, message.retained, message.dup, message.id);
    char* sub_topic = topic + strlen(topic_cmnd);  // find the last word of the topic (eg: cmnd/controller00/output2)
}

void Connection::mqtt_init(const char* server_ip, int port) {
    mqttNetwork = new MQTTNetwork(&wiz);
    client  = new MQTT::Client<MQTTNetwork, Countdown>(mqttNetwork, NET_TIMEOUT_MS);
#ifdef LOG
    LOG("Connecting to MQTT Broker....\n");
#endif
    if(mqttNetwork->connect(server_ip, port, NET_TIMEOUT_MS) != MQTT::SUCCESS){
#ifdef LOG
        LOG("Couldn't connect TCP socket to broker\n");
#endif
        return;
    }
#ifdef LOG
    LOG("MQTT broker connected\n");
#endif
    MQTTPacket_connectData conn_data = MQTTPacket_connectData_initializer;
    MQTTPacket_willOptions lwt = MQTTPacket_willOptions_initializer;
    lwt.topicName.cstring = topic_lwt;
    lwt.message.cstring = (char*)"0";
    lwt.retained = true;
    conn_data.willFlag = 1;
    conn_data.will = lwt;
    conn_data.MQTTVersion = 3;
    conn_data.keepAliveInterval = MQTT_KEEPALIVE;
    conn_data.clientID.cstring = (char*)"controller";
    if(client->connect(conn_data) != MQTT::SUCCESS){
#ifdef LOG
        LOG("MQTT Client couldn't connect to broker\n");
#endif
        return;
    }

#ifdef LOG
    LOG("Connected to broker %s \n", server_ip);
#endif
    if(client->subscribe(topic_sub, MQTT::QOS1, message_handler) != MQTT::SUCCESS){
#ifdef LOG
        LOG(" MQTT Client couldn't subscribe to topic \n");
#endif
        return;
    }
#ifdef LOG
    LOG("Subscribed to %s\n", topic_sub);
#endif
}


/*#pragma pop_macro("LOG")*/




