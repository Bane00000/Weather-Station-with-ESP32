#include "I2C_driver_component.h"

/*
Addresses
*/
#define bmp280_press_xlsb   0xF9
#define bmp280_press_lsb    0xF8
#define bmp280_press_msb    0xF7
#define bmp280_config       0xF5
#define bmp280_ctrl_meas    0xF4
#define bmp280_status       0xF3
#define bmp280_reset        0xE0
#define bmp280_id           0xD0
#define bmp280_address      0x76 // If connected to VDDIO then slave address ix 0x77. With 0x76 it's connected to ground. 5.2
#define bmp280_setup        0x06 // Disable temperature, enable pressure and choose force mode
#define bmp280_calib        0x88

/*
BMP280 struct
*/
typedef struct
{
    i2c_master_bus_handle_t bmp280_bus_handle;
    i2c_master_dev_handle_t bmp280_dev_handle;
    uint8_t address;
    uint8_t ctrl_meas;
    uint8_t config;
    uint8_t calib;
    uint8_t setup_commands;
    gpio_num_t SCL;
    gpio_num_t SDA;
    i2c_master_transmit_multi_buffer_info_t transmit_setup[4];
    uint8_t calib_data[26];
    uint8_t config_reg_val;
    uint8_t raw_data[6];
    uint8_t temp_reg_address;
    int32_t adc_P;
    int32_t adc_T;
    int32_t t_fine;

    /*
    Calibration parameters
    */
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

} bmp280_t;

/*
Function declarations
*/
void bmp280_init(void);
void bmp280_prepare_transmit_setup(void);
void bmp280_config_regs(void);
void bmp280_start_measure(void);
void bmp280_compensation_parameters(void);
void bmp280_read_raw_data(void);
int32_t bmp280_compensate_T_int32(int32_t adc_T);
uint32_t bmp280_compensate_P_int64(int32_t adc_P);
