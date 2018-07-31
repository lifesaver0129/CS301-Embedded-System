#include "sys.h"
#include "delay.h" 
#include "lcd.h"


int main(void){	 
	SCB->VTOR = SRAM_BASE | 0x1000;       
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LCD_init();
	while(1){
		POINT_COLOR=BLUE;
        LCD_ShowString(60,50,200,16,16,"Yuxing Hu 11510225");
        delay_ms(1000);
		}
	}	 
