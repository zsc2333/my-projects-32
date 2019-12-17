/*--------------------------------------------------------------------------------------
*  @file     Driver.c
*  @author   EU���� 
*  @version  base on stm32f40x   
*  @date     2016.08.19
*  @brief    none
---------------------------------------------------------------------------------------*/
/* ��׼C����� */
#include <string.h>
#include <stdio.h>
#include <stddef.h> 

/* ����ת�� */
#define  True  1
#define  False 0
typedef unsigned char       bool;
typedef unsigned char       u8;
typedef unsigned short      u16;

//����һ��BITΪ1    Example: a |= SETBIT0
enum
{
	SETBIT0 = 0x0001,  SETBIT1 = 0x0002,	SETBIT2 = 0x0004,	 SETBIT3 = 0x0008,
	SETBIT4 = 0x0010,	 SETBIT5 = 0x0020,	SETBIT6 = 0x0040,	 SETBIT7 = 0x0080,
	SETBIT8 = 0x0100,	 SETBIT9 = 0x0200,	SETBIT10 = 0x0400, SETBIT11 = 0x0800,
	SETBIT12 = 0x1000, SETBIT13 = 0x2000,	SETBIT14 = 0x4000, SETBIT15 = 0x8000		
};
//����һ��BIT   Example: a &= CLRBIT0
enum
{
	CLRBIT0 = 0xFFFE,  CLRBIT1 = 0xFFFD,	CLRBIT2 = 0xFFFB,	 CLRBIT3 = 0xFFF7,	
	CLRBIT4 = 0xFFEF,	 CLRBIT5 = 0xFFDF,	CLRBIT6 = 0xFFBF,	 CLRBIT7 = 0xFF7F,
	CLRBIT8 = 0xFEFF,	 CLRBIT9 = 0xFDFF,	CLRBIT10 = 0xFBFF, CLRBIT11 = 0xF7FF,
	CLRBIT12 = 0xEFFF, CLRBIT13 = 0xDFFF,	CLRBIT14 = 0xBFFF, CLRBIT15 = 0x7FFF
};
//ѡ��һ��BIT  Example: a = b&CHSBIT0
enum
{
	CHSBIT0 = 0x0001,  CHSBIT1 = 0x0002,	CHSBIT2 = 0x0004,	 CHSBIT3 = 0x0008,
	CHSBIT4 = 0x0010,	 CHSBIT5 = 0x0020,	CHSBIT6 = 0x0040,	 CHSBIT7 = 0x0080,
	CHSBIT8 = 0x0100,	 CHSBIT9 = 0x0200,	CHSBIT10 = 0x0400, CHSBIT11 = 0x0800,
	CHSBIT12 = 0x1000, CHSBIT13 = 0x2000,	CHSBIT14 = 0x4000, CHSBIT15 = 0x8000		
};

/* INCLUDES */
#include "Driver.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
/*-------------------------------------------------------------------------------------------------------
*  �ڲ�����								 
-------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------
*  ��Դ����											 
-------------------------------------------------------------------------------------------------------*/
static u8 Driver_PWMSta;
/*-------------------------------------------------------------------------------------------------------
*  ��������												 
-------------------------------------------------------------------------------------------------------*/
void Driver_MCU_Init(void);
void Driver_LedCont(u8 Num, bool sta);
/*-------------------------------------------------------------------------------------------------------
*  ִ�д���													 
-------------------------------------------------------------------------------------------------------*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++  ƽ̨���� +++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/********************************************************************************************************
*  Function: Driver_MCU_Init						                                                           
*  Object: MCU��ʼ��               
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ʱ������ MCU������һЩ����                                      
********************************************************************************************************/
void Driver_MCU_Init(void)
{

		#define PLL_M      8
		#define PLL_N      336	
		#define PLL_P      2	
		#define PLL_Q      7	
  	//--------------------------- CLK INIT, HSE PLL ----------------------------
		ErrorStatus HSEStartUpStatus;
		//RCC reset
		RCC_DeInit();
		//Enable HSE
		RCC_HSEConfig(RCC_HSE_ON); 
		//Wait HSE is ready
		HSEStartUpStatus = RCC_WaitForHSEStartUp();
		//If HSE start fail, wail and wail.
		while(HSEStartUpStatus == ERROR);
		//Set bus clock
		RCC_HCLKConfig(RCC_SYSCLK_Div1);	//(HCLK=SYSCLK)=168MHz
		RCC_PCLK1Config(RCC_HCLK_Div4);		//(PCLK1=SYSCLK/4)=42MHz
		RCC_PCLK2Config(RCC_HCLK_Div2);		//(PCLK2=SYSCLK/2)=84MHz
		//HSE 8M PLL-> 168M	
		//PLL=8MHz * N/ (M*P)=8MHz* 336 /(8*2) = 168MHz
		RCC_PLLConfig(RCC_PLLSource_HSE,PLL_M ,PLL_N ,PLL_P,PLL_Q);
		RCC_PLLCmd(ENABLE); 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		//Select PLL as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);
		
		

		//----------------------------- CLOSE HSI ---------------------------
		RCC_HSICmd(DISABLE);

		//--------------------------- OPEN GPIO CLK -------------------------
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		//---------------------------- INT CONFIG ---------------------------
		//2-level interrupt 
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
			
		//---------------------------- JTAG CONFIG ---------------------------
		//JTAG/SWD disable
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
}		   

