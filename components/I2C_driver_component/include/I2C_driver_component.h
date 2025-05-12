#include "driver/i2c_master.h"

// SCL - GPIO4
// SDA - GPIO5

/*
Extern Declarations
*/
extern i2c_master_bus_config_t i2c_bus_config;
extern i2c_master_bus_handle_t i2c_bus_handle;

extern i2c_device_config_t i2c_dev_config;
extern i2c_master_dev_handle_t i2c_dev_handle;

/*
Function Declarations
*/
void i2c_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle);
void i2c_send_data(i2c_master_dev_handle_t *dev_handle, const uint8_t *data, size_t length);
void i2c_read_data(i2c_master_dev_handle_t dev_handle, uint8_t *data, size_t length);
void i2c_send_read_data(void); // TODO
esp_err_t i2c_is_slave_connected(i2c_master_bus_handle_t bus_handle);