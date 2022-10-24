// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: fyp18032

#include <algorithm>
#include "stdio.h"
#include "ui.h"
#include "ui_helpers.h"
#include "csplit.h"
#include "../src/globals.h"
#include "../logger/log.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Home;
lv_obj_t * ui_ValveArc;
lv_obj_t * ui_ValveLabel;
lv_obj_t * ui_DiverterLabel;
lv_obj_t * ui_DiverterSwitch;
lv_obj_t * ui_TemperatureHeaderLabel;
lv_obj_t * ui_DegreesSymbolLabel;
lv_obj_t * ui_TemperatureRebaseButton;
lv_obj_t * ui_TemperatureRebaseLabel;
lv_obj_t * ui_WeightRebaseButton;
lv_obj_t * ui_WeightRebaseLabel;
lv_obj_t * ui_WeightHeaderLabel;
lv_obj_t * ui_KgSymbolLabel;
lv_obj_t * ui_ClosedLabel;
lv_obj_t * ui_HomeTitle;
lv_obj_t * ui_NextButton;
lv_obj_t * ui_NextBtnLabel;
lv_obj_t * ui_TemperatureValueLabel;
lv_obj_t * ui_WeightValueLabel;
lv_obj_t * ui_ValveArcValueLabel;
lv_obj_t * ui_ArcDegreesSymbolLabel;
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1Titlelabel;
lv_obj_t * ui_StepsSliderLabel;
lv_obj_t * ui_StepsSlider;
lv_obj_t * ui_StepsValueLabel;
lv_obj_t * ui_TimeSliderLabel;
lv_obj_t * ui_TimeValueLabel;
lv_obj_t * ui_StartButton;
lv_obj_t * ui_StartButtonTextLabel;
lv_obj_t * ui_StopButton;
lv_obj_t * ui_ResetButtonLabel;
lv_obj_t * ui_TemperatureLabel2;
lv_obj_t * ui_WeightLabel;
lv_obj_t * ui_StepNoLabel;
lv_obj_t * ui_WeightValueLabel2;
lv_obj_t * ui_TemperatureValueLabel2;
lv_obj_t * ui_TimeSlider;
lv_obj_t * ui_BackButton;
lv_obj_t * ui_BackButtonLabel;
lv_obj_t * ui_SecondsSymbolValueLabel;
lv_obj_t * ui_StepNoValueLabel;
lv_obj_t * ui_kgSymbolLabel;
lv_obj_t * ui_DegreesSymbolLabel2;
lv_obj_t * ui_NextStepButton;
lv_obj_t * ui_NextStepButtonLabel;
lv_obj_t * ui_TimeCountDownLabel;
lv_obj_t * ui_TimeCountDownValueLabel;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_TermLabel;
lv_obj_t * ui_NextButton1;
lv_obj_t * ui_NextBtnLabel1;
lv_obj_t * ui_BackButton1;
lv_obj_t * ui_BackButtonLabel1;
lv_obj_t * ui_ipTextArea;
lv_obj_t * ui_ipColonLabel;
lv_obj_t * ui_ipPortTextArea;
lv_obj_t * ui_ipKeyboard;
lv_obj_t * ui_connectBtn;
lv_obj_t * ui_connectBtnLabel;
lv_obj_t * ui_messageBox;
lv_obj_t * ui_spinner;
///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// USER DEFINED VARIABLES ////////////////////
static int n_steps = 0;
static int t_steps = 0;
static bool switched = true;
static bool is_home_screen= true;
static bool is_screen1_screen = true;
static int current_time  = 0;
static const char* ip_text = NULL;
static const char* ip_port = NULL;
static int g_port = 0;
static bool is_ip_valid;
static bool is_port_valid;
///////////////////// USER DECLARED FUNCTIONS ////////////////////
static void home_update_task();
static void screen1_update_task();
static void screen2_update_task();
///////////////////// USER DEFINED FUNCTIONS ////////////////////

static void home_update_task(){
    if(is_home_screen){
        appController.queue_temp(ds18b20);
        if(appController.get_temp_flag()){
            lv_label_set_text_fmt(ui_TemperatureValueLabel, "%.2f", appController.get_current_temperature());
            appController.set_temp_flag(false);
        }
        appController.queue_weight(hx711);
        if(appController.get_weight_flag()){
            lv_label_set_text_fmt(ui_WeightValueLabel, "%.2f", appController.get_current_weight());
            appController.set_weight_flag(false);
        }
    }
}