/********************************************************************************************************
*  Function: Driver_OpenEA					                                                           
*  Object: MCU�����ж�           
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ��	                                         
********************************************************************************************************/
void Driver_OpenEA(void)
{
		//���ж�
		__enable_irq(); 
}

/********************************************************************************************************
*  Function: Driver_Time10msON					                                                           
*  Object: 10ms��ʱ��ʼ������
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ��                    
********************************************************************************************************/
void Driver_Time10msON(void)
{	
		//set 10ms interrupt  (1/100)s = 10ms   
		SysTick_Config(168000000 / 100);
}

/********************************************************************************************************
*  Function: Driver_10ms_Interrupt					                                                           
*  Object: 10ms��ʱ�ж�
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ��   	                                  
********************************************************************************************************/
void Driver_10ms_Interrupt(void)
{
	  extern void Time_IntHandle(void);
		Time_IntHandle();
}
/********************************************************************************************************
*  Function: Driver_LedCont						                                                           
*  Object: 	LED����
*  ���룺 True, ��;  False, �ر�;
*  ����� ��	                                     
*  ��ע�� PB10                
********************************************************************************************************/
void Driver_LedCont(u8 Num, bool sta)
{
		static bool StartFlag = True;
		if(StartFlag)
		{
			GPIO_InitTypeDef GPIO_InitStructure;
			//initial LED1(PC0)
			GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 ;
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  	
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
			GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;								//��������
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			
			// initial LED2(PD3)
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  	
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
			GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;								//��������
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			StartFlag = False;
		}	
		switch(Num)
		{
				case 0: if(!sta) GPIO_SetBits(GPIOC, GPIO_Pin_0);	else GPIO_ResetBits(GPIOC, GPIO_Pin_0);	 break;
				case 1: if(!sta) GPIO_SetBits(GPIOD, GPIO_Pin_3);	else GPIO_ResetBits(GPIOD, GPIO_Pin_3);	 break;
		}
}
/********************************************************************************************************
*  Function: Driver_LightPWMON				                                                           
*  Object: PWM���� ��ʼ��
*  ���룺 ��
*  ����� ��                                     
*  ��ע�� ���ö�ʱ�������жϴ���                   
********************************************************************************************************/
void Driver_LightPWMON(void)
{ 
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		//������ʱ������ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		//���ö�ʱ������
		TIM_DeInit(TIM3); 
		TIM_TimeBaseStructure.TIM_Period = 20; 								     //20us�ж�һ��
		TIM_TimeBaseStructure.TIM_Prescaler = (84000000/1000000 - 1);              
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
		//�ж�����
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2 �����ȼ����ж� 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	 //��Ӧ���ȼ�0 �߼������Ӧ�ж�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
		NVIC_Init(&NVIC_InitStructure);	  
		//���ж�
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);					  
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
		//������ʱ��			 
		TIM_Cmd(TIM3, ENABLE); 
		//Ϩ��LED1-2
		Driver_LedCont(0, 0);
		Driver_LedCont(1, 0);
}

/********************************************************************************************************
*  Function: Driver_LightPWMSet				                                                           
*  Object: PWM���� 
*  ���룺 0~9  ���ȴӰ�����
*  ����� ��                                     
*  ��ע�� ���ö�ʱ�������жϴ��� ģ��PWM�仯                  
********************************************************************************************************/
void Driver_LightPWMSet(u8 sta)
{
		Driver_PWMSta = sta;
}

/********************************************************************************************************
*  Function: DriverLightPWMIntHandle				                                                           
*  Object: ģ��PWM��ʱ�жϴ���
*  ����: ��
*  ���: ��                                   
*  ��ע: ���ռ�ձȿɵ�����
********************************************************************************************************/
void DriverLightPWMIntHandle(void)
{
		//���жϱ�ʶ
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		//---------------- �жϴ���  ---------------------
		{
				static u8 Step = 0;
			  Step++;
				if(Step == 10)
					Step = 0;
				//ģ��PWM�仯
				if(Step < Driver_PWMSta)
					Driver_LedCont(0, 1);
				else
					Driver_LedCont(0, 0);
		}
}

/********************************************************************************************************
*  Function: Driver_Key1Sta						                                                           
*  Object: ����1״̬
*  ����: ��
*  ���: 1/0                                 
*  ��ע: ��                         
********************************************************************************************************/
bool Driver_Key1Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	 
			GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) ;
}

/********************************************************************************************************
*  Function: Driver_Key2Sta						                                                           
*  Object: ����2״̬
*  ����: ��
*  ���: 1/0                                 
*  ��ע: ��                              
********************************************************************************************************/
bool Driver_Key2Sta(void)
{
		static bool StartFlag = True;
		if(StartFlag)
		{	
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	 
			GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;
			GPIO_Init(GPIOF, &GPIO_InitStructure);
			StartFlag = False;
		}
		return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11);
}
