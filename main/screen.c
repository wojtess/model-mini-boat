#include "screen.h"
#include <stdbool.h>
#include <string.h>
#include "font8x8_basic.h"

#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22

#define WHOLE_TEXT_BUFFER_SIZE 20

SSD1306_t dev;

void screen_task(void* args) {
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, 0);
    ssd1306_init(&dev, 128, 32);

    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);

    char text[] = "Hello";
    int text_len = strlen(text);

    uint8_t whole_text_buffer[WHOLE_TEXT_BUFFER_SIZE][8];
    memset(whole_text_buffer, 0, sizeof(whole_text_buffer));
    for (int i = 0; i < text_len; i++) {
        memcpy(whole_text_buffer[i], font8x8_basic_tr[(uint8_t)text[i]], 8);
    }

    int offset = 0;
    int offset1 = 0;

    while(1) {
        if((8 * (16 - text_len) - offset) < 0) {
            offset1 = 0;
            ssd1306_display_image(&dev, 0, 8 * (16 - text_len) - offset, ((void*)whole_text_buffer[0]), 8 * text_len);
        
            // offset = 0;
            offset1++;
        } else {
            offset++;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
    // char* text = "POWERTRAIN";
    // char* text2 = "#DROGADOMONAKO";
    // ssd1306_display_text(&dev, 1, text, strlen(text), false);
    // ssd1306_display_text(&dev, 2, text2, strlen(text2), false);

    // while(1) {

    //         // for(uint32_t i = 0; i < 0xFFFFFFFF;i++) {
    //             vTaskDelay(pdMS_TO_TICKS(200));
    //             ssd1306_hardware_scroll(&dev, SCROLL_LEFT);
    //             vTaskDelay(pdMS_TO_TICKS(50));
    //             ssd1306_hardware_scroll(&dev, SCROLL_STOP);
    //         // }

    // }
}