static void screen1_update_task(){
    if(is_screen1_screen){
        // update the time countdown label
        lv_label_set_text_fmt(ui_TimeCountDownValueLabel, "%d s", (current_time < 0 ? 0: ((current_time--)/1000)));
        // n_steps and t_steps are set now
        if(appController.get_weight_flag()){
            lv_label_set_text_fmt(ui_WeightValueLabel2, "%.2f", appController.get_current_weight());
            appController.set_weight_flag(false);
            // increment the step
            lv_label_set_text_fmt(ui_StepNoValueLabel, "%d", appController.get_current_step());
        }
        if(appController.get_temp_flag()){
            lv_label_set_text_fmt(ui_TemperatureValueLabel2, "%.2f", appController.get_current_temperature());
            appController.set_temp_flag(false);
        }
    }
}

static void screen2_update_task(){
    if(is_screen1_screen || is_home_screen){
       return;
    }
    if(!eth.is_connected()){
        if(ui_spinner)
            _ui_flag_modify(ui_spinner, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        appController.eth_maintain(eth, ip_text, g_port);
    }else{
        if(ui_spinner)
            _ui_flag_modify(ui_spinner, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    lv_label_set_text(ui_TermLabel, retrieve_log());
}
///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////


static void split(const char* s,char* c, CSplitList_t* parts) {
    char* temp = strdup(s);
    CSplitError_t  err = csplit(parts, temp, c);
    if(err != CSPLIT_SUCCESS){
        free(temp);
        return;
    }
    free(temp);
}

static bool validateIPv4(const char* IP) {
    if (std::count(IP, (IP+strlen(IP)), '.') != 3) {
        return false;
    }
    CSplitList_t* parts = csplit_init_list();
    char* delim = ".";
    split(IP, delim, parts);
    for(int i = 0; i < parts->num_elems; i++){
        char* part = csplit_get_fragment_at_index(parts, i);
        if (part == NULL || strlen(part) > 3 || strlen(part) > 1 && part[0] == '0') {
            return false;
        }
        if(!isdigit(*part)){
            return false;
        }
        if (atoi(part) > 255) {
            return false;
        }
    }
    csplit_clear_list(parts);
    return true;
}

static bool validatePort(const char* port){
    if(port == NULL || !isdigit(*port)){
        return false;
    }
    return true;
}
static void ui_event_ValveArc(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_arc_set_text_value(ui_ValveArcValueLabel, ta, "", "");
        appController.servo_position(servo, (int)lv_arc_get_value(ta));
    }
}
static void ui_event_NextButton(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0);
        is_home_screen = false;
    }
}
static void ui_event_StepsSlider(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_slider_set_text_value(ui_StepsValueLabel, ta, "", "");
    }
}
static void ui_event_StartButton(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_TimeSlider, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_StepsSlider, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
        n_steps = (int) lv_slider_get_value(ui_StepsSlider);
        t_steps = (int) lv_slider_get_value(ui_TimeSlider);
        appController.fill_up_param_vecs(n_steps, t_steps);
        // start experiment - home  the actuators
        appController.servo_position(servo, 0);
        appController.lat8_operate(laT8, false);
        // disable home screen button
        _ui_state_modify(ui_BackButton, LV_STATE_DISABLED, _UI_MODIFY_FLAG_ADD);
    }
}
static void ui_event_ResetButton(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_TimeSlider, LV_STATE_DISABLED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_StepsSlider, LV_STATE_DISABLED, _UI_MODIFY_STATE_REMOVE);
        appController.stop_experiment(servo, laT8);
        _ui_state_modify(ui_BackButton, LV_STATE_DISABLED, _UI_MODIFY_FLAG_REMOVE);
        lv_label_set_text_fmt(ui_WeightValueLabel2, "%.2f", 0.00);
        lv_label_set_text_fmt(ui_StepNoValueLabel, "%d", 0);
        lv_label_set_text_fmt(ui_TemperatureValueLabel2, "%.2f", 0.00);
        _ui_slider_set_property(ui_StepsSlider, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 0);
        _ui_slider_set_property(ui_TimeSlider, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 0);
    }
}
static void ui_event_TimeSlider(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_slider_set_text_value(ui_TimeValueLabel, ta, "", "");
    }
}
static void ui_event_BackButton(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Home, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0);
        is_home_screen = true;
    }
}
static void ui_event_DiverterSwitch(lv_event_t* e){
    switched = !switched;
    appController.lat8_operate(laT8, switched);
}

