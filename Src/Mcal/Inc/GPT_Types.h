/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Types.h
 *       Module:  GPT_Types
 *
 *  Description:  <>     
 *  
 *********************************************************************************************************************/
#ifndef GPT_TYPES_H
#define GPT_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PMC_SIZE						4u // size of PMC field in GPIOCTL register



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
	typedef enum{
		TIMER0,
		TIMER1,
		TIMER2,
		TIMER3,
		TIMER4,
		TIMER5,
		WIDE_TIMER0,
		WIDE_TIMER1,
		WIDE_TIMER2,
		WIDE_TIMER3,
		WIDE_TIMER4,
		WIDE_TIMER5
		}GPT_ChannelType;
	
		typedef uint32 GPT_ValueType;
		
	
	typedef enum{
		GPT_CH_MODE_ONESHOT=1,
		GPT_CH_MODE_CONTINUOUS
		}GPT_ModeType;
	
	typedef enum{
	GPT_PREDEF_TIMER_1US_16BIT,
		GPT_PREDEF_TIMER_1US_24BIT,
		GPT_PREDEF_TIMER_1US_32BIT,
		GPT_PREDEF_TIMER_100US_32BIT
}GPT_PredefTimerType; 


typedef void(*GPTNotification)(void);

typedef struct {
GPT_ChannelType channelID;
	GPT_ModeType channelMode;
	GPT_ValueType channelTickFreq;
	GPT_ValueType channelTickValMax;
	GPTNotification channelNotification;
}Port_ConfigType;
 
#endif  /* GPT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: GPT_Types.h
 *********************************************************************************************************************/
