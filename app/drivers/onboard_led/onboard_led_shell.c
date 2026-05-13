// Zephyr Includes
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

// Sensor Include
#include "onboard_led_driver.h"

/**
 * @brief Sensor Led through Sensor API
 */
static const struct device *onboard_led_dev = DEVICE_DT_GET(DT_NODELABEL(onboard_led1));

/**
 * @brief SubCommand Fetch
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv) {

    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    
    // Obtain Onboard Led Driver data
    struct onboard_led_driver_data *data = onboard_led_dev->data;

    sensor_sample_fetch(onboard_led_dev);
    shell_fprintf(sh, SHELL_INFO, "Blink Counter = %d\n", data->blinks_count);
    return 0;
}

/**
 * @brief Subcommand Read
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv) {

    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    
    struct sensor_value val;
    sensor_channel_get(onboard_led_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_fprintf(sh, SHELL_INFO, "Sensor Channel Get. Temperature: %d\n", val.val1);
    return 0;
}

/**
 * @brief SubCommand Info
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv) {

    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_fprintf(sh, SHELL_INFO, "Device Name: %s | Ready State: %d\n", onboard_led_dev->name, device_is_ready(onboard_led_dev));
    return 0;
}

/**
 * @brief SubCommand Set Value
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_set_value(const struct shell *sh, size_t argc, char **argv) {

    // Obtain value to set
    int error_code;
    long value_received = shell_strtol(argv[1], 10, &error_code);

    // Check if the argument
    if (value_received < 0) {

        shell_error(sh, "The value to set must be great than 0");
        return -EINVAL;
    
    } else if (value_received > 200) {

        shell_error(sh, "The value to set must be less than 200");
        return -EINVAL;
    }

    // Cast value to set
    uint8_t value_set = (uint8_t)value_received;
    shell_fprintf(sh, SHELL_INFO, "Value Received: %d\n", value_set);

    // Set Blink Counter Value
    onboard_led_set_blink_counter(onboard_led_dev, value_set);
    return 0;
}

// Register Subcommands
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd, 
    SHELL_CMD(fetch, NULL, "Sensor Fetch", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Sensor Read", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Sensor Info", cmd_sensor_info),
    SHELL_CMD_ARG(set, NULL, "Sensor Set Value", cmd_sensor_set_value, 2, 0),
    SHELL_SUBCMD_SET_END
);

// Register Command "sensor"
SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor commands", NULL);
