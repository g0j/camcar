
idf_component_register(SRCS "main.c" "leds.c" "wifi.c"
                       INCLUDE_DIRS "."
                       REQUIRES "esp32-camera" "nvs_flash")
