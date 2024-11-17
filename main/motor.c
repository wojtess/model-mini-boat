#include "motor.h"
#include "data_types.h"

extern state_t state;

#define GPIO_PWM0A_OUT 13   // Pin wyjścia dla PWM0A
#define GPIO_PWM0B_OUT 33   // Pin wyjścia dla PWM0B

void motor_task(void *arg)
{
    // Inicjalizacja MCPWM dla jednostki MCPWM0
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);  // PWM na pinie 18 (do IN1 mostka H)
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);  // PWM na pinie 19 (do IN2 mostka H)

    // Inicjalizacja konfiguracji MCPWM
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    // Częstotliwość PWM 1 kHz
    pwm_config.cmpr_a = 0;          // Domyślny współczynnik wypełnienia dla PWM0A 0%
    pwm_config.cmpr_b = 0;          // Domyślny współczynnik wypełnienia dla PWM0B 0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    // Inicjalizacja MCPWM0

    while (1) {
        if(state.throttle > 0) {
            mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);  // IN2 nisko
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, state.throttle * 100.0);
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
        }
        if(state.throttle < 0) {
            mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);  // IN1 nisko
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, -state.throttle * 100.0);  // 50% współczynnik wypełnienia na IN2
            mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
        }

        if(state.throttle == 0) {
            mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
            mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}