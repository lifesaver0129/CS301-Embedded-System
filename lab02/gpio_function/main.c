#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

void delay(void);

int main(){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);
	
	  delay_init();
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD,GPIO_Pin_2);

    while(1){
        
        GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			  GPIO_SetBits(GPIOD,GPIO_Pin_2);
        delay_ms(500);
        GPIO_SetBits(GPIOA,GPIO_Pin_8);
			  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			  delay_ms(500);
    }
}

void delay(void){
    int i = 0, j= 0;
    for(i = 0; i< 5000;i++)
        for(j=0;j<1000;j++);
}
