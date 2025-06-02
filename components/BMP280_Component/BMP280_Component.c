#include <stdio.h>
#include "BMP280_Component.h"

/*
I2C handles
*/
i2c_master_bus_handle_t bmp280_bus_handle;
i2c_master_dev_handle_t bmp280_dev_handle;

/*
Data commands
*/
uint8_t ctrl_meas = bmp280_ctrl_meas;
uint8_t disable_command = DISABLE_TEMPERATURE;

extern i2c_master_transmit_multi_buffer_info_t disable_temp[2] =
{
    {.write_buffer = &ctrl_meas, .buffer_size = ONE_BYTE},
    {.write_buffer = &disable_command, .buffer_size = ONE_BYTE},
};

/*
Initialize BMP280 sensor
*/
void bmp280_init(void)
{
    i2c_init(&bmp280_bus_handle, &bmp280_dev_handle, bmp280_address, GPIO_NUM_37, GPIO_NUM_38);
}

/*
Disabling temperature
*/
void bmp280_temperature_setup(void)
{
    i2c_send_multiple_data(bmp280_dev_handle, disable_temp, sizeof(disable_temp) / sizeof(i2c_master_transmit_multi_buffer_info_t));
}
