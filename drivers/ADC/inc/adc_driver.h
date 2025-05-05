#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

const static char *TAG = "ADC";

extern adc_oneshot_unit_handle_t adc1_handle;

extern adc_channel_t channel;
extern int adc_raw;
extern int voltage;

void adc_init(adc_channel_t *channel);