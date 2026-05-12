#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

/**
 * @brief Led 0
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

/**
 * @brief Led 1 through Sensor API
 */
static const struct device* onboard_led = DEVICE_DT_GET_ANY(onboard_led);

/**
 * @brief Log Register
 */
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/**
 * Onboard Led Channel Get
 */
int onboard_led_channel_get() {

    struct sensor_value val;
    int error_code = sensor_channel_get(onboard_led, SENSOR_CHAN_AMBIENT_TEMP, &val);
    LOG_INF("Get Channel. Error Code: %d", error_code);
    return 0;
}

/**
 * Onboard Led Sample Fetch
 */
int onboard_led_sample_fetch() {

    int error_code = sensor_sample_fetch(onboard_led);
    LOG_INF("Sample Fetch. Error Code: %d", error_code);
    return 0;
}

int main(void)
{
    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return -ENODEV;

    if (!device_is_ready(onboard_led)) return -ENODEV;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        // Onboard Led Channel Get
        onboard_led_channel_get();
        onboard_led_sample_fetch();
    }
    return 0;
}
