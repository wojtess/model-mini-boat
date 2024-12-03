/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "screen.h"
#include "driver/adc.h"
#include "servo.h"
#include "data_types.h"
#include "joystick.h"
#include "motor.h"
#include "led.h"
#include "esp_rest.h"

#include <fcntl.h>

#include "esp_spiffs.h"

state_t state;

static const char* TAG = "main";

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void app_main() {
    // xTaskCreatePinnedToCore(adc_task, "adc_task", 4096, NULL, 3, NULL, 0);
    // xTaskCreatePinnedToCore(servo_task, "servo_task", 4096, NULL, 3, NULL, 0);
    // xTaskCreatePinnedToCore(motor_task, "motor_task", 4096, NULL, 3, NULL, 0);
    // xTaskCreatePinnedToCore(led_task, "led_task", 4096, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(screen_task, "screen_task", 4096, NULL, 3, NULL, 0);
    // xTaskCreatePinnedToCore(rest_task, "rest_task", 4096, NULL, 3, NULL, 0);

}
   

