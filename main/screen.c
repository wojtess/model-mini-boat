#include "screen.h"
#include <stdbool.h>
#include <string.h>

#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22

SSD1306_t dev;

void screen_task(void* args) {
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, 0);
    ssd1306_init(&dev, 128, 32);

    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
    char* text = "POWERTRAIN";
    char* text2 = "#DROGADOMONAKO";
    ssd1306_display_text(&dev, 1, text, strlen(text), false);
    ssd1306_display_text(&dev, 2, text2, strlen(text2), false);

    while(1) {

            // for(uint32_t i = 0; i < 0xFFFFFFFF;i++) {
                vTaskDelay(pdMS_TO_TICKS(200));
                ssd1306_hardware_scroll(&dev, SCROLL_LEFT);
                vTaskDelay(pdMS_TO_TICKS(50));
                ssd1306_hardware_scroll(&dev, SCROLL_STOP);
            // }

    }
}