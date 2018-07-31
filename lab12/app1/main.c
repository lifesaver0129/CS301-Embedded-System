#include "sys.h"
#include "usart.h"
#include "delay.h"  

int main(void){	 
	SCB->VTOR = FLASH_BASE | 0x10000;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	while(1){
		printf("Yuxing Hu 11510225\r\n\r\n");
		delay_ms(1000);
		}
	}	 
