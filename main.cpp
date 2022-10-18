#include "mbed.h"
#include "lvgl/lvgl.h"

#include "lvglDriver/LVGLDispDriverBase.h"
#include "lvglDriver/LVGLInputDriverBase.h"

#include "ui/ui.h"
#include "src/globals.h"


#include "EthernetInterface.h"

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
 * Ethernethttps://github.com/Embedded-AMS/EmbeddedProto_Example_Mbed_to_server.git
 * */
#define NET_TIMEOUT_MS 2000

unsigned long uptime_sec = 0;
uint8_t mac_addr[6]={0x00, 0x00, 0x00, 0xBE, 0xEF,  0x99};
bool connected_net = false;

bool networking_init(EthernetInterface &wiz);
template<typename ... Args>
void log( const std::string& format, Args ... args );
// tickers

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
    EthernetInterface wiz(PC_12, PC_11, PC_10, PA_15, PC_7);

    while(1) {
        ThisThread::sleep_for(200ms);
    }
}

bool networking_init(EthernetInterface &wiz) {
    log("%ld: Start networking...\n", uptime_sec);
    // reset the w5500
    wiz.init(mac_addr);
    if (wiz.connect(NET_TIMEOUT_MS) != 0) {
        log("%ld: DHCP failed :-(\n", uptime_sec);
        return false;
    }
    log("%ld: IP: %s\n", uptime_sec, wiz.getIPAddress());
    return true;
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