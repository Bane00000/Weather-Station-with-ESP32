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
#define DISABLE_TEMPERATURE 0x1F

/*
I2C handles
*/
extern i2c_master_bus_handle_t bmp280_bus_handle;
extern i2c_master_dev_handle_t bmp280_dev_handle;

/*
Data commands
*/
extern i2c_master_transmit_multi_buffer_info_t disable_temp[2];

extern uint8_t ctrl_meas;
extern uint8_t disable_command;

/*
Function declarations
*/
void bmp280_init(void);
void bmp280_temperature_setup(void);
void bmp280_pressure_setup(void);
