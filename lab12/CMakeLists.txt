cmake_minimum_required(VERSION 3.9)
project(lab12)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab12
        HARDWARE/KEY/key.c
        HARDWARE/KEY/key.h
        HARDWARE/LCD/FONT.H
        HARDWARE/LCD/lcd.c
        HARDWARE/LCD/lcd.h
        HARDWARE/LED/led.c
        HARDWARE/LED/led.h
        HARDWARE/STMFLASH/stmflash.c
        HARDWARE/STMFLASH/stmflash.h
        IAP/iap.c
        IAP/iap.h
        RTE/Device/STM32F103RC/RTE_Device.h
        RTE/Device/STM32F103RC/stm32f10x_conf.h
        RTE/Device/STM32F103RC/system_stm32f10x.c
        RTE/RTE_Components.h
        SYSTEM/delay/delay.c
        SYSTEM/delay/delay.h
        SYSTEM/sys/sys.c
        SYSTEM/sys/sys.h
        SYSTEM/usart/usart.c
        SYSTEM/usart/usart.h
        main.c)
