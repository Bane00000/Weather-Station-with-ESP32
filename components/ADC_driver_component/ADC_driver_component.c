//#include <stdio.h>
#include "ADC_driver_component.h"

// ADC oneshot driver initial configuration and channel configuration

void adc_init(adc_channel_t *channel, adc_unit_t adc_unit, adc_atten_t adc_atten, adc_bitwidth_t adc_bitdiwth, adc_oneshot_unit_handle_t *adc_handle)
{
    adc_oneshot_unit_init_cfg_t unitConfig =
    {
        .unit_id = adc_unit,
    };

    adc_oneshot_new_unit(&unitConfig, adc_handle);

    adc_oneshot_chan_cfg_t channelConfig =
    {
        .atten = adc_atten,
        .bitwidth = adc_bitdiwth,
    };

    adc_oneshot_config_channel(*adc_handle, *channel, &channelConfig);
}