#include <stdio.h>
#include "MQ135_Component.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Si7021_Component.h"
#include "BMP280_Component.h"

/******************************************************************************/
/*!                       Variables                                           */
BaseType_t status;

/******************************************************************************/
/*!                       Function declarations                               */
void mq135_task(void* pvParameters);
void si7021_task(void* pvParameters);
void bmp280_task(void* pvParameters);

/******************************************************************************/
/*!                       MAIN function                                       */
void app_main(void)
{
    /*status = xTaskCreate(mq135_task, "MQ135", 2048, NULL, 2, NULL);
    configASSERT(status == pdPASS);*/

    /*status = xTaskCreate(si7021_task, "SI7021", 2048, NULL, 2, NULL);
    configASSERT(status == pdPASS);*/

    /*status = xTaskCreate(bmp280_task, "BMP280", 2048, NULL, 2, NULL);
    configASSERT(status == pdPASS);*/

    bmp280_init();

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(100000));
    }
}

/******************************************************************************/
/*!                       Function definitions                               */
void mq135_task(void* pvParameters)
{
    mq135_init();

    while(1)
    {
        mq135_read();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void si7021_task(void* pvParameters)
{
    si7021_init();

    while(1)
    {
        si7021_read_hold_mode();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void bmp280_task(void* pvParameters)
{
    bmp280_init();
    bmp280_config_regs();

    while(1)
    {

    }
}
