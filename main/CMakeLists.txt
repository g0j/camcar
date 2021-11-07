
idf_component_register(SRCS "main.c" "leds.c" "wifi.c" "asyncserver.c"
                       INCLUDE_DIRS "."
                       REQUIRES "esp32-camera" "nvs_flash" "esp_eth" "esp_http_server" "ESPAsyncWebServer" "arduino-esp32")
