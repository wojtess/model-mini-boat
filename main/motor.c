#include "motor.h"
#include "data_types.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

extern state_t state;

#define GPIO_PWM0A_OUT 1   // Output pin for PWM0A
#define GPIO_PWM0B_OUT 2  // Output pin for PWM0B

#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES       LEDC_TIMER_8_BIT // 8-bit resolution for duty cycle (0-255)
#define LEDC_FREQUENCY      1000             // 1 kHz PWM frequency

void motor_task(shared_t *shared_data)
{
    // Configure LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num  = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY
    };
    ledc_timer_config(&ledc_timer);

    // Configure LEDC channels
    ledc_channel_config_t ledc_channel_a = {
        .speed_mode = LEDC_MODE,
        .channel    = LEDC_CHANNEL_0,
        .timer_sel  = LEDC_TIMER,
        .intr_type  = LEDC_INTR_DISABLE,
        .gpio_num   = GPIO_PWM0A_OUT,
        .duty       = 0,
        .hpoint     = 0
    };
    
    ledc_channel_config_t ledc_channel_b = {
        .speed_mode = LEDC_MODE,
        .channel    = LEDC_CHANNEL_1,
        .timer_sel  = LEDC_TIMER,
        .intr_type  = LEDC_INTR_DISABLE,
        .gpio_num   = GPIO_PWM0B_OUT,
        .duty       = 0,
        .hpoint     = 0
    };

    gpio_config_t gpio_conf = {
        .pin_bit_mask = (1ULL << 0),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&gpio_conf);
    

    ledc_channel_config(&ledc_channel_a);
    ledc_channel_config(&ledc_channel_b);

    while (1) {
        if(shared_data->throttle > 0) {
            gpio_set_level(0, 1);
            // Forward direction
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, 0);  // Set channel B to 0
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
            
            // Convert throttle (0-100) to duty cycle (0-255)
            uint32_t duty = (shared_data->throttle * 255) / 100;
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0);
        }
        else if(shared_data->throttle < 0) {
            gpio_set_level(0, 1);
            // Reverse direction
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, 0);  // Set channel A to 0
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0);
            
            // Convert throttle (-100-0) to duty cycle (0-255)
            uint32_t duty = (-shared_data->throttle * 255) / 100;
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
        }
        else {
            gpio_set_level(0, 0);
            // Stop - set both channels to 0
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, 0);
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, 0);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
