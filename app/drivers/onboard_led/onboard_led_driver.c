// Zephyr Includes
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

// Sensor Include
#include "onboard_led_driver.h"

#define DT_DRV_COMPAT onboard_led_driver

/**
 * @brief Blue Led
 */
static const struct gpio_dt_spec sensor_led = GPIO_DT_SPEC_GET(DT_ALIAS(sensor_led), gpios);

// Logger Declaration
LOG_MODULE_REGISTER(onboard_led, LOG_LEVEL_INF);

/**
 * @brief Onboard Led Set Blink Counter
 * @param dev Device Pointer
 * @param count_value Count Value
 */
void onboard_led_set_blink_counter(const struct device *dev, int count_value) {

    // Obtain Onboard Led Driver data
    struct onboard_led_driver_data *data = dev->data;

    // Set Count Value
    data->blinks_count = count_value;
}

/**
 * @brief Sample Fetch Onboard Led Implementation
 */
static int sample_fetch_onboard_led(const struct device *dev, enum sensor_channel chan) {
    
    LOG_INF("Onboard Led Sample Fetch");
    
    // Obtain Onboard Led Driver data
    struct onboard_led_driver_data *data = dev->data;
    LOG_INF("Blink Counter = %d", data->blinks_count);

    // Increment Counter
    data->blinks_count += 1;
    
    // Turn On Led
    gpio_pin_set_dt(&sensor_led, 1);
    return 0;
}

/**
 * @brief Channel Get Onboard Led Implementation
 */
static int channel_get_onboard_led(const struct device *dev,
                                        enum sensor_channel chan,
                                        struct sensor_value *val) {
    LOG_INF("Onboard Led Channel Get");
    gpio_pin_set_dt(&sensor_led, 0);
    return 0;
}

static DEVICE_API(sensor, onboard_led_driver_api) = {

    .sample_fetch = sample_fetch_onboard_led,
    .channel_get = channel_get_onboard_led,
};

/**
 * @brief Onboard Led Init Function
 * @param dev Device Pointer
 */
static int onboard_led_init(const struct device* dev) {

    if (gpio_pin_configure_dt(&sensor_led, GPIO_OUTPUT_INACTIVE) < 0) return 0;
    LOG_INF("Onboard Led Driver initialized");
    return 0;
}

// Define Onboard Led Instance
#define DEV_INST(inst)                                          \
                                                                \
    /* Runtime Data */                                          \
    static struct onboard_led_driver_data data_##inst = {       \
        .blinks_count = 0,                                      \
    };                                                          \
                                                                \
    DEVICE_DT_INST_DEFINE(inst,                                 \
                            onboard_led_init,                   \
                            NULL,                               \
                            &data_##inst,                        \
                            NULL,                               \
                            POST_KERNEL,                        \
                            80,                                 \
                            &onboard_led_driver_api);           \

// Iterate all Onboard Led available
DT_INST_FOREACH_STATUS_OKAY(DEV_INST);