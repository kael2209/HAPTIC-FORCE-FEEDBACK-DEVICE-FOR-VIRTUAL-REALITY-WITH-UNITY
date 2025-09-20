#include <stdint.h>

void timer1_pwm_init(void);
void timer3_pwm_init(void);
void pwm_start(void);

void pwm_channel1_set(uint8_t duty1);
void pwm_channel2_set(uint8_t duty2);
void pwm_channel3_set(uint8_t duty3);
void pwm_channel4_set(uint8_t duty4);
void pwm_channel5_set(uint8_t duty5);
void pwm_channel6_set(uint8_t duty6);

void pwm_set_all(uint8_t duty[6]);