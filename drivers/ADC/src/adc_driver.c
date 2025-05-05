#include "C:/Users/Bane/Documents/Weather Station Workspace/WeatherStation/drivers/ADC/inc/adc_driver.h"

adc_oneshot_unit_handle_t adc1_handle;

adc_channel_t channel = ADC_CHANNEL_0;
int adc_raw;
int voltage;

// ADC oneshot driver initial configuration and channel configuration
void adc_init(adc_channel_t *channel)
{
    adc_oneshot_unit_init_cfg_t unitConfig =
    {
        .unit_id = ADC_UNIT_1, // ADC1
    };

    adc_oneshot_new_unit(&unitConfig, &adc1_handle);

    adc_oneshot_chan_cfg_t channelConfig =
    {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_oneshot_config_channel(adc1_handle, *channel, &channelConfig);
}