cmake_minimum_required(VERSION 3.8)
project(lab11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        HARDWARE/LCD/FONT.H
        HARDWARE/LCD/lcd.c
        HARDWARE/LCD/lcd.h
        HARDWARE/LED/led.c
        HARDWARE/LED/led.h
        HARDWARE/REMOTE/remote.c
        HARDWARE/REMOTE/remote.h
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

add_executable(lab11 ${SOURCE_FILES})