#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

//实验（四）串口实验   

 int main(void)
 {	
	u8 t;
	u8 len;	
	u16 times=0; 
 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
 
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{				
			LED0=1;
			len=USART_RX_STA&0x3fff;
			printf("\r\n你好，\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
			delay_ms(100);
			LED1=!LED1;
			delay_ms(100);
			LED1=!LED1;
		}else
		{
			times++;
			LED0=0;//常亮led
			delay_ms(10);   
		}
	}	 
}


