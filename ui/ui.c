// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: FYP1803

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_MainWindow;
lv_obj_t * ui_StartNStopPanel;
lv_obj_t * ui_startBtn;
lv_obj_t * ui_startLbl;
lv_obj_t * ui_stopBtn;
lv_obj_t * ui_stopLbl;
lv_obj_t * ui_StepsPanel;
lv_obj_t * ui_StepsSliderLbl;
lv_obj_t * ui_StepsSlider;
lv_obj_t * ui_StepsText;
lv_obj_t * ui_TimePanel;
lv_obj_t * ui_TimeSliderLbl;
lv_obj_t * ui_TimeSlider;
lv_obj_t * ui_TimeText;
lv_obj_t * ui_StepNumberPanel;
lv_obj_t * ui_StepNumberLbl;
lv_obj_t * ui_StepNumberTxt;
lv_obj_t * ui_TemperaturePanel;
lv_obj_t * ui_TemperatureLbl;
lv_obj_t * ui_TemperatureTxt;
lv_obj_t * ui_WeightPanel;
lv_obj_t * ui_WeightLbl;
lv_obj_t * ui_WeightTxt;
lv_obj_t * ui_StatusPanel;
lv_obj_t * ui_StatusTxt;
lv_obj_t * ui_TitlePanel;
lv_obj_t * ui_TitleLbl;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_StepsSlider(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_slider_set_text_value(ui_StepsSliderLbl, ta, "", "");
    }
}
static void ui_event_TimeSlider(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_VALUE_CHANGED) {
        _ui_slider_set_text_value(ui_TimeSliderLbl, ta, "", "");
    }
}

