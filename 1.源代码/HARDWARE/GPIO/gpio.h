
#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LED1_G_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED1_G引脚
#define LED1_G_PORT                           		GPIOB
#define LED1_G_PIN                            		GPIO_Pin_0
#define LED1_G 																	PBout(0)

#define LED1_R_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED1_R引脚
#define LED1_R_PORT                           		GPIOB
#define LED1_R_PIN                            		GPIO_Pin_1
#define LED1_R 																	PBout(1)

#define LED2_G_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED2_G引脚
#define LED2_G_PORT                           		GPIOB
#define LED2_G_PIN                            		GPIO_Pin_10
#define LED2_G 																	PBout(10)

#define LED2_R_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED2_R引脚
#define LED2_R_PORT                           		GPIOB
#define LED2_R_PIN                            		GPIO_Pin_11
#define LED2_R 																	PBout(11)

#define LED3_G_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED3_G引脚
#define LED3_G_PORT                           		GPIOB
#define LED3_G_PIN                            		GPIO_Pin_12
#define LED3_G 																	PBout(12)

#define LED3_R_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED3_R引脚
#define LED3_R_PORT                           		GPIOB
#define LED3_R_PIN                            		GPIO_Pin_13
#define LED3_R 																	PBout(13)

#define LED4_G_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED4_G引脚
#define LED4_G_PORT                           		GPIOB
#define LED4_G_PIN                            		GPIO_Pin_14
#define LED4_G 																	PBout(14)

#define LED4_R_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOB				//LED4_R引脚
#define LED4_R_PORT                           		GPIOB
#define LED4_R_PIN                            		GPIO_Pin_15
#define LED4_R 																	PBout(15)

#define IR_1_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOA				//IR_1引脚
#define IR_1_PORT                           	GPIOA
#define IR_1_PIN                            	GPIO_Pin_4
#define IR_1 																	PAin(4)

#define IR_2_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOA				//IR_2引脚
#define IR_2_PORT                           	GPIOA
#define IR_2_PIN                            	GPIO_Pin_5
#define IR_2 																	PAin(5)

#define IR_3_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOA				//IR_3引脚
#define IR_3_PORT                           	GPIOA
#define IR_3_PIN                            	GPIO_Pin_6
#define IR_3 																	PAin(6)

#define IR_4_GPIO_CLK_ENABLE             			RCC_APB2Periph_GPIOA				//IR_4引脚
#define IR_4_PORT                           	GPIOA
#define IR_4_PIN                            	GPIO_Pin_7
#define IR_4 																	PAin(7)

/**********************************
函数声明
**********************************/
void Gpio_Init(void);													//GPIO初始化

		 				    
#endif
