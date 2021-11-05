#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "leds.h"

void task_lamp(void *param);

void app_main(void)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_pad_select_gpio(LED_LAMP);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_LAMP, GPIO_MODE_OUTPUT);

    xTaskCreate(task_lamp, "task_lamp", 1024 * 2, NULL, 3, NULL);
}

void task_lamp(void *param)
{
    while (1)
    {
        flashLED(250,LED_PIN);
    }

    vTaskDelete(NULL);
}
