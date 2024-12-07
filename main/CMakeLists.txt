idf_component_register(SRCS "esp_rest.c"
                            "rest_server.c"
                            "screen.c"
                            "main.c"
                            "servo.c"
                            "joystick.c"
                            "motor.c"
                            "led_strip_encoder.c"
                            "led.c"
                    INCLUDE_DIRS ".")


set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../front/a")
if(EXISTS ${WEB_SRC_DIR}/build)
    spiffs_create_partition_image(www ${WEB_SRC_DIR}/build FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR}/dist doesn't exit. Please run 'npm run build' in ${WEB_SRC_DIR}")
endif()

