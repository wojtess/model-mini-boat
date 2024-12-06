#include "screen.h"
#include <stdbool.h>
#include <string.h>


#define CONFIG_SDA_GPIO 8
#define CONFIG_SCL_GPIO 9

#define WHOLE_TEXT_BUFFER_SIZE 44

#define TEXT_PART_SIZE 14

#define NEEDED_SPACE 58

SSD1306_t dev;

void screen_task(void* args) {
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, 0);
    ssd1306_init(&dev, 128, 16);

    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);

    char text[] = "              PUT Powertrain #DrogaDoMonako";
    int text_len = strlen(text);

    char whole_text_buffer[NEEDED_SPACE][TEXT_PART_SIZE];
    for (int i = 0; i < text_len; i++) {
        strncpy(whole_text_buffer[i], text + i , TEXT_PART_SIZE);
    }

    int offset = 0;
    int offset1 = 0;

    while(1) {
        ssd1306_display_text(&dev, 0, whole_text_buffer[offset], TEXT_PART_SIZE , false);
        if (offset >= WHOLE_TEXT_BUFFER_SIZE){
            offset = 0;
        }
        else{
            offset++;
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}