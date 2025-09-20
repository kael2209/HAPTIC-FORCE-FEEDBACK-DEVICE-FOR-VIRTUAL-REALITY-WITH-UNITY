#include <stdint.h>


void convert_angles(int16_t* encoder_value, float* angle);
float convert_current(uint16_t adc_value, float voltage_calib, float *buffer, int *index, float *sum, int duty);
int PID_Current1(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha);
int PID_Current2(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha);
int PID_Current3(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha);

