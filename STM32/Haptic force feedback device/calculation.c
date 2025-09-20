#include "calculation.h"

void convert_angles(int16_t* encoder_value, float* angle)
{
	for (char i=0;i<3;i++)
	{
		*angle = *encoder_value*(360/800.0)/10.0-35;
		encoder_value++;
		angle++;
	}
}

float convert_current(uint16_t adc_value, float voltage_calib, float *buffer, int *index, float *sum, int duty)
{
	float raw_current = 2000*((float)adc_value / 4096.0 * 3.3 - voltage_calib) / 0.185;

	buffer[*index] = raw_current;
	*sum += raw_current;
	(*index)++;
	if (*index >= 500)
	{
			float average = *sum / 500.0;
			*index = 0;
			*sum = 0;
			return (duty == 0) ? 0 : average;
	}
	return -1; // giá tr? chua s?n sàng, v?n dang l?y m?u
}
int PID_Current1(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha)
{
	static float err_p=0, ui_p=0,udf_p=0;
	float err,up,ui,ud,udf;
	int uout=0;
	float u_unclamped;
	
	err = DesiredValue - CurrentValue;
	
	up = Kp*err;
	ui = ui_p + Ki*Ts*err;
	ud = Kd*(err - err_p)/Ts;
	udf = (1-alpha)*udf_p + alpha*ud;
	

	u_unclamped = up + ui_p + udf;

	if ((u_unclamped >= 100 && err > 0) || (u_unclamped <= 0 && err < 0)) {
			ui = ui_p;  
	} else {
			ui = ui_p + Ki * Ts * err;  
	}
	
	ui_p = ui;
	err_p = err;
	udf_p = udf;
	
	uout = (int)(up+ui+ud);
	if (uout>=100) uout=100;
	else if (uout<0) uout=0;
	return uout;
}

int PID_Current2(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha)
{
	static float err_p=0, ui_p=0,udf_p=0;
	float err,up,ui,ud,udf;
	int uout=0;
	float u_unclamped;
	
	err = DesiredValue - CurrentValue;
	
	up = Kp*err;
	ui = ui_p + Ki*Ts*err;
	ud = Kd*(err - err_p)/Ts;
	udf = (1-alpha)*udf_p + alpha*ud;
	

	u_unclamped = up + ui_p + udf;

	if ((u_unclamped >= 100 && err > 0) || (u_unclamped <= 0 && err < 0)) {
			ui = ui_p;  
	} else {
			ui = ui_p + Ki * Ts * err;  
	}
	
	ui_p = ui;
	err_p = err;
	udf_p = udf;
	
	uout = (int)(up+ui+ud);
	if (uout>=100) uout=100;
	else if (uout<0) uout=0;
	return uout;
}

int PID_Current3(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha)
{
	static float err_p=0, ui_p=0,udf_p=0;
	float err,up,ui,ud,udf;
	int uout=0;
	float u_unclamped;
	
	err = DesiredValue - CurrentValue;
	
	up = Kp*err;
	ui = ui_p + Ki*Ts*err;
	ud = Kd*(err - err_p)/Ts;
	udf = (1-alpha)*udf_p + alpha*ud;
	

	u_unclamped = up + ui_p + udf;

	if ((u_unclamped >= 100 && err > 0) || (u_unclamped <= 0 && err < 0)) {
			ui = ui_p;  
	} else {
			ui = ui_p + Ki * Ts * err;  
	}
	
	ui_p = ui;
	err_p = err;
	udf_p = udf;
	
	uout = (int)(up+ui+ud);
	if (uout>=100) uout=100;
	else if (uout<0) uout=0;
	return uout;
}

/*
int PID_Current2(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha)
{
	static float err_p=0, ui_p=0,udf_p=0;
	float err,up,ui,ud,udf;
	int uout=0;
	
	err = DesiredValue - CurrentValue;
	
	up = Kp*err;
	ui = ui_p + Ki*Ts*err;
	ud = Kd*(err - err_p)/Ts;
	udf = (1-alpha)*udf_p + alpha*ud;
	
	ui_p = ui;
	err_p = err;
	udf_p = udf;
	
	uout = (int)(up+ui+ud);
	if (uout>=100) uout=100;
	else if (uout<0) uout=0;
	return uout;
}
int PID_Current3(float DesiredValue, float CurrentValue,float Kp,float Ki,float Kd,float Ts,float alpha)
{
	static float err_p=0, ui_p=0,udf_p=0;
	float err,up,ui,ud,udf;
	int uout=0;
	
	err = DesiredValue - CurrentValue;
	
	up = Kp*err;
	ui = ui_p + Ki*Ts*err;
	ud = Kd*(err - err_p)/Ts;
	udf = (1-alpha)*udf_p + alpha*ud;
	
	ui_p = ui;
	err_p = err;
	udf_p = udf;
	
	uout = (int)(up+ui+ud);
	if (uout>=100) uout=100;
	else if (uout<0) uout=0;
	return uout;
}
*/

