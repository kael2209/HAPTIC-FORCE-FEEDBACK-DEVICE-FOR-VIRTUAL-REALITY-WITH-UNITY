#include "main.h"

int main(void)
{
	usart_start();
	timer_encoder_start(encoder);
	pwm_start();
	adc_start(analog_rx);
	timer10_init();
	timer9_start();
	while(1)
	{
		__WFI();
	}
}
void TIM1_UP_TIM10_IRQHandler(void)
{
	TIM10->SR&=~(1<<0);
	
	convert_angles(encoder,angle_value);

	raw_current[0] = (850*((float)analog_rx[0]/4096.0*3.3 - vol_calib[0])/0.185);//1.584   // them fabs()
	raw_current[1] = (2050*((float)analog_rx[1]/4096.0*3.3 - vol_calib[1])/0.185);//1.639
	raw_current[2] = (1300*((float)analog_rx[2]/4096.0*3.3 - vol_calib[2])/0.185);//1.640

	current1_array[current_index] = raw_current[0];
	current2_array[current_index] = raw_current[1];
	current3_array[current_index] = raw_current[2];
	
	if (current_index == 99)
	{
		tim_flag=1;
		//printf("%d;%.3f\n",pwm[2],current_mA[1]);
		printf("%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",angle_value[0],angle_value[1],angle_value[2],current1_sum/100.0,current2_sum/100.0,current3_sum/100.0);
		
		current1_sum =0,current2_sum =0,current3_sum =0;
		current_index=0;
		for (int i=0;i<100;i++)
		{
			current1_sum+=current1_array[i];
			current2_sum+=current2_array[i];
			current3_sum+=current3_array[i];
		}
//		current_mA[0] =(pwm[0]==0)? 0:(current1_sum/500.0);
//		current_mA[1] =(pwm[2]==0)? 0:(current2_sum/500.0);
//		current_mA[2] =(pwm[4]==0)? 0:(current3_sum/500.0);
		
		/* TEST */
		current_mA[0] =fabs(current1_sum/100.0);
		current_mA[1] =fabs(current2_sum/100.0);
		current_mA[2] =fabs(current3_sum/100.0);
		//rx_current[0]=rx_current[1]=rx_current[2]=temp;
		//printf("%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",(float)rx_current[0],current_mA[0],(float)rx_current[1],current_mA[1],(float)rx_current[2],current_mA[2]);
		if (rx_current[0] >0) direction[0] = 1;
		else if (rx_current[0] <0) direction[0] = 0;
		else if (rx_current[0]==0) direction[0] = 10;
		
		if (rx_current[1] >0) direction[1] = 1;
		else if (rx_current[1]<0) direction[1] = 0;
		else if (rx_current[1]==0) direction[1] = 10;
		
		if (rx_current[2] >0) direction[2] = 1;
		else if (rx_current[2] <0) direction[2] = 0;
		else if (rx_current[2]==0) direction[2] = 10;

		if (direction[0] == 1)	// 0.004,4
		{
			pwm[0] = PID_Current1(fabs((float)rx_current[0]),current_mA[0],KP1,KI1,KD1,TS1,ALPHA1);
			pwm[1] =0;
		}
		else if (direction[0] == 0)	
		{
			pwm[1] = PID_Current1(fabs((float)rx_current[0]),current_mA[0],KP1,KI1,KD1,TS1,ALPHA1);
			pwm[0] =0;
		}
		else pwm[0]=pwm[1] = 0;
		
		if (direction[1] == 1)	
		{
			pwm[2] = PID_Current2(fabs((float)rx_current[1]),current_mA[1],KP2,KI2,KD2,TS2,ALPHA2);
			pwm[3] = 0;
		}
		else if (direction[1] == 0)									
		{
			pwm[3] = PID_Current2(fabs((float)rx_current[1]),current_mA[1],KP2,KI2,KD2,TS2,ALPHA2);
			pwm[2] =0;
		}
		else pwm[2] = pwm[3] = 0;
		
		if (direction[2] == 1)	
		{
			pwm[4] = PID_Current3(fabs((float)rx_current[2]),current_mA[2],KP3,KI3,KD3,TS3,ALPHA3);
			pwm[5] =0;
		}
		else if (direction[2] == 0)	
		{
			pwm[5] = PID_Current3(fabs((float)rx_current[2]),current_mA[2],KP3,KI3,KD3,TS3,ALPHA3);
			pwm[4] =0;
		}
		else pwm[4] = pwm[5] =0;

		pwm_set_all(pwm);	
	
	}
	else current_index++;
}

void USART2_IRQHandler(void)
{
	rx_buffer[rx_index] = USART2->DR;
	if (rx_buffer[rx_index] == '\n')
	{
		sscanf(rx_buffer,"%d;%d;%d\n",&rx_current[0],&rx_current[1],&rx_current[2]);
		rx_index=0;
		strcpy(rx_buffer,"");
	}
	else rx_index++;
}
