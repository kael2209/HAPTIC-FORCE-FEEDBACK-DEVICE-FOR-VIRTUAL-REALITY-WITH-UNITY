#include "stdint.h"

void adc_init(void);
void adc_enabled(void);
void adc_dma_init(uint16_t* analog_rx);
void adc_dma_enabled(void);
void adc_start(uint16_t *analog_rx);
