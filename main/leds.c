#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "leds.h"

void flashLED(int flashtime, gpio_num_t pinNumber)
{
  gpio_set_level(pinNumber, LED_OFF);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  gpio_set_level(pinNumber, LED_ON);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  gpio_set_level(pinNumber, LED_OFF);
}