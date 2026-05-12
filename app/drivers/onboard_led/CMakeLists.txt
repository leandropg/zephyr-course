if(CONFIG_ONBOARD_LED_DRIVER)
    target_sources(app PRIVATE onboard_led_driver.c)
endif()