static void ui_event_NextStepButton(lv_event_t* e){
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_CLICKED){
        appController.next_step(servo, ds18b20, laT8, hx711);
        current_time = appController.get_current_time();
    }
}

static void ui_event_TemperatureRebaseButton(lv_event_t* e){
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_CLICKED){
        lv_label_set_text_fmt(ui_TemperatureValueLabel, "%.2f", 0.00);
    }
}

static void ui_event_WeightRebaseButton(lv_event_t* e){
    lv_event_code_t  event = lv_event_get_code(e);
    if(event == LV_EVENT_CLICKED){
        lv_label_set_text_fmt(ui_WeightValueLabel, "%.2f",0.00);
    }
}

static void ui_event_NextButton1(lv_event_t* e){
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_CLICKED){
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0);
        is_screen1_screen = false;
    }
}

static void ui_event_BackButton1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0);
        is_screen1_screen = true;
    }
}

static void ui_ipTextArea_cb(lv_event_t* e){
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_FOCUSED){
        _ui_flag_modify(ui_ipKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        lv_keyboard_set_textarea(ui_ipKeyboard, ui_ipTextArea);
        return;
    } else if(event == LV_EVENT_DEFOCUSED){
        _ui_flag_modify(ui_ipKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_keyboard_set_textarea(ui_ipKeyboard, NULL);
    }
}

static void ui_ipPortTextArea_cb(lv_event_t* e){
    lv_event_code_t event = lv_event_get_code(e);
    if(event == LV_EVENT_FOCUSED){
        _ui_flag_modify(ui_ipKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        lv_keyboard_set_textarea(ui_ipKeyboard, ui_ipPortTextArea);
    }else if(event  == LV_EVENT_DEFOCUSED){
        _ui_flag_modify(ui_ipKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        lv_keyboard_set_textarea(ui_ipKeyboard, NULL);
    }
}

static void ui_connectBtn_cb(lv_event_t* e){
    ip_text = lv_textarea_get_text(ui_ipTextArea);
    is_ip_valid = validateIPv4(ip_text);
    ip_port = lv_textarea_get_text(ui_ipPortTextArea);
    is_port_valid = validatePort(ip_port);
    if(!is_ip_valid || !is_port_valid){
        // raise an alert message
        //  ui_messageBox;
        ui_messageBox = lv_msgbox_create(ui_Screen2, "Warning", "Invalid ip/port format", NULL, true);
        lv_obj_set_align(ui_messageBox, LV_ALIGN_CENTER);
        lv_obj_set_x(ui_messageBox, 0);
        lv_obj_set_y(ui_messageBox, 0);
        return;
    }else{
        // spinbox
        ui_spinner = lv_spinner_create(ui_Screen2, 800, 100);
        lv_obj_set_align(ui_spinner, LV_ALIGN_CENTER);
        g_port = atoi(ip_port);
        // initiate ethernet connection maintenance
        if(!eth.is_connected()){
            appController.eth_maintain(eth, ip_text, g_port);
        }
    }
}
///////////////////// SCREENS ////////////////////
void ui_Home_screen_init(void)
{

    // ui_Home

    ui_Home = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Home, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ValveArc

    ui_ValveArc = lv_arc_create(ui_Home);

    lv_obj_set_width(ui_ValveArc, 136);
    lv_obj_set_height(ui_ValveArc, 139);

    lv_obj_set_x(ui_ValveArc, -84);
    lv_obj_set_y(ui_ValveArc, 15);

    lv_obj_set_align(ui_ValveArc, LV_ALIGN_CENTER);

    lv_arc_set_range(ui_ValveArc, 0, 90);
    lv_arc_set_bg_angles(ui_ValveArc, 120, 60);

    lv_obj_add_event_cb(ui_ValveArc, ui_event_ValveArc, LV_EVENT_ALL, NULL);

    // ui_ValveLabel

    ui_ValveLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_ValveLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ValveLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ValveLabel, -85);
    lv_obj_set_y(ui_ValveLabel, -73);

    lv_obj_set_align(ui_ValveLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_ValveLabel, "Valve");

    // ui_DiverterLabel

    ui_DiverterLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_DiverterLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DiverterLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DiverterLabel, 79);
    lv_obj_set_y(ui_DiverterLabel, -75);

    lv_obj_set_align(ui_DiverterLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_DiverterLabel, "Diverter");

    // ui_DiverterSwitch

    ui_DiverterSwitch = lv_switch_create(ui_Home);

    lv_obj_set_width(ui_DiverterSwitch, 74);
    lv_obj_set_height(ui_DiverterSwitch, 37);

    lv_obj_set_x(ui_DiverterSwitch, 76);
    lv_obj_set_y(ui_DiverterSwitch, -30);

    lv_obj_set_align(ui_DiverterSwitch, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_DiverterSwitch, ui_event_DiverterSwitch, LV_EVENT_VALUE_CHANGED, NULL);
    // ui_TemperatureHeaderLabel

    ui_TemperatureHeaderLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_TemperatureHeaderLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureHeaderLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureHeaderLabel, 44);
    lv_obj_set_y(ui_TemperatureHeaderLabel, 10);

    lv_obj_set_align(ui_TemperatureHeaderLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureHeaderLabel, "Temperature");

    // ui_DegreesSymbolLabel

    ui_DegreesSymbolLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_DegreesSymbolLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DegreesSymbolLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DegreesSymbolLabel, 56);
    lv_obj_set_y(ui_DegreesSymbolLabel, 41);

    lv_obj_set_align(ui_DegreesSymbolLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_DegreesSymbolLabel, "°C ");

    // ui_TemperatureRebaseButton

    ui_TemperatureRebaseButton = lv_btn_create(ui_Home);

    lv_obj_set_width(ui_TemperatureRebaseButton, 76);
    lv_obj_set_height(ui_TemperatureRebaseButton, 28);

    lv_obj_set_x(ui_TemperatureRebaseButton, 115);
    lv_obj_set_y(ui_TemperatureRebaseButton, 41);

    lv_obj_set_align(ui_TemperatureRebaseButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_TemperatureRebaseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_TemperatureRebaseButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_TemperatureRebaseButton, ui_event_TemperatureRebaseButton, LV_EVENT_ALL, NULL);
    // ui_TemperatureRebaseLabel

    ui_TemperatureRebaseLabel = lv_label_create(ui_TemperatureRebaseButton);

    lv_obj_set_width(ui_TemperatureRebaseLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureRebaseLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureRebaseLabel, 0);
    lv_obj_set_y(ui_TemperatureRebaseLabel, 0);

    lv_obj_set_align(ui_TemperatureRebaseLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureRebaseLabel, "Rebase");

    // ui_WeightRebaseButton

    ui_WeightRebaseButton = lv_btn_create(ui_Home);

    lv_obj_set_width(ui_WeightRebaseButton, 76);
    lv_obj_set_height(ui_WeightRebaseButton, 28);

    lv_obj_set_x(ui_WeightRebaseButton, 116);
    lv_obj_set_y(ui_WeightRebaseButton, 99);

    lv_obj_set_align(ui_WeightRebaseButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_WeightRebaseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_WeightRebaseButton, LV_OBJ_FLAG_SCROLLABLE);

    // ui_WeightRebaseLabel

    ui_WeightRebaseLabel = lv_label_create(ui_WeightRebaseButton);

    lv_obj_set_width(ui_WeightRebaseLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightRebaseLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightRebaseLabel, 0);
    lv_obj_set_y(ui_WeightRebaseLabel, 0);

    lv_obj_set_align(ui_WeightRebaseLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightRebaseLabel, "Rebase");

    lv_obj_add_event_cb(ui_WeightRebaseButton, ui_event_WeightRebaseButton, LV_EVENT_ALL, NULL);
    // ui_WeightHeaderLabel

    ui_WeightHeaderLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_WeightHeaderLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightHeaderLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightHeaderLabel, 24);
    lv_obj_set_y(ui_WeightHeaderLabel, 69);

    lv_obj_set_align(ui_WeightHeaderLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightHeaderLabel, "Weight");

    // ui_KgSymbolLabel

    ui_KgSymbolLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_KgSymbolLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_KgSymbolLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_KgSymbolLabel, 53);
    lv_obj_set_y(ui_KgSymbolLabel, 98);

    lv_obj_set_align(ui_KgSymbolLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_KgSymbolLabel, " kg");

    // ui_ClosedLabel

    ui_ClosedLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_ClosedLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ClosedLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ClosedLabel, -125);
    lv_obj_set_y(ui_ClosedLabel, 101);

    lv_obj_set_align(ui_ClosedLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_ClosedLabel, "Closed");

    // ui_HomeTitle

    ui_HomeTitle = lv_label_create(ui_Home);

    lv_obj_set_width(ui_HomeTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_HomeTitle, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_HomeTitle, -10);
    lv_obj_set_y(ui_HomeTitle, -105);

    lv_obj_set_align(ui_HomeTitle, LV_ALIGN_CENTER);

    lv_label_set_text(ui_HomeTitle, "FYP18-03");
    lv_label_set_recolor(ui_HomeTitle, "true");

    // ui_NextButton

    ui_NextButton = lv_btn_create(ui_Home);

    lv_obj_set_width(ui_NextButton, 56);
    lv_obj_set_height(ui_NextButton, 23);

    lv_obj_set_x(ui_NextButton, 129);
    lv_obj_set_y(ui_NextButton, -103);

    lv_obj_set_align(ui_NextButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NextButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_NextButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_NextButton, ui_event_NextButton, LV_EVENT_ALL, NULL);

    // ui_NextBtnLabel

    ui_NextBtnLabel = lv_label_create(ui_NextButton);

    lv_obj_set_width(ui_NextBtnLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NextBtnLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NextBtnLabel, 0);
    lv_obj_set_y(ui_NextBtnLabel, 0);

    lv_obj_set_align(ui_NextBtnLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_NextBtnLabel, "Next");

    // ui_TemperatureValueLabel

    ui_TemperatureValueLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_TemperatureValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureValueLabel, 26);
    lv_obj_set_y(ui_TemperatureValueLabel, 41);

    lv_obj_set_align(ui_TemperatureValueLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureValueLabel, "0.00");

    // ui_WeightValueLabel

    ui_WeightValueLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_WeightValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightValueLabel, 28);
    lv_obj_set_y(ui_WeightValueLabel, 97);

    lv_obj_set_align(ui_WeightValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightValueLabel, "0.00");

    // ui_ValveArcValueLabel

    ui_ValveArcValueLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_ValveArcValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ValveArcValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ValveArcValueLabel, -83);
    lv_obj_set_y(ui_ValveArcValueLabel, 12);

    lv_obj_set_align(ui_ValveArcValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_ValveArcValueLabel, "0");
    lv_label_set_recolor(ui_ValveArcValueLabel, "true");

    // ui_ArcDegreesSymbolLabel

    ui_ArcDegreesSymbolLabel = lv_label_create(ui_Home);

    lv_obj_set_width(ui_ArcDegreesSymbolLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ArcDegreesSymbolLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ArcDegreesSymbolLabel, -68);
    lv_obj_set_y(ui_ArcDegreesSymbolLabel, 2);

    lv_obj_set_align(ui_ArcDegreesSymbolLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_ArcDegreesSymbolLabel, "°");

}
void ui_Screen1_screen_init(void)
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Screen1Titlelabel

    ui_Screen1Titlelabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_Screen1Titlelabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Screen1Titlelabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Screen1Titlelabel, 0);
    lv_obj_set_y(ui_Screen1Titlelabel, -108);

    lv_obj_set_align(ui_Screen1Titlelabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Screen1Titlelabel, "Coefficient of Discharge");
    lv_label_set_recolor(ui_Screen1Titlelabel, "true");

    // ui_StepsSliderLabel

    ui_StepsSliderLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_StepsSliderLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepsSliderLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepsSliderLabel, -127);
    lv_obj_set_y(ui_StepsSliderLabel, -76);

    lv_obj_set_align(ui_StepsSliderLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepsSliderLabel, "Steps");

    // ui_StepsSlider

    ui_StepsSlider = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_StepsSlider, 0, 100);

    lv_obj_set_width(ui_StepsSlider, 169);
    lv_obj_set_height(ui_StepsSlider, 18);

    lv_obj_set_x(ui_StepsSlider, -2);
    lv_obj_set_y(ui_StepsSlider, -75);

    lv_obj_set_align(ui_StepsSlider, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_StepsSlider, ui_event_StepsSlider, LV_EVENT_ALL, NULL);

    // ui_StepsValueLabel

    ui_StepsValueLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_StepsValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepsValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepsValueLabel, 111);
    lv_obj_set_y(ui_StepsValueLabel, -77);

    lv_obj_set_align(ui_StepsValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepsValueLabel, "0");

    // ui_TimeSliderLabel

    ui_TimeSliderLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TimeSliderLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeSliderLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeSliderLabel, -130);
    lv_obj_set_y(ui_TimeSliderLabel, -38);

    lv_obj_set_align(ui_TimeSliderLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeSliderLabel, "Time");

    // ui_TimeValueLabel

    ui_TimeValueLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TimeValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeValueLabel, 114);
    lv_obj_set_y(ui_TimeValueLabel, -34);

    lv_obj_set_align(ui_TimeValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeValueLabel, "0");

    // ui_StartButton

    ui_StartButton = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_StartButton, 61);
    lv_obj_set_height(ui_StartButton, 32);

    lv_obj_set_x(ui_StartButton, 27);
    lv_obj_set_y(ui_StartButton, 4);

    lv_obj_set_align(ui_StartButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_StartButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_StartButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_StartButton, ui_event_StartButton, LV_EVENT_ALL, NULL);

    // ui_StartButtonTextLabel

    ui_StartButtonTextLabel = lv_label_create(ui_StartButton);

    lv_obj_set_width(ui_StartButtonTextLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartButtonTextLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartButtonTextLabel, 1);
    lv_obj_set_y(ui_StartButtonTextLabel, -1);

    lv_obj_set_align(ui_StartButtonTextLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StartButtonTextLabel, "Start");

    // ui_StopButton

    ui_StopButton = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_StopButton, 61);
    lv_obj_set_height(ui_StopButton, 32);

    lv_obj_set_x(ui_StopButton, 102);
    lv_obj_set_y(ui_StopButton, 5);

    lv_obj_set_align(ui_StopButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_StopButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_StopButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_StopButton, ui_event_ResetButton, LV_EVENT_ALL, NULL);

    // ui_ResetButtonLabel

    ui_ResetButtonLabel = lv_label_create(ui_StopButton);

    lv_obj_set_width(ui_ResetButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ResetButtonLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ResetButtonLabel, 0);
    lv_obj_set_y(ui_ResetButtonLabel, -1);

    lv_obj_set_align(ui_ResetButtonLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_ResetButtonLabel, "Reset");

    // ui_TemperatureLabel2

    ui_TemperatureLabel2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TemperatureLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureLabel2, 27);
    lv_obj_set_y(ui_TemperatureLabel2, 72);

    lv_obj_set_align(ui_TemperatureLabel2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureLabel2, "Temperature:");

    // ui_WeightLabel

    ui_WeightLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_WeightLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightLabel, 44);
    lv_obj_set_y(ui_WeightLabel, 45);

    lv_obj_set_align(ui_WeightLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightLabel, "Weight:");

    // ui_StepNoLabel

    ui_StepNoLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_StepNoLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepNoLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepNoLabel, -115);
    lv_obj_set_y(ui_StepNoLabel, 42);

    lv_obj_set_align(ui_StepNoLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepNoLabel, "Step No:");

    // Time countdown
    ui_TimeCountDownLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TimeCountDownLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeCountDownLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeCountDownLabel, -100);
    lv_obj_set_y(ui_TimeCountDownLabel, 72);

    lv_obj_set_align(ui_TimeCountDownLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeCountDownLabel, "Time: ");

    // ui_TimeCountDownValueLabel

    ui_TimeCountDownValueLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TimeCountDownValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeCountDownValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeCountDownValueLabel, -50);
    lv_obj_set_y(ui_TimeCountDownValueLabel, 72);

    lv_obj_set_align(ui_TimeCountDownValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeCountDownValueLabel, "0 s");

    // ui_WeightValueLabel2

    ui_WeightValueLabel2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_WeightValueLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightValueLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightValueLabel2, 101);
    lv_obj_set_y(ui_WeightValueLabel2, 45);

    lv_obj_set_align(ui_WeightValueLabel2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightValueLabel2, "0");

    // ui_TemperatureValueLabel2

    ui_TemperatureValueLabel2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_TemperatureValueLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureValueLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureValueLabel2, 103);
    lv_obj_set_y(ui_TemperatureValueLabel2, 72);

    lv_obj_set_align(ui_TemperatureValueLabel2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureValueLabel2, "0");

    // ui_TimeSlider

    ui_TimeSlider = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_TimeSlider, 0, 100);

    lv_obj_set_width(ui_TimeSlider, 170);
    lv_obj_set_height(ui_TimeSlider, 18);

    lv_obj_set_x(ui_TimeSlider, 2);
    lv_obj_set_y(ui_TimeSlider, -35);

    lv_obj_set_align(ui_TimeSlider, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_TimeSlider, ui_event_TimeSlider, LV_EVENT_ALL, NULL);

    // ui_BackButton

    ui_BackButton = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_BackButton, 61);
    lv_obj_set_height(ui_BackButton, 25);

    lv_obj_set_x(ui_BackButton, -126);
    lv_obj_set_y(ui_BackButton, 102);

    lv_obj_set_align(ui_BackButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BackButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BackButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BackButton, ui_event_BackButton, LV_EVENT_ALL, NULL);

    // ui_BackButtonLabel

    ui_BackButtonLabel = lv_label_create(ui_BackButton);

    lv_obj_set_width(ui_BackButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BackButtonLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BackButtonLabel, 0);
    lv_obj_set_y(ui_BackButtonLabel, -1);

    lv_obj_set_align(ui_BackButtonLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_BackButtonLabel, "Back");

    // ui_NextStepButton
    ui_NextStepButton = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_NextStepButton, 100);
    lv_obj_set_height(ui_NextStepButton, 25);

    lv_obj_set_x(ui_NextStepButton,  100);
    lv_obj_set_y(ui_NextStepButton, 102);

    lv_obj_set_align(ui_NextStepButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NextStepButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_NextStepButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_NextStepButton, ui_event_NextStepButton, LV_EVENT_ALL, NULL);

    // ui_NextButtonLabel

    ui_NextStepButtonLabel = lv_label_create(ui_NextStepButton);

    lv_obj_set_width(ui_NextStepButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NextStepButtonLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NextStepButtonLabel, 0);
    lv_obj_set_y(ui_NextStepButtonLabel, -1);

    lv_obj_set_align(ui_NextStepButtonLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_NextStepButtonLabel, "Next Step");
    // ui_SecondsSymbolValueLabel

    ui_SecondsSymbolValueLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_SecondsSymbolValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SecondsSymbolValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SecondsSymbolValueLabel, 145);
    lv_obj_set_y(ui_SecondsSymbolValueLabel, -33);

    lv_obj_set_align(ui_SecondsSymbolValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_SecondsSymbolValueLabel, "s");

    // ui_StepNoValueLabel

    ui_StepNoValueLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_StepNoValueLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepNoValueLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepNoValueLabel, -59);
    lv_obj_set_y(ui_StepNoValueLabel, 42);

    lv_obj_set_align(ui_StepNoValueLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepNoValueLabel, "0");

    // ui_kgSymbolLabel

    ui_kgSymbolLabel = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_kgSymbolLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_kgSymbolLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_kgSymbolLabel, 138);
    lv_obj_set_y(ui_kgSymbolLabel, 46);

    lv_obj_set_align(ui_kgSymbolLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_kgSymbolLabel, "kg");

    // ui_DegreesSymbolLabel2

    ui_DegreesSymbolLabel2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_DegreesSymbolLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DegreesSymbolLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DegreesSymbolLabel2, 140);
    lv_obj_set_y(ui_DegreesSymbolLabel2, 73);

    lv_obj_set_align(ui_DegreesSymbolLabel2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_DegreesSymbolLabel2, "°C");

    // ui_NextButton1

    ui_NextButton1 = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_NextButton1, 56);
    lv_obj_set_height(ui_NextButton1, 23);

    lv_obj_set_x(ui_NextButton1, 129);
    lv_obj_set_y(ui_NextButton1, -103);

    lv_obj_set_align(ui_NextButton1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NextButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_NextButton1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_NextButton1, ui_event_NextButton1, LV_EVENT_ALL, NULL);

    // ui_NextBtnLabel1

    ui_NextBtnLabel1 = lv_label_create(ui_NextButton1);

    lv_obj_set_width(ui_NextBtnLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NextBtnLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NextBtnLabel1, 0);
    lv_obj_set_y(ui_NextBtnLabel1, 0);

    lv_obj_set_align(ui_NextBtnLabel1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_NextBtnLabel1, "Next");

}

