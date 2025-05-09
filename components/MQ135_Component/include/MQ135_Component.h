#include "esp_adc/adc_oneshot.h"

/*
    Variable declarations
*/
extern adc_oneshot_unit_handle_t adc1_handle_mq135;

extern adc_channel_t channel_mq135;
extern int adc_raw_mq135;
extern int voltage_mq135;

extern adc_unit_t adc_unit_mq135;
extern adc_atten_t adc_atten_mq135;
extern adc_bitwidth_t adc_bitdiwth_mq135;

/*
    Function declarations
*/
void mq135_init(void);

void mq135_read(void);
