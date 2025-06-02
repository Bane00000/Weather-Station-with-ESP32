#include "driver/i2c_master.h"

#define ONE_BYTE    1
#define TWO_BYTES   2
#define THREE_BYTES 3

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
void i2c_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle, uint8_t address,
                gpio_num_t scl_num, gpio_num_t sda_num);
void i2c_send_data(i2c_master_dev_handle_t dev_handle, const uint8_t *data, size_t length);
void i2c_send_multiple_data(i2c_master_dev_handle_t dev_handle, i2c_master_transmit_multi_buffer_info_t *buffer_info_array,
                            size_t array_size);
void i2c_read_data(i2c_master_dev_handle_t dev_handle, uint8_t *data, size_t length);
void i2c_send_read_data(i2c_master_dev_handle_t dev_handle,
                        const uint8_t* write_buffer, size_t write_size, uint8_t* read_buffer, size_t read_size);
void i2c_is_slave_connected(i2c_master_bus_handle_t bus_handle);