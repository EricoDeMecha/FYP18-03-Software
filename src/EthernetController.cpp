//
// Created by erico on 10/9/22.
//

#include "EthernetController.h"

EthernetController::EthernetController(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset):
                                    wiz(mosi, miso, sclk, cs, reset), mqttNetwork(&wiz),
                                    client(mqttNetwork, NET_TIMEOUT_MS),
                                    logs(MAX_LOG) {}

void message_handler(MQTT::MessageData& md) {
    MQTT::Message &message = md.message;
    char topic[md.topicName.lenstring.len + 1];
    sprintf(topic, "%.*s", md.topicName.lenstring.len, md.topicName.lenstring.data);
    char* payload = new char[message.payloadlen + 1];
    sprintf(payload, "%.*s", message.payloadlen, (char*)message.payload);
    char* sub_topic = topic + strlen(topic_cmnd);
    // TODO: process the output
}

bool EthernetController::publish(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, char* msg_payload, bool retained) {
    // main function to publish MQTT messages
    MQTT::Message msg;
    msg.qos = MQTT::QOS1;
    msg.retained = retained;
    msg.payloadlen = strlen(msg_payload);
    msg.payload = (char*)msg_payload;
    char topic_full[30];
    strcat(topic_full, topic_pub);
    strcat(topic_full, topic);
    // printf("%ld: DEBUG: Publishing: %s to: %s\n", uptime_sec, msg.payload, topic_full);
    if (client.publish(topic_full, msg) != MQTT::SUCCESS) {
        log("%ld: Publish Error! (topic:%s msg:%s)\n", uptime_sec, topic, msg_payload);
        return false;
    }
    return true;
}

bool EthernetController::networking_init(EthernetInterface &wiz) {
    log("%ld:Start networking...", uptime_sec);
    // reset the w5500
    wiz.init();
    if (wiz.connect(NET_TIMEOUT_MS) != 0) {
        log("%ld: DHCP failed :-(", uptime_sec);
        return false;
    }
    log("%ld:%s", uptime_sec, wiz.getIPAddress());
    return true;
}


bool EthernetController::mqtt_init(MQTTNetwork &mqttNet, MQTT::Client<MQTTNetwork, Countdown> &client) {
    // TCP connect to broker
    log("%ld:Connecting to MQTT broker...", uptime_sec);
    if (mqttNet.connect((char*)mqtt_broker, mqtt_port, NET_TIMEOUT_MS) != MQTT::SUCCESS) {
        log("%ld: Couldn't connect TCP socket to broker %s",uptime_sec, mqtt_broker);
        conn_failures++;  // record this as a connection failure in case we need to reset the Wiznet
        return false;
    }
    // Client connect to broker
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
    if (client.connect(conn_data) != MQTT::SUCCESS) {
        log("%ld:Couldn't connect TCP socket to broker  %s",uptime_sec, mqtt_broker);
        conn_failures++;  // record this as a connection failure in case we need to reset the Wiznet
        return false;
    }
    log("%ld:Connected to broker  %s",uptime_sec, mqtt_broker);
    // Subscribe to topic
    if (client.subscribe(topic_sub, MQTT::QOS1, message_handler) != MQTT::SUCCESS) {
        log("%ld:MQTT Client couldn't subscribe to topic :-(", uptime_sec);
        return false;
    }

    log("%ld:Subscribed to : %s",uptime_sec, topic_sub );
    // Node online message
    publish(client, "IPAddress", mqttNet.getIPAddress(), true);
    conn_failures = 0;   // remember to reset this on success
    return true;
}

template<typename... Args>
void EthernetController::log(const string &format, Args... args) {
    int size_s = std::snprintf( nullptr, 0, "%s", format.c_str(), args ... ) + 1; // Extra space for '\0'
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, "%s", format.c_str(), args ... );
    // store
    if(logs.size() == MAX_LOG){
        logs.pop_front();
    }
    logs.emplace_back(buf.get());
}


