#include <stdio.h>
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "i2c_bus.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_console.h"


void i2c_setup(void)
{
  i2c_master_bus_config_t i2c_bus_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_NUM_0,
    .sda_io_num = 7,
    .scl_io_num = 8,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
  };
}

void app_main(void)
{
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {  
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = true,
        }};
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    lv_disp_t *disp = lv_disp_get_default();
    bsp_display_rotate(disp, LV_DISP_ROTATION_90);

    bsp_display_lock(0); 

    lv_obj_t *screen = lv_obj_create(lv_screen_active());
    lv_obj_center(screen);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xFF), LV_STATE_DEFAULT);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    bsp_display_unlock();
}