///////////////////// SCREENS ////////////////////
void ui_MainWindow_screen_init(void)
{

    // ui_MainWindow

    ui_MainWindow = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_MainWindow, LV_OBJ_FLAG_SCROLLABLE);

    // ui_StartNStopPanel

    ui_StartNStopPanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_StartNStopPanel, 140);
    lv_obj_set_height(ui_StartNStopPanel, 41);

    lv_obj_set_x(ui_StartNStopPanel, 84);
    lv_obj_set_y(ui_StartNStopPanel, 8);

    lv_obj_set_align(ui_StartNStopPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_StartNStopPanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_startBtn

    ui_startBtn = lv_btn_create(ui_StartNStopPanel);

    lv_obj_set_width(ui_startBtn, 62);
    lv_obj_set_height(ui_startBtn, 33);

    lv_obj_set_x(ui_startBtn, -9);
    lv_obj_set_y(ui_startBtn, -1);

    lv_obj_set_align(ui_startBtn, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_startBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_startBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_startBtn, 18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_startLbl

    ui_startLbl = lv_label_create(ui_startBtn);

    lv_obj_set_width(ui_startLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_startLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_startLbl, 0);
    lv_obj_set_y(ui_startLbl, 0);

    lv_obj_set_align(ui_startLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_startLbl, "Start");

    // ui_stopBtn

    ui_stopBtn = lv_btn_create(ui_StartNStopPanel);

    lv_obj_set_width(ui_stopBtn, 62);
    lv_obj_set_height(ui_stopBtn, 33);

    lv_obj_set_x(ui_stopBtn, 10);
    lv_obj_set_y(ui_stopBtn, 0);

    lv_obj_set_align(ui_stopBtn, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_stopBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_stopBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_stopBtn, 18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_stopLbl

    ui_stopLbl = lv_label_create(ui_stopBtn);

    lv_obj_set_width(ui_stopLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_stopLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_stopLbl, 0);
    lv_obj_set_y(ui_stopLbl, 0);

    lv_obj_set_align(ui_stopLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_stopLbl, "Stop");

    // ui_StepsPanel

    ui_StepsPanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_StepsPanel, 312);
    lv_obj_set_height(ui_StepsPanel, 40);

    lv_obj_set_x(ui_StepsPanel, -1);
    lv_obj_set_y(ui_StepsPanel, -75);

    lv_obj_set_align(ui_StepsPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_StepsPanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_StepsSliderLbl

    ui_StepsSliderLbl = lv_label_create(ui_StepsPanel);

    lv_obj_set_width(ui_StepsSliderLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepsSliderLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepsSliderLbl, 123);
    lv_obj_set_y(ui_StepsSliderLbl, 1);

    lv_obj_set_align(ui_StepsSliderLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepsSliderLbl, "0");

    // ui_StepsSlider

    ui_StepsSlider = lv_slider_create(ui_StepsPanel);
    lv_slider_set_range(ui_StepsSlider, 0, 100);

    lv_obj_set_width(ui_StepsSlider, 188);
    lv_obj_set_height(ui_StepsSlider, 15);

    lv_obj_set_x(ui_StepsSlider, 2);
    lv_obj_set_y(ui_StepsSlider, -1);

    lv_obj_set_align(ui_StepsSlider, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_StepsSlider, ui_event_StepsSlider, LV_EVENT_ALL, NULL);

    // ui_StepsText

    ui_StepsText = lv_label_create(ui_StepsPanel);

    lv_obj_set_width(ui_StepsText, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepsText, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepsText, -129);
    lv_obj_set_y(ui_StepsText, 0);

    lv_obj_set_align(ui_StepsText, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepsText, "Steps");

    // ui_TimePanel

    ui_TimePanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_TimePanel, 312);
    lv_obj_set_height(ui_TimePanel, 40);

    lv_obj_set_x(ui_TimePanel, 0);
    lv_obj_set_y(ui_TimePanel, -33);

    lv_obj_set_align(ui_TimePanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_TimePanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TimeSliderLbl

    ui_TimeSliderLbl = lv_label_create(ui_TimePanel);

    lv_obj_set_width(ui_TimeSliderLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeSliderLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeSliderLbl, 123);
    lv_obj_set_y(ui_TimeSliderLbl, 1);

    lv_obj_set_align(ui_TimeSliderLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeSliderLbl, "0");

    // ui_TimeSlider

    ui_TimeSlider = lv_slider_create(ui_TimePanel);
    lv_slider_set_range(ui_TimeSlider, 0, 100);

    lv_obj_set_width(ui_TimeSlider, 188);
    lv_obj_set_height(ui_TimeSlider, 15);

    lv_obj_set_x(ui_TimeSlider, 2);
    lv_obj_set_y(ui_TimeSlider, -1);

    lv_obj_set_align(ui_TimeSlider, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_TimeSlider, ui_event_TimeSlider, LV_EVENT_ALL, NULL);

    // ui_TimeText

    ui_TimeText = lv_label_create(ui_TimePanel);

    lv_obj_set_width(ui_TimeText, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeText, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeText, -129);
    lv_obj_set_y(ui_TimeText, 0);

    lv_obj_set_align(ui_TimeText, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TimeText, "Time");

    // ui_StepNumberPanel

    ui_StepNumberPanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_StepNumberPanel, 106);
    lv_obj_set_height(ui_StepNumberPanel, 28);

    lv_obj_set_x(ui_StepNumberPanel, -100);
    lv_obj_set_y(ui_StepNumberPanel, 47);

    lv_obj_set_align(ui_StepNumberPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_StepNumberPanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_StepNumberLbl

    ui_StepNumberLbl = lv_label_create(ui_StepNumberPanel);

    lv_obj_set_width(ui_StepNumberLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepNumberLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepNumberLbl, 29);
    lv_obj_set_y(ui_StepNumberLbl, -1);

    lv_obj_set_align(ui_StepNumberLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepNumberLbl, "12");
    lv_label_set_recolor(ui_StepNumberLbl, "true");

    lv_obj_set_style_text_color(ui_StepNumberLbl, lv_color_hex(0x0091FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StepNumberLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StepNumberTxt

    ui_StepNumberTxt = lv_label_create(ui_StepNumberPanel);

    lv_obj_set_width(ui_StepNumberTxt, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StepNumberTxt, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StepNumberTxt, -18);
    lv_obj_set_y(ui_StepNumberTxt, -1);

    lv_obj_set_align(ui_StepNumberTxt, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StepNumberTxt, "Step No.");

    // ui_TemperaturePanel

    ui_TemperaturePanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_TemperaturePanel, 155);
    lv_obj_set_height(ui_TemperaturePanel, 28);

    lv_obj_set_x(ui_TemperaturePanel, 77);
    lv_obj_set_y(ui_TemperaturePanel, 46);

    lv_obj_set_align(ui_TemperaturePanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_TemperaturePanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TemperatureLbl

    ui_TemperatureLbl = lv_label_create(ui_TemperaturePanel);

    lv_obj_set_width(ui_TemperatureLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureLbl, 52);
    lv_obj_set_y(ui_TemperatureLbl, 0);

    lv_obj_set_align(ui_TemperatureLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureLbl, "12");

    lv_obj_set_style_text_color(ui_TemperatureLbl, lv_color_hex(0x0091FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TemperatureLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TemperatureTxt

    ui_TemperatureTxt = lv_label_create(ui_TemperaturePanel);

    lv_obj_set_width(ui_TemperatureTxt, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureTxt, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureTxt, -18);
    lv_obj_set_y(ui_TemperatureTxt, -1);

    lv_obj_set_align(ui_TemperatureTxt, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TemperatureTxt, "Temperature:");

    // ui_WeightPanel

    ui_WeightPanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_WeightPanel, 155);
    lv_obj_set_height(ui_WeightPanel, 28);

    lv_obj_set_x(ui_WeightPanel, 77);
    lv_obj_set_y(ui_WeightPanel, 79);

    lv_obj_set_align(ui_WeightPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_WeightPanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_WeightLbl

    ui_WeightLbl = lv_label_create(ui_WeightPanel);

    lv_obj_set_width(ui_WeightLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightLbl, 52);
    lv_obj_set_y(ui_WeightLbl, 0);

    lv_obj_set_align(ui_WeightLbl, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightLbl, "12");

    lv_obj_set_style_text_color(ui_WeightLbl, lv_color_hex(0x0091FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WeightLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_WeightTxt

    ui_WeightTxt = lv_label_create(ui_WeightPanel);

    lv_obj_set_width(ui_WeightTxt, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WeightTxt, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WeightTxt, 0);
    lv_obj_set_y(ui_WeightTxt, -1);

    lv_obj_set_align(ui_WeightTxt, LV_ALIGN_CENTER);

    lv_label_set_text(ui_WeightTxt, "Weight:");

    // ui_StatusPanel

    ui_StatusPanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_StatusPanel, 313);
    lv_obj_set_height(ui_StatusPanel, 22);

    lv_obj_set_x(ui_StatusPanel, 1);
    lv_obj_set_y(ui_StatusPanel, 106);

    lv_obj_set_align(ui_StatusPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_StatusPanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_StatusTxt

    ui_StatusTxt = lv_label_create(ui_StatusPanel);

    lv_obj_set_width(ui_StatusTxt, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StatusTxt, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StatusTxt, 0);
    lv_obj_set_y(ui_StatusTxt, 0);

    lv_obj_set_align(ui_StatusTxt, LV_ALIGN_CENTER);

    lv_label_set_long_mode(ui_StatusTxt, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_StatusTxt, "Status");

    // ui_TitlePanel

    ui_TitlePanel = lv_obj_create(ui_MainWindow);

    lv_obj_set_width(ui_TitlePanel, 313);
    lv_obj_set_height(ui_TitlePanel, 22);

    lv_obj_set_x(ui_TitlePanel, 0);
    lv_obj_set_y(ui_TitlePanel, -109);

    lv_obj_set_align(ui_TitlePanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_TitlePanel, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TitleLbl

    ui_TitleLbl = lv_label_create(ui_TitlePanel);

    lv_obj_set_width(ui_TitleLbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TitleLbl, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TitleLbl, 0);
    lv_obj_set_y(ui_TitleLbl, 0);

    lv_obj_set_align(ui_TitleLbl, LV_ALIGN_CENTER);

    lv_label_set_long_mode(ui_TitleLbl, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_TitleLbl, "CoD Experiment");

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainWindow_screen_init();
    lv_disp_load_scr(ui_MainWindow);
}

