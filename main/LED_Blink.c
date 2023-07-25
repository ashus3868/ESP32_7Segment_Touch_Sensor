#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const int seven_seg_pins[7] = {GPIO_NUM_22, GPIO_NUM_21, GPIO_NUM_19, GPIO_NUM_18, GPIO_NUM_5, GPIO_NUM_4, GPIO_NUM_2};
const int numbers[10][7] = {{0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0}, 
{0, 0, 0, 0, 1, 1, 0}, {1, 0, 0, 1, 1, 0, 0}, {0, 1, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 0, 0}, 
{0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0}};

int count = 0;

void app_main(void)
{
    for (int x = 0; x < 7; x++)
    {
        gpio_set_direction(seven_seg_pins[x], GPIO_MODE_OUTPUT);
    }

    gpio_set_direction(GPIO_NUM_23, GPIO_MODE_INPUT);

    while (1)
    {
        if (gpio_get_level(GPIO_NUM_23))
        {
            if (count < 9)
            {
                count += 1;
            }
            else
            {
                count = 0;
            }
        }
        else
        {
        }

        for (int i = 0; i < 7; i++)
        {
            gpio_set_level(seven_seg_pins[i], numbers[count][i]);
        }
        vTaskDelay(30);
    }
}
