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
    uint8_t setup_commands;
    gpio_num_t SCL;
    gpio_num_t SDA;
    i2c_master_transmit_multi_buffer_info_t transmit_setup[4];
    uint8_t config_reg_val;

} bmp280_t;

/*
Function declarations
*/
void bmp280_init(void);
void bmp280_prepare_transmit_setup(void);
void bmp280_config_regs(void);
void bmp280_start_measure(void);
