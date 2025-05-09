#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"

const static char *TAG = "ADC";

void adc_init(adc_channel_t *channel, adc_unit_t adc_unit, adc_atten_t adc_atten, adc_bitwidth_t adc_bitdiwth, adc_oneshot_unit_handle_t *adc_handle);