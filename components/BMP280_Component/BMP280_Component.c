#include <stdio.h>
#include "BMP280_Component.h"

static bmp280_t bmp280;

/*
Initialize BMP280 sensor
*/
void bmp280_init(void)
{
    bmp280.address = bmp280_address;
    bmp280.ctrl_meas = bmp280_ctrl_meas;
    bmp280.config = bmp280_config;
    bmp280.setup_commands = bmp280_setup;
    bmp280.SCL = GPIO_NUM_37;
    bmp280.SDA = GPIO_NUM_38;

    i2c_init(&bmp280.bmp280_bus_handle, &bmp280.bmp280_dev_handle, bmp280.address, bmp280.SCL, bmp280.SDA);

    i2c_send_data(bmp280.bmp280_dev_handle, &bmp280.config, ONE_BYTE);
    i2c_read_data(bmp280.bmp280_dev_handle, &bmp280.config_reg_val, ONE_BYTE);

    bmp280.config_reg_val &= ~(0b111 << 2);  // Clear bits 4:2
    bmp280.config_reg_val |= (0 << 2);      // Set filter = 000 (OFF)

    bmp280_prepare_transmit_setup();
}

/*
Disabling temperature, enabling pressure and choosing normal mode
*/
void bmp280_config_regs(void)
{
    i2c_send_multiple_data(bmp280.bmp280_dev_handle, bmp280.transmit_setup,
                        sizeof(bmp280.transmit_setup) / sizeof(i2c_master_transmit_multi_buffer_info_t));
}

/*
After configuring all the registers of BMP280, use this function to start measuring pressure
*/
void bmp280_start_measure(void)
{
    i2c_send_multiple_data(bmp280.bmp280_dev_handle, bmp280.transmit_setup, TWO_BYTES);
}

void bmp280_prepare_transmit_setup(void)
{
    bmp280.transmit_setup[0].write_buffer = &bmp280.ctrl_meas;
    bmp280.transmit_setup[0].buffer_size = ONE_BYTE;

    bmp280.transmit_setup[1].write_buffer = &bmp280.setup_commands;
    bmp280.transmit_setup[1].buffer_size = ONE_BYTE;

    bmp280.transmit_setup[2].write_buffer = &bmp280.config;
    bmp280.transmit_setup[2].buffer_size = ONE_BYTE;

    bmp280.transmit_setup[3].write_buffer = &bmp280.config_reg_val;
    bmp280.transmit_setup[3].buffer_size = ONE_BYTE;
}
