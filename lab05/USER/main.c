#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h" 
//
//实验（五）外部中断实验   
//
 int main(void)
 {	
 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
 	EXTIX_Init();		//外部中断初始化
  LED0=0;				//点亮LED
	while(1)
	{	    
		printf("OK\n");	
		delay_ms(3000);	  
	} 
}


