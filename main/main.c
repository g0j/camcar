#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_camera.h"

#include <esp_http_server.h>

#include "leds.h"
#include "wifi.h"
#include "server.h"
#include "camera.h"


httpd_handle_t front_httpd = NULL;

void initMisc()
{
    //Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

void initCamera()
{
    ESP_ERROR_CHECK(esp_camera_init(&camera_config));
    ESP_LOGE(CAMERA_TAG, "Camera Initialized");
}

void initWifi()
{
    ESP_LOGI(WIFI_TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();
}

void initServer()
{
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &front_httpd));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &front_httpd));

    front_httpd = start_webserver();
    ESP_LOGI(HTTP_TAG, "Web server initialized");

}

void app_main()
{
    initLeds();
    initMisc();
    initWifi();
    initCamera();
    initServer();
}
