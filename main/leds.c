#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "esp_attr.h"
#include "leds.h"

void initLeds()
{
    gpio_pad_select_gpio(LED_STATUS);
    gpio_set_direction(LED_STATUS, GPIO_MODE_OUTPUT);

    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, LED_LAMP);

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    //frequency = 500Hz,
    pwm_config.cmpr_a = 0;          //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;          //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
}

void flashLED(int flashtime, gpio_num_t pinNumber)
{
  gpio_set_level(pinNumber, LED_OFF);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  gpio_set_level(pinNumber, LED_ON);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  gpio_set_level(pinNumber, LED_OFF);
}

void flashStatus(int flashtime)
{
  flashLED(flashtime,LED_STATUS);
}

void setLamp(int percent)
{
  if (percent==0){
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
    return;
  }

  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, percent);
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
}

void flashLamp(int flashtime)
{
  setLamp(0);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  setLamp(100);
  vTaskDelay(flashtime / portTICK_PERIOD_MS);

  setLamp(0);
}
