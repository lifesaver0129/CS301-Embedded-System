#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "remote.h"

int main(void) {
    u8 key;
    u8 t = 0;
    u8 *str = 0;
    //Create a matrix to record the data
    int rec[9][9] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 3, 6, 0, 0, 0, 0, 0},
                     {0, 7, 0, 0, 9, 0, 2, 0, 0},
                     {0, 5, 0, 0, 0, 7, 0, 0, 0},
                     {0, 0, 0, 0, 4, 5, 7, 0, 0},
                     {0, 0, 0, 1, 0, 0, 0, 3, 0},
                     {0, 0, 1, 0, 0, 0, 0, 6, 8},
                     {0, 0, 8, 5, 0, 0, 0, 1, 0},
                     {0, 9, 0, 0, 0, 0, 4, 0, 0}};
    //Create a matrix to store the answer
    int ans[9][9] = {{8, 1, 2, 7, 5, 3, 6, 4, 9},
                     {9, 4, 3, 6, 8, 2, 1, 7, 5},
                     {6, 7, 5, 4, 9, 1, 2, 8, 3},
                     {1, 5, 4, 2, 3, 7, 8, 9, 6},
                     {3, 6, 9, 8, 4, 5, 7, 2, 1},
                     {2, 8, 7, 1, 6, 9, 5, 3, 4},
                     {5, 2, 1, 9, 7, 4, 3, 6, 8},
                     {4, 3, 8, 5, 2, 6, 9, 1, 7},
                     {7, 9, 6, 3, 1, 8, 4, 5, 2}};
    //Create a matrix to record all the input
    int data[9][9] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 3, 6, 0, 0, 0, 0, 0},
                      {0, 7, 0, 0, 9, 0, 2, 0, 0},
                      {0, 5, 0, 0, 0, 7, 0, 0, 0},
                      {0, 0, 0, 0, 4, 5, 7, 0, 0},
                      {0, 0, 0, 1, 0, 0, 0, 3, 0},
                      {0, 0, 1, 0, 0, 0, 0, 6, 8},
                      {0, 0, 8, 5, 0, 0, 0, 1, 0},
                      {0, 9, 0, 0, 0, 0, 4, 0, 0}};
    //Set the cursor
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int cnte = 0;
    int edge = 0;
    //Some initial settings
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);
    LED_Init();
    LCD_Init();
    KEY_Init();
    Remote_Init();
    //Set color to black.
    POINT_COLOR = BLACK;
    //Fill the corner of the color yellow.
    LCD_Fill(13, 13, 11 + 24 * 3, 11 + 24 * 3, 0xFFE0);
    LCD_Fill(13 + 24 * 6, 13, 11 + 24 * 9, 11 + 24 * 3, 0xFFE0);
    LCD_Fill(13 + 24 * 3, 13 + 24 * 3, 11 + 24 * 6, 11 + 24 * 6, 0xFFE0);
    LCD_Fill(13, 13 + 24 * 6, 11 + 24 * 3, 11 + 24 * 9, 0xFFE0);
    LCD_Fill(13 + 24 * 6, 13 + 24 * 6, 11 + 24 * 9, 11 + 24 * 9, 0xFFE0);
    //Draw the vertical and horizon line.
    for (i = 0; i < 10; i++) {
        LCD_DrawLine(12, 12 + 24 * i, 228, 12 + 24 * i);
        LCD_DrawLine(12 + 24 * i, 12, 12 + 24 * i, 228);
    }
    //Write the title
    LCD_ShowString(30, 240, 200, 16, 16, "World's Hartdest SUDOKU");
    //Write the designer name
    LCD_ShowString(24, 260, 200, 16, 16, "Maker: 11510225 Yuxing Hu");
    //Fill in some number
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (rec[i][j] != 0)
                LCD_ShowNum(20 + 24 * j, 16 + 24 * i, rec[i][j], 1, 16);
        }
    }
    while (1) {
        key = Remote_Scan();
        t = KEY_Scan(0);
        if (t) {
            //The number that filled in will be displayed in blue.
            POINT_COLOR = BLUE;
            //Cover up the help
            LCD_Fill(4, 280, 16 + 8 * 30, 300, WHITE);
            switch (t) {
                case KEY0_PRES:
                    if (edge == 1) {
                        LCD_ShowString(50, 280, 200, 16, 16, "Edge wall is closed");
                        edge = 0;
                    } else {
                        LCD_ShowString(50, 280, 200, 16, 16, "Edge wall is opened");
                        edge = 1;
                    }
                    break;
                case KEY1_PRES:
                    POINT_COLOR = RED;
                    LCD_ShowString(34, 280, 200, 16, 16, "KEY 1 is not reachable");
                    break;
                case WKUP_PRES:
                    //Set color to black.
                    POINT_COLOR = BLACK;
                    //Fill the corner of the color yellow.
                    LCD_Fill(13, 13, 11 + 24 * 3, 11 + 24 * 3, 0xFFE0);
                    LCD_Fill(13, 13 + 24 * 3, 11 + 24 * 3, 11 + 24 * 6, 0xFFFF);
                    LCD_Fill(13 + 24 * 6, 13, 11 + 24 * 9, 11 + 24 * 3, 0xFFE0);
                    LCD_Fill(13 + 24 * 3, 13, 11 + 24 * 6, 11 + 24 * 3, 0xFFFF);
                    LCD_Fill(13 + 24 * 3, 13 + 24 * 3, 11 + 24 * 6, 11 + 24 * 6, 0xFFE0);
                    LCD_Fill(13 + 24 * 3, 13 + 24 * 6, 11 + 24 * 6, 11 + 24 * 9, 0xFFFF);
                    LCD_Fill(13, 13 + 24 * 6, 11 + 24 * 3, 11 + 24 * 9, 0xFFE0);
                    LCD_Fill(13 + 24 * 6, 13 + 24 * 3, 11 + 24 * 9, 11 + 24 * 6, 0xFFFF);
                    LCD_Fill(13 + 24 * 6, 13 + 24 * 6, 11 + 24 * 9, 11 + 24 * 9, 0xFFE0);
                    //Draw the vertical and horizon line.
                    for (i = 0; i < 10; i++) {
                        LCD_DrawLine(12, 12 + 24 * i, 228, 12 + 24 * i);
                        LCD_DrawLine(12 + 24 * i, 12, 12 + 24 * i, 228);
                    }
                    //Fill in some number
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 9; j++) {
                            if (rec[i][j] != 0) {
                                LCD_ShowNum(20 + 24 * j, 16 + 24 * i, rec[i][j], 1, 16);
                            } else {
                                data[i][j] = 0;
                            }
                        }
                    }
                    break;
            }
        }
        if (key) {
            //The number that filled in will be displayed in blue.
            POINT_COLOR = BLUE;
            //Cover up the help
            LCD_Fill(4, 280, 16 + 8 * 30, 300, WHITE);
            switch (key) {
                case 0:
                    str = "ERROR";
                    break;
                case 162:
                    //case power
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 9; j++) {
                            if (data[i][j] == 0) {
                                POINT_COLOR = RED;
                                LCD_ShowString(52, 280, 200, 16, 16, "Please finish all!");
                                i = 10;
                                break;
                            }
                        }
                    }
                    if (i == 11)
                        break;
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 9; j++) {
                            if (data[i][j] != ans[i][j]) {
                                POINT_COLOR = RED;
                                LCD_ShowString(16, 280, 200, 16, 16, "Please recheck value in");
                                LCD_ShowNum(216, 280, j+1, 1, 16);
                                LCD_ShowNum(206, 280, i+1, 1, 16);
                                i = 9;
                                break;
                            }
                        }
                    }
                    if (i == 10)
                        break;
                    POINT_COLOR = RED;
                    LCD_ShowString(5, 280, 300, 16, 16, "Congratulations! You made it!");
                    break;
                case 98:
                    //case up
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    if (edge == 1) {
                        y = y - 1;
                        if (y < 0)
                            y = y + 9;
                        while (rec[y][x] != 0) {
                            y = y - 1;
                            if (y < 0)
                                y = y + 9;
                        }
                    } else {
                        cnte = 0;
                        y = y - 1;
                        if (y < 0)
                            y = y + 1;
                        while (rec[y][x] != 0) {
                            cnte += 1;
                            y = y - 1;
                            if(y<0)
                                break;
                        }
                        if (y < 0)
                            y = y + 1 + cnte;
                    }
                    printf("(%d, %d)", x, y);
                    POINT_COLOR = BLUE;
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    delay_ms(1000);
                    break;
                case 2:
                    str = "PLAY";
                    break;
                case 226:
                    str = "ALIENTEK";
                    break;
                case 194:
                    //case right
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    if (edge == 1) {
                        x = x + 1;
                        if (x > 8)
                            x = x - 9;
                        while (rec[y][x] != 0) {
                            x = x + 1;
                            if (x > 8)
                                x = x - 9;
                        }
                    } else {
                        cnte = 0;
                        x = x + 1;
                        if (x > 8)
                            x = x - 1;
                        while (rec[y][x] != 0) {
                            cnte += 1;
                            x = x + 1;
                        }
                        if (x > 8)
                            x = x - 1 - cnte;
                    }
                    printf("(%d, %d)", x, y);
                    POINT_COLOR = BLUE;
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    delay_ms(1000);
                    break;
                case 34: {
                    //case left
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    if (edge == 1) {
                        x = x - 1;
                        if (x < 0)
                            x = x + 9;
                        while (rec[y][x] != 0) {
                            x = x - 1;
                            if (x < 0)
                                x = x + 9;
                        }
                    } else {
                        cnte = 0;
                        x = x - 1;
                        if (x < 0)
                            x = x + 1;
                        while (rec[y][x] != 0) {
                            cnte += 1;
                            x = x - 1;
                        }
                        if (x < 0)
                            x = x + 1 + cnte;
                    }
                    printf("(%d, %d)", x, y);
                    POINT_COLOR = BLUE;
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    delay_ms(1000);
                    break;
                }
                case 224:
                    str = "VOL-";
                    break;
                case 168:
                    //case down
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    if (edge == 1) {
                        y = y + 1;
                        if (y > 8)
                            y = y - 8;
                        while (rec[y][x] != 0) {
                            y = y + 1;
                            if (y > 8)
                                y = y - 9;
                        }
                    } else {
                        cnte = 0;
                        y = y + 1;
                        if (y > 8)
                            y = y - 1;
                        while (rec[y][x] != 0) {
                            cnte += 1;
                            y = y + 1;
                            if (y > 8)
                                break;

                        }
                        if (y > 8)
                            y = y - 1 - cnte;
                    }
                    printf("(%d, %d)", x, y);
                    POINT_COLOR = BLUE;
                    LCD_DrawRectangle(13 + 24 * x, 13 + 24 * y, 13 + 24 * x + 22, 13 + 24 * y + 22);
                    delay_ms(1000);
                    break;
                case 144:
                    str = "VOL+";
                    break;
                case 104: {
                    //case num 1
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 1, 1, 16);
                    data[y][x] = 1;
                    break;
                }
                case 152:
                    //case num 2
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 2, 1, 16);
                    data[y][x] = 2;
                    break;
                case 176:
                    //case num 3
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 3, 1, 16);
                    data[y][x] = 3;
                    break;
                case 48:
                    //case num 4
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 4, 1, 16);
                    data[y][x] = 4;
                    break;
                case 24:
                    //case num 5
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 5, 1, 16);
                    data[y][x] = 5;
                    break;
                case 122:
                    //case num 6
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 6, 1, 16);
                    data[y][x] = 6;
                    break;
                case 16:
                    //case num 7
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 7, 1, 16);
                    data[y][x] = 7;
                    break;
                case 56:
                    //case num 8
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 8, 1, 16);
                    data[y][x] = 8;
                    break;
                case 90:
                    //case num 9
                    POINT_COLOR = LCD_ReadPoint(14 + 24 * x, 14 + 24 * y);
                    LCD_Fill(14 + 24 * x, 14 + 24 * y, 34 + 24 * x, 34 + 24 * y, POINT_COLOR);
                    POINT_COLOR = BLUE;
                    LCD_ShowNum(20 + 24 * x, 16 + 24 * y, 9, 1, 16);
                    data[y][x] = 9;
                    break;
                case 66:
                    //case num 0
                    POINT_COLOR = RED;
                    LCD_ShowString(32, 280, 200, 16, 16, "Num 0 is not available");
                    break;
                case 82:
                    str = "DELETE";
                    break;
            }
            //LCD_Fill(116,170,116+8*8,170+16,WHITE);
            //LCD_ShowString(116,170,200,16,16,str);
        } else delay_ms(500);
        //t++;
        //if(t==20)
        //{
        //t=0;
        //LED0=!LED0;
        //}
    }


}


