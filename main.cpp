#include "mbed.h"
#include "lvgl/lvgl.h"

#include "lvglDriver/LVGLDispDriverBase.h"
#include "lvglDriver/LVGLInputDriverBase.h"

#include "ui/ui.h"
#include "src/globals.h"

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
    servo.attach(0);// Attach and enable the motor
    // start the temperature conversion
    ds18b20.begin();
    // hx711
    hx711.powerUp();
    // ethernet
    eth.network_init();

    while(1) {
        led1 = !led1;
        led2 = !led2;
        ThisThread::sleep_for(200ms);
    }
}