void ui_Screen2_screen_init(void){
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);
    // term label
    ui_TermLabel = lv_label_create(ui_Screen2);

    lv_obj_set_width(ui_TermLabel, 310);
    lv_obj_set_height(ui_TermLabel, 210);

    lv_obj_set_x(ui_TermLabel, 0);
    lv_obj_set_y(ui_TermLabel, 20);

    lv_obj_set_align(ui_TermLabel, LV_ALIGN_BOTTOM_LEFT);

    // ui_BackButton

    ui_BackButton1 = lv_btn_create(ui_Screen2);

    lv_obj_set_width(ui_BackButton1, 61);
    lv_obj_set_height(ui_BackButton1, 25);

    lv_obj_set_x(ui_BackButton1, -126);
    lv_obj_set_y(ui_BackButton1, 102);

    lv_obj_set_align(ui_BackButton1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BackButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BackButton1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BackButton1, ui_event_BackButton1, LV_EVENT_ALL, NULL);

    // ui_BackButtonLabel

    ui_BackButtonLabel1 = lv_label_create(ui_BackButton1);

    lv_obj_set_width(ui_BackButtonLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BackButtonLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BackButtonLabel1, 0);
    lv_obj_set_y(ui_BackButtonLabel1, -1);

    lv_obj_set_align(ui_BackButtonLabel1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_BackButtonLabel1, "Back");

    // ui_ipTextArea
    ui_ipTextArea = lv_textarea_create(ui_Screen2);
    lv_textarea_set_placeholder_text(ui_ipTextArea ,"192.168.88.83");
    lv_textarea_set_one_line(ui_ipTextArea, true);
    lv_obj_align(ui_ipTextArea, LV_ALIGN_TOP_LEFT, 10, 0);
    lv_obj_set_size(ui_ipTextArea, 120, 30);
    lv_obj_add_event_cb(ui_ipTextArea, ui_ipTextArea_cb, LV_EVENT_ALL, NULL);
    ui_ipKeyboard = lv_keyboard_create(ui_Screen2);
    lv_keyboard_set_mode(ui_ipKeyboard, LV_KEYBOARD_MODE_NUMBER);
    _ui_flag_modify(ui_ipKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // ui_ip_dot1
    ui_ipColonLabel = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_ipColonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ipColonLabel, LV_SIZE_CONTENT);
    lv_obj_align(ui_ipColonLabel, LV_ALIGN_TOP_LEFT, 132, 8);
    lv_label_set_text(ui_ipColonLabel, ":");

    // ui_ipPortTextArea
    ui_ipPortTextArea = lv_textarea_create(ui_Screen2);
    lv_textarea_set_placeholder_text(ui_ipPortTextArea ,"1883");
    lv_textarea_set_one_line(ui_ipPortTextArea, true);
    lv_obj_align(ui_ipPortTextArea, LV_ALIGN_TOP_LEFT, 137, 0);
    lv_obj_set_size(ui_ipPortTextArea, 60, 30);
    lv_obj_add_event_cb(ui_ipPortTextArea, ui_ipPortTextArea_cb, LV_EVENT_ALL, NULL);

    // ui_connectBtn

    ui_connectBtn = lv_btn_create(ui_Screen2);

    lv_obj_set_width(ui_connectBtn, 76);
    lv_obj_set_height(ui_connectBtn, 28);

    lv_obj_set_x(ui_connectBtn, 118);
    lv_obj_set_y(ui_connectBtn, -103);

    lv_obj_set_align(ui_connectBtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_connectBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_connectBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_connectBtn, ui_connectBtn_cb, LV_EVENT_CLICKED, NULL);
    // ui_connectBtnLabel

    ui_connectBtnLabel = lv_label_create(ui_connectBtn);

    lv_obj_set_width(ui_connectBtnLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_connectBtnLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_connectBtnLabel, 0);
    lv_obj_set_y(ui_connectBtnLabel, 0);

    lv_obj_set_align(ui_connectBtnLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_connectBtnLabel, "connect");
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Home_screen_init();
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Home->user_data = (void*) home_update_task;
    ui_Screen1->user_data = (void*) screen1_update_task;
    ui_Screen2->user_data = (void*) screen2_update_task;
    lv_disp_load_scr(ui_Home);
}

