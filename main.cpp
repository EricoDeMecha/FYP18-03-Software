#include "mbed.h"
#include "lvgl/lvgl.h"

#include "lvglDriver/LVGLDispDriverBase.h"
#include "lvglDriver/LVGLInputDriverBase.h"

#include "ui/ui.h"
#include "src/globals.h"

/*MQTT*/
#include "EthernetInterface.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"


using rtos::Kernel::Clock;

Ticker ticker_lvgl;

DigitalOut led1(LED1, 0);
DigitalOut led2(LED2, 1);

//
// lv Ticker, executed in interrupt context
//

void fnLvTicker()
{
    lv_tick_inc(5); /*Tell LittlevGL that 2 milliseconds were elapsed*/
}

typedef void (*lv_update_cb_t)(bool);

[[maybe_unused]] static void lv_screen_update(lv_timer_t* timer)
{
	static lv_obj_t* last_screen = nullptr;
	lv_obj_t* act_screen = lv_disp_get_scr_act((lv_disp_t*)timer->user_data);// use the  user data

	last_screen = act_screen;
	if (act_screen && act_screen->user_data) {// Active screen and active screen user data are available
		((lv_update_cb_t)act_screen->user_data)(act_screen != last_screen);
	}
}

[[noreturn]] void lvglThreadFn()
{
    while (true) {
        lv_task_handler();
        ThisThread::sleep_for(10ms);
    }
}

Thread  lvgl_thread(osPriorityLow, 8192);// thread for LVGL GUI handling


/*
 * MQTT
 * */

#define WATCHDOG_TIMEOUT_MS 9999
#define NET_TIMEOUT_MS 2000
#define MQTT_KEEPALIVE 20
#define LOOP_SLEEP_MS 99

unsigned long uptime_sec = 0;
const char* mqtt_broker = "192.168.1.1";
const int mqtt_port = 1883;
uint8_t conn_failures = 0;
char* topic_lwt = "stat/controller/online";
char* topic_sub = "cmnd/controller/+";
char* topic_cmnd = "cmnd/controller/";
char* topic_pub = "stat/controller/";
bool connected_net = false;

Watchdog &wd = Watchdog::get_instance();
Ticker tick_every1s;
Ticker tick_every500ms;

bool networking_init(EthernetInterface &wiz);
bool mqtt_init(MQTTNetwork &mqttNet, MQTT::Client<MQTTNetwork, Countdown> &client);
void message_handler(MQTT::MessageData& md);
bool publish(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, char* msg_payload, bool retained = false);
bool publish_num(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, int num, bool retained = false);
template<typename ... Args>
void log( const std::string& format, Args ... args );
// tickers
void every_second(){
    uptime_sec++;
    if(connected_mqtt){
        led1 = !led1;
        led2 = !led2;
    }
    wd.kick();
}

void every_500ms(){
    if(connected_net && !connected_mqtt) {
        led1 = !led1;
        led2 = !led2;
    }
}

int main(){
    printf("Mbed ScannerController\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    sleep_manager_lock_deep_sleep();
    // Start the controller thread
    appController.start();
    LVGLDispDriver*  lvgl_display      = LVGLDispDriver::get_target_default_instance();
    LVGLInputDriver::get_target_default_instance_touchdrv(lvgl_display);
    
    // register update handler. Task will call screen dependent cyclic updates
	lv_timer_create(lv_screen_update, 200,  lvgl_display->getLVDisp());// update every 200ms
    
    //start threads
    ticker_lvgl.attach(&fnLvTicker, 5ms);
    
    // main screen
    ui_init();
    lvgl_thread.start(lvglThreadFn);
    /*APP INITs*/
    // servo
    servo.attach(SERVO_POS_MIN);// Attach and enable the motor
    // start the temperature conversion
    ds18b20.begin();
    // hx711
    hx711.powerUp();

    /*MQTT*/
    wd.start(WATCHDOG_TIMEOUT_MS);
    EthernetInterface wiz(PB_14, PC_3, PB_13, PB_12, PA_3);
    MQTTNetwork mqttNetwork(&wiz);
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork, NET_TIMEOUT_MS);

    tick_every500ms.attach(every_500ms, 0.5);
    tick_every1s.attach(every_second, 1);

    wd.kick();

    while(1) {
        if(!connected_net){
            led1 = !led1;
            led2 = !led2;
            connected_mqtt = false;
            connected_net = networking_init(wiz);
        }else{
            if(!connected_mqtt){
                connected_mqtt = mqtt_init(mqttNetwork, client);
                if (conn_failures > 3) {      // wiznet could be bad, re-initialise
                    log("%ld: Too many connection failures! Resetting wiznet...\n", uptime_sec);
                    connected_net = false;
                    conn_failures = 0;
                }
            }else{
                // we are connected, do stuff
                connected_mqtt = client.isConnected();
            }
            client.yield(LOOP_SLEEP_MS);
        }
        ThisThread::sleep_for(LOOP_SLEEP_MS);
    }
}

