#include "driver/gpio.h"

#define LED_LAMP GPIO_NUM_4
#define LED_STATUS GPIO_NUM_33
#define LED_ON 1
#define LED_OFF 0

void initLeds();
void flashLED(int flashtime, gpio_num_t pinNumber);
void flashStatus(int flashtime);
void flashLamp(int flashtime);
void setLamp(int percent);
void flashLamp(int flashtime);
