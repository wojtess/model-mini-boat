#include "screen.h"
#include <stdbool.h>
#include <string.h>


#define CONFIG_SDA_GPIO 8
#define CONFIG_SCL_GPIO 9

#define WHOLE_TEXT_BUFFER_SIZE 90

#define TEXT_PART_SIZE 14

#define NEEDED_SPACE WHOLE_TEXT_BUFFER_SIZE + TEXT_PART_SIZE

SSD1306_t dev;

void screen_task(shared_t* shared_data) {
    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, 0);
    ssd1306_init(&dev, 128, 16);

    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);

    char text[200] = "";
    int text_len = strlen(text);

    char whole_text_buffer[NEEDED_SPACE][TEXT_PART_SIZE];
    for (int i = 0; i < text_len; i++) {
        strncpy(whole_text_buffer[i], text + i , TEXT_PART_SIZE);
    }

    int offset = 0;
    int offset1 = 0;

    while(1) {
        if(strcmp(text, shared_data->text) != 0) {
            strncpy(text, shared_data->text, WHOLE_TEXT_BUFFER_SIZE);

            text_len = strlen(text);

            
            memset(whole_text_buffer, 0, sizeof(whole_text_buffer));
            
            char copied_text[200];
            memset(copied_text, ' ', 14);
            memset(copied_text + 14, 0, sizeof(copied_text) - 14);
            strncpy(copied_text + 14, text, WHOLE_TEXT_BUFFER_SIZE - 14);

            text_len = strlen(copied_text);

            for (int i = 0; i < text_len; i++) {
                strncpy(whole_text_buffer[i], copied_text + i , TEXT_PART_SIZE);
            }
        }

        ssd1306_display_text(&dev, 0, whole_text_buffer[offset], TEXT_PART_SIZE , false);
        if (offset >= text_len){
            offset = 0;
        }
        else{
            offset++;
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}