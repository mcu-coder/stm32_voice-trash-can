/**********************************
包含头文件
**********************************/
#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "delay.h"
#include "gpio.h"
#include "key.h"
#include "usart.h"
#include "motor_duoji.h"


/**********************************
变量定义
**********************************/
uint8_t key_num = 0;									//按键扫描标志位	
uint32_t time_num = 0;								//10ms计时
uint8_t flag_waste_1 = 0;							//可回收垃圾桶标志位
uint8_t flag_waste_2 = 0;							//厨余垃圾桶标志位
uint8_t flag_waste_3 = 0;							//有害垃圾桶标志位
uint8_t flag_waste_4 = 0;							//其他垃圾桶标志位
extern uint8_t usart2_buf[64];				//串口2接收数组

/**********************************
函数声明
**********************************/
void Key_function(void);							//按键函数
void Monitor_function(void);					//监测函数
void Manage_function(void);						//处理函数


/****
*******	主函数 
*****/
int main()
{
	Delay_Init();	    	 								//延时初始化	  
	Gpio_Init();		  									//IO初始化
	Key_Init();		  										//按键初始化 
	Usart1_Init(9600);									//串口1初始化
	Usart2_Init(9600);									//串口2初始化
 										//延时100ms
	
	while(1)
	{
		Key_function();										//按键函数
		Monitor_function();								//监测函数
		Manage_function();								//处理函数

		Delay_ms(10);											//延时10ms
		time_num++;												//计时变量+1
		if(time_num >= 5000)
		{
			time_num = 0;
		}
	}
}

/****
*******按键函数
*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(0);		//按键扫描
 
}

/****
*******监测函数
*****/
void Monitor_function(void)
{
	if(USART2_WaitRecive() == 0)					//如果收到数据
	{
		if(usart2_buf[0] == 0x01)						//收到语音指令是“废纸|塑料瓶|可回收垃圾”，控制可回收垃圾桶打开
		{
			TIM_SetCompare1(TIM2,1900); 			//打开
			Delay_ms(1000);										//延时2s
			Delay_ms(1000);
			TIM_SetCompare1(TIM2,1850); 			//关闭
			USART2_Clear();										//清空缓存
		}
		else if(usart2_buf[0] == 0x02)			//收到语音指令是“剩饭|骨头|厨余垃圾”，控制厨余垃圾桶打开
		{
			TIM_SetCompare2(TIM2,1900); 			//打开
			Delay_ms(1000);										//延时2s
			Delay_ms(1000);
			TIM_SetCompare2(TIM2,1850); 			//关闭
			USART2_Clear();										//清空缓存
		}
	 
	}
}
/****
*******处理函数
*****/
void Manage_function(void)
{
	if(IR_1 == 1)													//可回收垃圾桶装满，红灯亮，并通过蓝牙发送"可回收垃圾桶已满"
	{
		Delay_ms(1000);
		if(IR_1 == 1)
		{
			LED1_G = 1;
			LED1_R = 0;
			if(flag_waste_1)
			{
				UsartPrintf(USART1,"可回收垃圾桶已满\r\n");
				flag_waste_1 = 0;
			}
		}
	}
	else																	//未装满，绿灯亮
	{
		LED1_G = 0;
		LED1_R = 1;
		flag_waste_1 = 1;
	}
	  
}

