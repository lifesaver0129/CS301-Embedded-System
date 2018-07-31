#include "led.h"
#include "delay.h"
#include "sys.h"
#include "includes.h"
#include "usart.h"
 

//START 任务
//设置任务优先级
#define START_TASK_PRIO                 10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE                  64
//任务堆栈  
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);   

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO                  7 
//设置任务堆栈大小
#define LED0_STK_SIZE                   64
//任务堆栈  
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO                  6 
//设置任务堆栈大小
#define LED1_STK_SIZE                   64
//任务堆栈
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);


int main(void)
{
    delay_init();               //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组 2 
    LED_Init();           //初始化与 LED 连接的硬件接口
    uart_init(9600);
		OSInit();
    OSTaskCreate(start_task,(void *)0,(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO);
    OSStart();
}


//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
    pdata = pdata; 
    OS_ENTER_CRITICAL();            //进入临界区(无法被中断打断)    
    OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);                         
    OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);                     
    OSTaskSuspend(START_TASK_PRIO); //挂起起始任务.
    OS_EXIT_CRITICAL();             //退出临界区(可以被中断打断)
}

//LED0任务
void led0_task(void *pdata)
{       
    while(1)
    {
        LED0=0;
        delay_ms(500);
        LED0=1;
        delay_ms(500);
    };
}

//LED1任务
void led1_task(void *pdata)
{     
    while(1)
    {
        LED1=0;
        LED0=1;
		printf("Led1 is on and led0 is off for 100ms.\r\n");
        delay_ms(100);
        LED1=1;
        LED0=0;
		printf("Led1 is off and led0 is on for 400ms.\r\n\r\n");
        delay_ms(400);
    };
}
