#include "data_types.h"
#include "joystick.h"

extern state_t state;

const static char *TAG = "POWERTRAIN IS THE BEST";

/*---------------------------------------------------------------
        ADC General Macros
---------------------------------------------------------------*/

#define ADC2_CHAN0          ADC_CHANNEL_2
#define ADC2_CHAN1          ADC_CHANNEL_1

#define ADC_ATTEN           ADC_ATTEN_DB_12
#define ADC_LOG

static int adc_raw[2];
static int voltage[2];
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);
static void example_adc_calibration_deinit(adc_cali_handle_t handle);

void adc_task(void* args)
{
    //-------------ADC2 Init---------------//
    adc_oneshot_unit_handle_t adc2_handle;
    adc_oneshot_unit_init_cfg_t init_config2 = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config2, &adc2_handle));

    //-------------ADC2 Calibration Init---------------//
    adc_cali_handle_t adc2_chan0_cali_handle = NULL;
    adc_cali_handle_t adc2_chan1_cali_handle = NULL;
    bool do_calibration2_chan0 = example_adc_calibration_init(ADC_UNIT_2, ADC2_CHAN0, ADC_ATTEN, &adc2_chan0_cali_handle);
    bool do_calibration2_chan1 = example_adc_calibration_init(ADC_UNIT_2, ADC2_CHAN1, ADC_ATTEN, &adc2_chan1_cali_handle);

    //-------------ADC2 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, ADC2_CHAN0, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, ADC2_CHAN1, &config));

    while (1) {
        ESP_ERROR_CHECK(adc_oneshot_read(adc2_handle, ADC2_CHAN0, &adc_raw[0]));
        #ifdef ADC_LOG
        ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_2 + 1, ADC2_CHAN0, adc_raw[0]);
        #endif
        if (do_calibration2_chan0) {
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc2_chan0_cali_handle, adc_raw[0], &voltage[0]));
            state.throttle = (float)voltage[0] / (3126.0f / 2.0f) - 1;
            #ifdef ADC_LOG
            ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV, throttle: %f", ADC_UNIT_2 + 1, ADC2_CHAN0, voltage[0], state.throttle);
            #endif
        }
        ESP_ERROR_CHECK(adc_oneshot_read(adc2_handle, ADC2_CHAN1, &adc_raw[1]));
        #ifdef ADC_LOG
        ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_2 + 1, ADC2_CHAN1, adc_raw[1]);
        #endif
        if (do_calibration2_chan1) {
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc2_chan0_cali_handle, adc_raw[1], &voltage[1]));
            state.yaw = (float)voltage[1] / (3126.0f / 2.0f) - 1;
            #ifdef ADC_LOG
            ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV, yaw: %f", ADC_UNIT_2 + 1, ADC2_CHAN1, voltage[1], state.yaw);
            #endif
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc2_handle));
    if (do_calibration2_chan0 && do_calibration2_chan1) {
        example_adc_calibration_deinit(adc2_chan0_cali_handle);
        example_adc_calibration_deinit(adc2_chan1_cali_handle);
    }
}

/*---------------------------------------------------------------
        ADC Calibration
---------------------------------------------------------------*/
static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
}

static void example_adc_calibration_deinit(adc_cali_handle_t handle)
{
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    ESP_LOGI(TAG, "deregister %s calibration scheme", "Curve Fitting");
    ESP_ERROR_CHECK(adc_cali_delete_scheme_curve_fitting(handle));

#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    ESP_LOGI(TAG, "deregister %s calibration scheme", "Line Fitting");
    ESP_ERROR_CHECK(adc_cali_delete_scheme_line_fitting(handle));
#endif
}
