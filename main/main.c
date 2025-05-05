#include <stdio.h>
#include "C:/Users/Bane/Documents/Weather Station Workspace/WeatherStation/drivers/ADC/inc/adc_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    adc_init(&channel);

    while(1)
    {
        adc_oneshot_read(adc1_handle, channel, &adc_raw);
        voltage = adc_raw*3300/4095;
        printf("CHANNEL: %d\t RAW: %d\t mV: %d\n", channel, adc_raw, voltage);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}