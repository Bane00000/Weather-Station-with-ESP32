#include <stdio.h>
#include "MQ135_Component.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    mq135_init();

    while(1)
    {
        mq135_read();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}