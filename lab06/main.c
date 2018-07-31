#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "usart.h"

//
//实验（六）PWM输出实验   


 int main(void)
 {	
	u16 led0pwmval=0;    
	u8 dir=1;	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
	uart_init(9600);
   	while(1)
	{
 		delay_ms(10);	 
		if(dir)
			led0pwmval++;
		else
			led0pwmval--;	 
 		if(led0pwmval>300)
			dir=0;
		if(led0pwmval==0){
			dir=1;
			printf("The light is off.\n");
			delay_ms(1000);
		}
		TIM_SetCompare1(TIM1,led0pwmval);
	} 
}
