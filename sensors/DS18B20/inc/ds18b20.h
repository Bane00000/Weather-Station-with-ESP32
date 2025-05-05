#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define HIGH    1
#define LOW     0

/*
ROM Commands
*/
#define READ_ROM    0x33

esp_err_t ds18b20_init(gpio_num_t ONE_WIRE_BUS);
void write_time_slot(gpio_num_t ONE_WIRE_BUS, uint16_t rom_commands);


