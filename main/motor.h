#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"
#include "esp_attr.h"
#include "soc/mcpwm_periph.h"
#include "data_types.h"

void motor_task(shared_t *arg);