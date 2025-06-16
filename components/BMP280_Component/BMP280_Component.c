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
    bmp280.calib = bmp280_calib;
    bmp280.setup_commands = bmp280_setup;
    bmp280.temp_reg_address = bmp280_press_msb;
    bmp280.SCL = GPIO_NUM_37;
    bmp280.SDA = GPIO_NUM_38;

    i2c_init(&bmp280.bmp280_bus_handle, &bmp280.bmp280_dev_handle, bmp280.address, bmp280.SCL, bmp280.SDA);

    i2c_send_read_data(bmp280.bmp280_dev_handle, &bmp280.config, ONE_BYTE, &bmp280.config_reg_val, ONE_BYTE);

    bmp280.config_reg_val &= ~(0b111 << 2);  // Clear bits 4:2
    bmp280.config_reg_val |= (0 << 2);      // Set filter = 000 (OFF)

    bmp280_prepare_transmit_setup();
    bmp280_config_regs();
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

/*
Get calibration parameters for the compensation formula
*/
void bmp280_compensation_parameters(void)
{
    i2c_send_read_data(bmp280.bmp280_dev_handle, &bmp280.calib, ONE_BYTE, bmp280.calib_data, 26); // no stop condition

    bmp280.dig_T1 = (uint16_t)(bmp280.calib_data[1] << 8 | bmp280.calib_data[0]);
    bmp280.dig_T2 = (int16_t)(bmp280.calib_data[3] << 8 | bmp280.calib_data[2]);
    bmp280.dig_T3 = (int16_t)(bmp280.calib_data[5] << 8 | bmp280.calib_data[4]);
    bmp280.dig_P1 = (uint16_t)(bmp280.calib_data[7] << 8 | bmp280.calib_data[6]);
    bmp280.dig_P2 = (int16_t)(bmp280.calib_data[9] << 8 | bmp280.calib_data[8]);
    bmp280.dig_P3 = (int16_t)(bmp280.calib_data[11] << 8 | bmp280.calib_data[10]);
    bmp280.dig_P4 = (int16_t)(bmp280.calib_data[13] << 8 | bmp280.calib_data[12]);
    bmp280.dig_P5 = (int16_t)(bmp280.calib_data[15] << 8 | bmp280.calib_data[14]);
    bmp280.dig_P6 = (int16_t)(bmp280.calib_data[17] << 8 | bmp280.calib_data[16]);
    bmp280.dig_P7 = (int16_t)(bmp280.calib_data[19] << 8 | bmp280.calib_data[18]);
    bmp280.dig_P8 = (int16_t)(bmp280.calib_data[21] << 8 | bmp280.calib_data[20]);
    bmp280.dig_P9 = (int16_t)(bmp280.calib_data[23] << 8 | bmp280.calib_data[22]);
}

void bmp280_read_raw_data(void)
{
    i2c_send_read_data(bmp280.bmp280_dev_handle, &bmp280.temp_reg_address, ONE_BYTE, bmp280.raw_data, 6);

    bmp280.adc_P = ((int32_t)bmp280.raw_data[0] << 12) | ((int32_t)bmp280.raw_data[1] << 4) | (bmp280.raw_data[2] >> 4);
    bmp280.adc_T = ((int32_t)bmp280.raw_data[3] << 12) | ((int32_t)bmp280.raw_data[4] << 4) | (bmp280.raw_data[5] >> 4);
}

int32_t bmp280_compensate_T_int32(int32_t adc_T)
{
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)bmp280.dig_T1 << 1))) * ((int32_t)bmp280.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)bmp280.dig_T1)) * ((adc_T >> 4) - ((int32_t)bmp280.dig_T1))) >> 12) *
            ((int32_t)bmp280.dig_T3)) >> 14;
    bmp280.t_fine = var1 + var2;
    T = (bmp280.t_fine * 5 + 128) >> 8;  // Temperature in 0.01 °C

    return T;
}

uint32_t bmp280_compensate_P_int64(int32_t adc_P)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)bmp280.t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bmp280.dig_P6;
    var2 = var2 + ((var1 * (int64_t)bmp280.dig_P5) << 17);
    var2 = var2 + (((int64_t)bmp280.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)bmp280.dig_P3) >> 8) + ((var1 * (int64_t)bmp280.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)bmp280.dig_P1) >> 33;

    if (var1 == 0) return 0;  // avoid divide by zero

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = ((int64_t)bmp280.dig_P9 * (p >> 13) * (p >> 13)) >> 25;
    var2 = ((int64_t)bmp280.dig_P8 * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)bmp280.dig_P7) << 4);

    return (uint32_t)p;  // pressure in Pa (Pascal), Q24.8 format
}

void bmp280_start(void)
{
    bmp280_compensation_parameters();
    bmp280_read_raw_data();
    bmp280_compensate_T_int32(bmp280.adc_T);
    bmp280_compensate_P_int64(bmp280.adc_P);
}
