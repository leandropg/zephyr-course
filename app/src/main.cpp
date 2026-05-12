// Zephyr Includes
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

// Sensor Include
#include "../drivers/onboard_led/onboard_led_driver.h"

/**
 * @brief App Led
 */
static const struct gpio_dt_spec app_led = GPIO_DT_SPEC_GET(DT_ALIAS(app_led), gpios);

/**
 * @brief Sensor Led through Sensor API
 */
static const struct device *onboard_led_dev = DEVICE_DT_GET(DT_NODELABEL(onboard_led0));

/**
 * @brief Log Register
 */
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/**
 * Onboard Led Sample Fetch
 */
int onboard_led_sample_fetch() {

    int error_code = sensor_sample_fetch(onboard_led_dev);
    LOG_INF("Sample Fetch. Error Code: %d", error_code);
    return 0;
}

/**
 * Onboard Led Channel Get
 */
int onboard_led_channel_get() {

    struct sensor_value val;
    int error_code = sensor_channel_get(onboard_led_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    LOG_INF("Get Channel. Error Code: %d", error_code);
    return 0;
}

int main(void)
{
    bool led_state = true;

    if (!gpio_is_ready_dt(&app_led)) return -ENODEV;

    if (!device_is_ready(onboard_led_dev)) return -ENODEV;

    // Set Blink Counter Value
    onboard_led_set_blink_counter(onboard_led_dev, 100);

    if (gpio_pin_configure_dt(&app_led, GPIO_OUTPUT_INACTIVE) < 0) return 0;

    LOG_INF("Starting...");

    while (1) {

        // Toggle Leds
        if (led_state) {

            onboard_led_sample_fetch();
            gpio_pin_set_dt(&app_led, 1);
        
        } else {

            onboard_led_channel_get();
            gpio_pin_set_dt(&app_led, 0);
        }

        // Show current state
        LOG_INF("LEDs state: %s", led_state ? "ON" : "OFF");

        // Change State next cycle
        led_state = !led_state;

        // Sleep for some miliseconds
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
