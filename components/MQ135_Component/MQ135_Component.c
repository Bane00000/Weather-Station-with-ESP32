#include <stdio.h>
#include "MQ135_Component.h"
#include "ADC_driver_component.h"

/*
Variable declarations
*/
adc_oneshot_unit_handle_t adc1_handle_mq135;

adc_channel_t channel_mq135 = ADC_CHANNEL_0;
int adc_raw_mq135;
int voltage_mq135;

adc_unit_t adc_unit_mq135 = ADC_UNIT_1;
adc_atten_t adc_atten_mq135 = ADC_ATTEN_DB_12;
adc_bitwidth_t adc_bitdiwth_mq135 = ADC_BITWIDTH_12;

/**
  * @brief  Initializes ADC for MQ135
  * @param  /
  * @retval void
  */
void mq135_init(void)
{
    adc_init(&channel_mq135, adc_unit_mq135, adc_atten_mq135, adc_bitdiwth_mq135, &adc1_handle_mq135);
}

/**
  * @brief  Reads data
  * @param  /
  * @retval void
  */
void mq135_read(void)
{
    adc_oneshot_read(adc1_handle_mq135, channel_mq135, &adc_raw_mq135);
    voltage_mq135 = adc_raw_mq135*3300/4095;
    printf("CHANNEL: %d\t RAW: %d\t mV: %d\n", channel_mq135, adc_raw_mq135, voltage_mq135);
}
