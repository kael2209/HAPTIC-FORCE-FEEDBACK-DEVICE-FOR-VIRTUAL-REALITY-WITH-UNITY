#include <stdint.h>

/* Encoder variable */
extern int16_t encoder[3];

/* USART variables */ 
extern char rx_buffer[15],rx;
extern int rx_index,rx_current[3];

/* HBridge variables */
extern uint8_t pwm[6];
extern uint8_t direction[3];

/* Convert_angles variables */
extern float angle_value[3];

/* ADC variables */
extern uint16_t analog_rx[3];

extern int current_index;
extern float raw_current[3];
extern float current1_array[500],current2_array[500],current3_array[500];
extern float current1_sum,current2_sum,current3_sum;
extern float current_mA[3];
extern float vol_calib[3];

extern int tim_flag;
extern int usart_flag;

extern float DesiredCurrent1;
extern float DesiredCurrent2;
extern float DesiredCurrent3;

extern float KP1,KI1,KD1,TS1,ALPHA1;		/* MOTOR 1*/
extern float KP2,KI2,KD2,TS2,ALPHA2;		/* MOTOR 2*/
extern float KP3,KI3,KD3,TS3,ALPHA3;  	/* MOTOR 3*/


extern float array1[2000],array2[2000],array3[2000];
extern float sum[3];
//int index=0;
extern float avg_current[3];

extern float tem_current[3];

extern int analog_array[1000], analog_index,analog_sum;
extern float analog_average;
extern int analog_array_1[1000], analog_index_1,analog_sum_1;
extern float analog_average_1;
extern int analog_array_2[1000], analog_index_2,analog_sum_2;
extern float analog_average_2;