/**********************************
包含头文件
**********************************/
#include "motor_duoji.h"
#include "delay.h"


/*
控制count值控制电机转动角度（1750-1950对应180°，每10对应0.9°）
uint16_t motor_duoji_cout;			//舵机pwm值

motor_duoji_cout = 1850;				//舵机pwm初始值90°
TIM_SetCompare1(TIM1,cout); 		//设置定时器pwm值
*/


/****
*******舵机初始化函数
*****/
void Motor_Duoji_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//ADC数据右对齐
	ADC_Init(ADC1, &ADC_InitStructure);															//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器 
	
	RCC_APB2PeriphClockCmd(MOTOR_DUOJI_TIM_CLK_ENABLE, ENABLE);			// 使能定时器时钟
	RCC_APB2PeriphClockCmd(MOTOR_DUOJI_GPIO_CLK_ENABLE , ENABLE);  	//使能GPIO外设时钟
 								//MOE 主输出使能

	TIM_OC1PreloadConfig(MOTOR_DUOJI_TIM, TIM_OCPreload_Enable); 	 	//预装载使能
	TIM_OC4PreloadConfig(MOTOR_DUOJI_TIM, TIM_OCPreload_Enable); 	 	//预装载使能	 

	TIM_ARRPreloadConfig(MOTOR_DUOJI_TIM, ENABLE); 									//使能定时器在ARR上的预装载寄存器

	TIM_Cmd(MOTOR_DUOJI_TIM, ENABLE);  															//使能定时器
}

void Motor_Duoji2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(MOTOR_DUOJI2_TIM_CLK_ENABLE, ENABLE);			// 使能定时器时钟
	RCC_APB2PeriphClockCmd(MOTOR_DUOJI2_GPIO_CLK_ENABLE , ENABLE);  	//使能GPIO外设时钟

	//设置IO引脚
	GPIO_InitStructure.GPIO_Pin = MOTOR_DUOJI2_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(MOTOR_DUOJI2_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_SetBits(MOTOR_DUOJI2_PORT,MOTOR_DUOJI2_PIN);						 			//初始输出高
	
	GPIO_InitStructure.GPIO_Pin = MOTOR_DUOJI2_PIN_2;				 				//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(MOTOR_DUOJI2_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	GPIO_SetBits(MOTOR_DUOJI2_PORT,MOTOR_DUOJI2_PIN_2);						 		//初始输出高

	//设置该引脚为复用输出功能,输出PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = MOTOR_DUOJI2_PIN; 									//TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  								//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(MOTOR_DUOJI2_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	
	GPIO_InitStructure.GPIO_Pin = MOTOR_DUOJI2_PIN_2; 									//TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  								//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//IO口速度为50MHz
	GPIO_Init(MOTOR_DUOJI2_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化

	//PWM频率===(2000*720)/72000000=0.02=20ms
	TIM_TimeBaseStructure.TIM_Period = 1999; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =719; 											//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 										//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  		//TIM向上计数模式
	TIM_TimeBaseInit(MOTOR_DUOJI2_TIM, &TIM_TimeBaseStructure); 			//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM1 Channe11 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 							//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 															//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
	TIM_OC1Init(MOTOR_DUOJI2_TIM, &TIM_OCInitStructure);  						//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 							//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 															//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
	TIM_OC2Init(MOTOR_DUOJI2_TIM, &TIM_OCInitStructure);  						//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(MOTOR_DUOJI2_TIM,ENABLE);											//MOE 主输出使能

	TIM_OC1PreloadConfig(MOTOR_DUOJI2_TIM, TIM_OCPreload_Enable); 	 	//预装载使能
	TIM_OC2PreloadConfig(MOTOR_DUOJI2_TIM, TIM_OCPreload_Enable); 	 	//预装载使能	 

	TIM_ARRPreloadConfig(MOTOR_DUOJI2_TIM, ENABLE); 									//使能定时器在ARR上的预装载寄存器

	TIM_Cmd(MOTOR_DUOJI2_TIM, ENABLE);  															//使能定时器
}
