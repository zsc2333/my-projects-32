#ifndef __Driver__
#define __Driver__
/*--------------------------------------------------------------------------------------
*  @file     Driver.h
*  @author   EU����
*  @version  base on stm32f4xx
*  @date     2016.08.25
*  @brief    none
---------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++ Type Declaration ++++++++++++++++++++++++++++++++++//
//!You should modify it for different c compiler.
typedef unsigned char       bool;
typedef unsigned char       u8;
/*-------------------------------------------------------------------------------------------------------
*  ��������					 
-------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------
*  ����ӿ�	ΪӦ�ò��ṩ�Ľӿ�										 
-------------------------------------------------------------------------------------------------------*/
//mcu
extern void Driver_MCU_Init(void);
extern void Driver_OpenEA(void);
//TIME
extern void Driver_Time10msON(void);
//LIGHT
extern void Driver_LightPWMON(void);
extern void Driver_LightPWMSet(u8 sta);
//KEY
extern bool Driver_Key1Sta(void);
extern bool Driver_Key2Sta(void);

#endif



