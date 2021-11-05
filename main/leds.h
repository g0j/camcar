#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_4
#define LED_LAMP GPIO_NUM_33
#define LED_ON 1
#define LED_OFF 0

void flashLED(int flashtime, gpio_num_t pinNumber);