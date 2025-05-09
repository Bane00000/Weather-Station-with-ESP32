#include "driver/i2c_master.h"

// SCL - GPIO4
// SDA - GPIO5

/*
Extern Declarations
*/
extern i2c_master_bus_config_t i2c_config;
extern i2c_master_bus_handle_t i2c_bus_handle;

extern i2c_device_config_t i2c_dev_config;
extern i2c_master_dev_handle_t i2c_dev_handle;

void i2c_init(void);
