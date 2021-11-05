
idf_component_register(SRCS "main.c" "leds.c" "wifi.c" "server.c"
                       INCLUDE_DIRS "."
                       REQUIRES "esp32-camera" "nvs_flash" "esp_eth" "esp_http_server")
