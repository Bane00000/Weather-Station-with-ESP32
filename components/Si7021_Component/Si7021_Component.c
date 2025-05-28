#include <stdio.h>
#include "Si7021_Component.h"
#include "freertos/FreeRTOS.h"

i2c_master_bus_handle_t si7021_i2c_bus_handle;
i2c_master_dev_handle_t si7021_i2c_dev_handle;

uint8_t si7021_humidity[3];
const uint8_t si7021_measure = si7021_measure_humidity_hold_master_mode;
const uint8_t si7021_measure_no_hold_master_mode = si7021_measure_humidity_no_hold_master_mode;

void si7021_init(void)
{
    i2c_init(&si7021_i2c_bus_handle, &si7021_i2c_dev_handle, si7021_address, GPIO_NUM_5, GPIO_NUM_6);
}

void si7021_read_hold_mode(void)
{
    i2c_send_data(si7021_i2c_dev_handle, &si7021_measure, ONE_BYTE);
    vTaskDelay(pdMS_TO_TICKS(25));
    i2c_read_data(si7021_i2c_dev_handle, si7021_humidity, THREE_BYTES);

    uint8_t calculated_crc = si7021_crc8(si7021_humidity, TWO_BYTES);
    if (calculated_crc != si7021_humidity[2])
        {
            printf("CRC error: data corrupted!\n");
            return;
        }

    float humidity = si7021_convert_humidity(si7021_humidity[0], si7021_humidity[1]);
    printf("Humidity: %.2f %%RH\n", humidity);
}

float si7021_convert_humidity(uint8_t msb, uint8_t lsb)
{
    uint16_t raw_humidity = ((uint16_t)msb << 8) | lsb;

    float humidity = ((125.0f * raw_humidity) / 65536.0f) - 6.0f;

    return humidity;
}

uint8_t si7021_crc8(const uint8_t *data, uint8_t length)
{
    uint8_t crc = 0x00;

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;

            crc &= 0xFF;
        }
    }

    return crc;
}
