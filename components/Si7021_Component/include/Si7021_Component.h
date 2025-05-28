#include "I2C_driver_component.h"

/*
Si7021 Commands and Address
*/
#define si7021_address                              (0x40)
#define si7021_measure_humidity_hold_master_mode    (0xE5)
#define si7021_measure_humidity_no_hold_master_mode (0xF5)
#define si7021_reset                                (0xFE)

extern const uint8_t si7021_measure;

extern i2c_master_bus_handle_t si7021_i2c_bus_handle;
extern i2c_master_dev_handle_t si7021_i2c_dev_handle;

extern uint8_t si7021_humidity[3];

void si7021_init(void);
void si7021_read_hold_mode(void);
float si7021_convert_humidity(uint8_t msb, uint8_t lsb);
uint8_t si7021_crc8(const uint8_t *data, uint8_t length);