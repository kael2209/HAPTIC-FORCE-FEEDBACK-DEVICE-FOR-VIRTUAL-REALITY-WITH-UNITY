#include <stdint.h>

void timer5_encoder_init(void);
void timer5_encoder_dma_init(int16_t* counter);

void timer2_encoder_init(void);
void timer2_encoder_dma_init(int16_t* counter2);

void timer4_encoder_init(void);
void timer4_encoder_dma_init(int16_t* counter3);

void timer_encoder_start(int16_t counter[3]);