bool networking_init(EthernetInterface &wiz) {
    log("%ld: Start networking...\n", uptime_sec);
    // reset the w5500
    wiz.init();
    if (wiz.connect(NET_TIMEOUT_MS) != 0) {
        log("%ld: DHCP failed :-(\n", uptime_sec);
        return false;
    }
    log("%ld: IP: %s\n", uptime_sec, wiz.getIPAddress());
    return true;
}


bool mqtt_init(MQTTNetwork &mqttNet, MQTT::Client<MQTTNetwork, Countdown> &client) {
    // TCP connect to broker
    log("%ld: Connecting to MQTT broker...\n", uptime_sec);
    if (mqttNet.connect((char*)mqtt_broker, mqtt_port, NET_TIMEOUT_MS) != MQTT::SUCCESS) {
        log("%ld: Couldn't connect TCP socket to broker %s :-(\n", uptime_sec, mqtt_broker);
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
        log("%ld: MQTT Client couldn't connect to broker %s :-(\n", uptime_sec, mqtt_broker);
        conn_failures++;  // record this as a connection failure in case we need to reset the Wiznet
        return false;
    }
    log("%ld: Connected to broker %s :-)\n", uptime_sec, mqtt_broker);
    // Subscribe to topic
    if (client.subscribe(topic_sub, MQTT::QOS1, message_handler) != MQTT::SUCCESS) {
        log("%ld: MQTT Client couldn't subscribe to topic :-(\n", uptime_sec);
        return false;
    }
    printf("%ld: Subscribed to %s\n", uptime_sec, topic_sub);
    // Node online message
    publish(client, "IPAddress", mqttNet.getIPAddress(), true);
    publish_num(client, "online", 1, true);
    conn_failures = 0;   // remember to reset this on success
    return true;
}

void message_handler(MQTT::MessageData& md){
    // MQTT callback function
    MQTT::Message &message = md.message;
    char topic[md.topicName.lenstring.len + 1];
    sprintf(topic, "%.*s", md.topicName.lenstring.len, md.topicName.lenstring.data);
    char* payload = new char[message.payloadlen + 1];
    sprintf(payload, "%.*s", message.payloadlen, (char*)message.payload);
    char* sub_topic = topic + strlen(topic_cmnd);  // find the last word of the topic (eg: cmnd/controller00/output2)

    /*TODO - process the output*/
}


bool publish(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, char* msg_payload, bool retained) {
    // main function to publish MQTT messages
    MQTT::Message msg;
    msg.qos = MQTT::QOS1;
    msg.retained = retained;
    msg.payloadlen = strlen(msg_payload);
    msg.payload = (char*)msg_payload;
    char topic_full[30];
    strcat(topic_full, topic_pub);
    strcat(topic_full, topic);
    if (client.publish(topic_full, msg) != MQTT::SUCCESS) {
        log("%ld: Publish Error! (topic:%s msg:%s)\n", uptime_sec, topic, msg_payload);
        return false;
    }
    return true;
}

bool publish_num(MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, int num, bool retained) {
    char message[10];
    sprintf(message, "%d", num);
    return publish(client, topic, message, retained);
}

template<typename ... Args>
void log( const std::string& format, Args ... args ){
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    // store
    if(logs.size() == MAX_LOGS){
        logs.pop_front();
    }
    logs.emplace_back(std::string( buf.get(), buf.get() + size - 1 ));
}