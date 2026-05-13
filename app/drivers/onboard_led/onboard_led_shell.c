// Zephyr Includes
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

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

    sensor_sample_fetch(onboard_led_dev);
    shell_info(sh, "Sensor Sample Fetch executed");
    return 0;
}

/**
 * @brief Subcommand Read
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv) {

    struct sensor_value val;
    sensor_channel_get(onboard_led_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_fprintf(sh, SHELL_INFO, "Sensor Channel Get. Temperature: %d", val.val1);
    return 0;
}

/**
 * @brief SubCommand Info
 * @param sh Shell Pointer
 * @param argc Argument Counter
 * @param argv Argument Values
 */
static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv) {

    shell_fprintf(sh, SHELL_INFO, "Device Name: %s | Ready State: %s\n", "NAME", "STATE");
    return 0;
}

// Register Subcommands
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd, 
    SHELL_CMD(fetch, NULL, "Sensor Fetch", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Sensor Read", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Sensor Info", cmd_sensor_info),
    SHELL_SUBCMD_SET_END
);

// Register Command "sensor"
SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor commands", NULL);
