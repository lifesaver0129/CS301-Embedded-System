#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"

int main(void){
	u8 t;
	u8 len;	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	uart_init(9600);
	LED_Init();
	EXTIX_Init();  
  LED0=0; 
	while(1){
		if(USART_RX_STA&0x8000)
		{				
			len=USART_RX_STA&0x3fff;
			printf("\r\nÄãºÃ,\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);
			}
			printf("\r\n\r\n");
			USART_RX_STA=0;
		}else
		{
			printf("OK\n");
			delay_ms(3000);
		}
		
	
	} 
}
