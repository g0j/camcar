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


static httpd_handle_t server = NULL;

void init_misc()
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

void init_camera()
{
    ESP_ERROR_CHECK(esp_camera_init(&camera_config));
    ESP_LOGE(CAMERA_TAG, "Camera Initialized");
}

void init_wifi()
{
    ESP_LOGI(WIFI_TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();
}

void init_server()
{
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

    /* Start the server for the first time */
    server = start_webserver();
    ESP_LOGI(HTTP_TAG, "ESP_WIFI_MODE_STA");

}

void app_main()
{
    gpio_pad_select_gpio(LED_LAMP);
    gpio_set_direction(LED_LAMP, GPIO_MODE_OUTPUT);

    init_misc();
    init_wifi();
    init_server();
    init_camera();

    camera_fb_t *pic;
    while (1)
    {
        ESP_LOGI(CAMERA_TAG, "Taking picture...");
        gpio_set_level(LED_LAMP, LED_ON);
        vTaskDelay(500 / portTICK_RATE_MS);
        pic = esp_camera_fb_get();

        // use pic->buf to access the image
        ESP_LOGI(CAMERA_TAG, "Picture taken! Its size was: %zu bytes", pic->len);
        esp_camera_fb_return(pic);
        gpio_set_level(LED_LAMP, LED_OFF);

        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}
