#ifndef ONBOARD_LED_DRIVER_H_
#define ONBOARD_LED_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define Data Struct
 */
struct onboard_led_driver_data {

    int blinks_count;
};

/**
 * @brief Onboard Led Set Blink Counter
 * @param dev Device Pointer
 * @param count_value Count Value
 */
void onboard_led_set_blink_counter(const struct device *dev, int count_value);

#ifdef __cplusplus
}
#endif

#endif // ONBOARD_LED_DRIVER_H_
