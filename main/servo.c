#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"
#include "esp_log.h"
#include "servo.h"

extern state_t state;

static const char *TAG = "example";

// Parametry serwa
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimalna szerokość impulsu w mikrosekundach
#define SERVO_MAX_PULSEWIDTH_US 2500  // Maksymalna szerokość impulsu w mikrosekundach
#define SERVO_MIN_DEGREE        -90   // Minimalny kąt
#define SERVO_MAX_DEGREE        90    // Maksymalny kąt

#define SERVO_PULSE_GPIO 32  // GPIO dla sygnału PWM
#define SERVO_MAX_ANGLE 45

static inline uint32_t example_angle_to_compare(int angle)
{
    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

void servo_task(void* arg)
{
    ESP_LOGI(TAG, "Inicjalizacja MCPWM");
    // Inicjalizacja MCPWM dla jednostki MCPWM0
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PULSE_GPIO);

    // Konfiguracja MCPWM
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // Częstotliwość 50 Hz (20ms okres)
    pwm_config.cmpr_a = 0;      // Domyślna wartość wypełnienia dla PWM0A
    pwm_config.cmpr_b = 0;      // Domyślna wartość wypełnienia dla PWM0B (nieużywane)
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

    // Inicjalizacja MCPWM
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);

    // Ustawienie serwa na środek (0 stopni)
    uint32_t initial_pulsewidth = example_angle_to_compare(0);
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, initial_pulsewidth);

    ESP_LOGI(TAG, "Serwo gotowe");

    while (1) {
        float angle = state.yaw * (float)SERVO_MAX_ANGLE;
        uint32_t pulsewidth = example_angle_to_compare((int)angle);
        // ESP_LOGI(TAG, "angle: %f, pulsewidth: %ld", angle, pulsewidth);
        ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulsewidth));
        // Dodanie opóźnienia na czas obrotu serwa
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
