#include "ds18b20.h"

/*
The protocol for accessing the DS18B20 via the 1-Wire port is as follows:
  Initialization
  ROM Function Command
  Memory Function Command
  Transaction/Data
*/

/*
    Initialization sequence
The initialization sequence required to begin any communication with the DS18B20 is shown in
Figure 11.  A reset pulse followed by a presence pulse indicates the DS18B20 is ready to send or receive
data given the correct ROM command and memory function command. PAGE 14 I/O SIGNALING
*/

/*
PAGE 11 of datasheet for ROM commands
*/

/*
To initiate a temperature measurement 
and A-to-D conversion, the master must issue a Convert 
T [44h] command. Following the conversion, the resulting 
thermal data is stored in the 2-byte temperature register 
in the scratchpad memory and the DS18B20 returns to its 
idle state. If the DS18B20 is powered by an external sup
ply, the master can issue “read time slots” (see the 1-Wire 
Bus System section) after the Convert T command and 
the DS18B20 will respond by transmitting 0 while the tem
perature conversion is in progress and 1 when the con
version is done.

PAGE 5 of datasheet
*/

/*
The tempera
ture data is stored as a 16-bit sign-extended two’s comple
ment number in the temperature register.

PAGE 6 of datasheet
*/

/*
In some situations the bus master may not know whether 
the DS18B20s on the bus are parasite powered or pow
ered by external supplies. The master needs this informa
tion to determine if the strong bus pullup should be used 
during temperature conversions. To get this information, 
the master can issue a Skip ROM [CCh] command fol
lowed by a Read Power Supply [B4h] command followed 
by a “read time slot”. During the read time slot, parasite 
powered DS18B20s will pull the bus low, and externally 
powered DS18B20s will let the bus remain high. If the 
bus is pulled low, the master knows that it must supply 
the strong pullup on the 1-Wire bus during temperature 
conversions.

PAGE 7 of datasheet
*/

/*
trigger registers (TH and TL) and configuration register. 
Note that if the DS18B20 alarm function is not used, 
the TH and TL registers can serve as general-purpose 
memory.

PAGE 8 of datasheet
*/

/*
When there is only one slave on the bus, the sys
tem is referred to as a “single-drop” system; the system is 
“multidrop” if there are multiple slaves on the bus.

5k ohm resistor is needed

PAGE 10 of datasheet
*/

/*
Initialization Sequence
*/
esp_err_t ds18b20_init(gpio_num_t ONE_WIRE_BUS)
{
    gpio_set_direction(ONE_WIRE_BUS, GPIO_MODE_OUTPUT);
    gpio_set_level(ONE_WIRE_BUS, LOW);
    esp_rom_delay_us(480);

    gpio_set_direction(ONE_WIRE_BUS, GPIO_MODE_INPUT);
    esp_rom_delay_us(480);

    if(gpio_get_level(ONE_WIRE_BUS))
    {
        return ESP_FAIL;
    }
    else
    {
        return ESP_OK;
    }
}

/*
ROM Function Command
*/
void write_time_slot(gpio_num_t ONE_WIRE_BUS, uint16_t rom_commands)
{
    switch (rom_commands)
    {
    case READ_ROM:
        /* code */
        gpio_set_direction(ONE_WIRE_BUS, LOW);
        esp_rom_delay_us(120);
        gpio_set_direction(ONE_WIRE_BUS, HIGH);
        esp_rom_delay_us(120);
        gpio_set_direction(ONE_WIRE_BUS, LOW);
        esp_rom_delay_us(120);
        gpio_set_direction(ONE_WIRE_BUS, HIGH);
        esp_rom_delay_us(120);
        break;
    
    default:
        break;
    }
}