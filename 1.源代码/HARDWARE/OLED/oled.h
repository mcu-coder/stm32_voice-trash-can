/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef __OLED_H__
#define __OLED_H__


/**********************************
包含头文件
**********************************/
#include "sys.h" 


/**********************************
PIN口定义
**********************************/
#define OLED_SCL_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SCL引脚
#define OLED_SCL_PORT                 GPIOB
#define OLED_SCL_PIN                  GPIO_Pin_10
#define OLED_SCL  										PBout(10)

#define OLED_SDA_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SDA引脚
#define OLED_SDA_PORT                 GPIOB
#define OLED_SDA_PIN                  GPIO_Pin_11
#define OLED_SDA  										PBout(11)


/**********************************
函数声明
**********************************/
void Oled_Init(void);																							//OLED初始化函数
void Oled_Clear_All(void);																				//OLED清全屏函数
void Oled_ShowString(uint8_t x,uint8_t y,char *chr);							//OLED显示字符串函数
void Oled_ShowCHinese(uint8_t x,uint8_t y,char *P);								//OLED显示中文函数


#endif

