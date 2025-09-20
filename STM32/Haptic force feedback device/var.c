#include "var.h"
#include <stdint.h>

int16_t encoder[3];

char rx_buffer[15],rx;
int rx_index=0,rx_current[3];

uint8_t pwm[6] = {0,0,0,0,0,0};

float angle_value[3] = {-35,-35,-35};

uint16_t analog_rx[3];

int current_index=0;
float raw_current[3]={0,0,0};
float current1_array[500],current2_array[500],current3_array[500];
float current1_sum=0,current2_sum=0,current3_sum=0;
float current_mA[3] = {0,0,0};

//float vol_calib[3] = {2.55 ,2.5355 ,2.535};
//float vol_calib[3] = {2.53699994, 2.52749991 ,2.52099991};
float vol_calib[3] = {0.0,0.0,0.0};

int tim_flag=0;
int usart_flag=0;

float DesiredCurrent1=0;
float DesiredCurrent2=0;
float DesiredCurrent3=0;

uint8_t direction[3] = {10,10,10};

float KP1=0.011		,KI1=10.66		,KD1=0	,TS1=0.001	,ALPHA1=0;			/* MOTOR 1*/
float KP2=0.017		,KI2=8.527		,KD2=0	,TS2=0.001	,ALPHA2=0;			/* MOTOR 2*/
float KP3=0.011		,KI3=10.526		,KD3=0	,TS3=0.001	,ALPHA3=0;  		/* MOTOR 3*/

//float KP1=0.0414		,KI1=41.44		,KD1=0	,TS1=0.001	,ALPHA1=0;			/* MOTOR 1*/
/*Calib Tool*/
float array1[2000],array2[2000],array3[2000];
float sum[3]={0.0,0.0,0.0};
//int index=0;
float avg_current[3];

float tem_current[3]={0.0,0.0,0.0};

int analog_array[1000], analog_index=0,analog_sum=0;
float analog_average=0;
int analog_array_1[1000], analog_index_1=0,analog_sum_1=0;
float analog_average_1=0;
int analog_array_2[1000], analog_index_2=0,analog_sum_2=0;
float analog_average_2=0;