#include <stdio.h>
#include "I2C_driver_component.h"
#include "Si7021_Component.h"

void i2c_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle,
                uint8_t address, gpio_num_t scl_num, gpio_num_t sda_num)
{
    i2c_master_bus_config_t i2c_bus_config =
    {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = -1, // Auto-selecting
        .scl_io_num = scl_num,
        .sda_io_num = sda_num,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, bus_handle));

    i2c_device_config_t i2c_dev_config =
    {
        .device_address = address,
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .scl_speed_hz = 100000,
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &i2c_dev_config, dev_handle));
}

void i2c_send_data(i2c_master_dev_handle_t dev_handle, const uint8_t *data, size_t length)
{
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data, length, -1));
}

void i2c_read_data(i2c_master_dev_handle_t dev_handle, uint8_t *data, size_t length)
{
    ESP_ERROR_CHECK(i2c_master_receive(dev_handle, data, length, -1));
}

void i2c_is_slave_connected(i2c_master_bus_handle_t bus_handle)
{
    ESP_ERROR_CHECK(i2c_master_probe(bus_handle, si7021_address, -1));
}

void i2c_send_read_data(i2c_master_dev_handle_t dev_handle,
                        const uint8_t* write_buffer, size_t write_size, uint8_t* read_buffer, size_t read_size)
{
    ESP_ERROR_CHECK(i2c_master_transmit_receive(dev_handle, write_buffer, write_size, read_buffer, read_size, -1));
}
