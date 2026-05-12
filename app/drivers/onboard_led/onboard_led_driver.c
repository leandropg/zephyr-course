#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT onboard_led_driver

// Logger Declaration
LOG_MODULE_REGISTER(onboard_led, LOG_LEVEL_INF);

/**
 * @brief Channel Get Onboard Led Implementation
 */
static int channel_get_onboard_led(const struct device *dev,
                                        enum sensor_channel chan,
                                        struct sensor_value *val) {
    LOG_INF("Onboard Led Channel GET");
    return 0;
}

/**
 * @brief Sample Fetch Onboard Led Implementation
 */
static int sample_fetch_onboard_led(const struct device *dev, enum sensor_channel chan) {
    
    LOG_INF("Onboard Led Sample Fetch");
    return 0;
}

static DEVICE_API(sensor, onboard_led_driver_api) = {

    .channel_get = channel_get_onboard_led,
    .sample_fetch = sample_fetch_onboard_led,
};

/**
 * @brief Onboard Led Init Function
 * @param dev Device Pointer
 */
static int onboard_led_init(const struct device* dev) {

    LOG_INF("Onboard Led Driver initialized");
    return 0;
}

// Instance Onboard Led
DEVICE_DT_INST_DEFINE(0, onboard_led_init, NULL, NULL, NULL, POST_KERNEL, 80, &onboard_led_driver_api);