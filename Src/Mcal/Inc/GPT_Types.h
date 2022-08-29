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
		TIMERA=1,
		TIMERB,
		TIMERCON
		}GPT_TimerType;
		
	
	typedef enum{
		GPT_CH_MODE_ONESHOT=1,
		GPT_CH_MODE_CONTINUOUS
		}GPT_ModeType;
	

typedef enum{
	Timer0A_INDEX,
	TIMER0B_INDEX,
	TIMER1A_INDEX,
	TIMER1B_INDEX,
	TIMER2A_INDEX,
	TIMER2B_INDEX,
	TIMER3A_INDEX,
	TIMER3B_INDEX,
	TIMER4A_INDEX,
	TIMER4B_INDEX,
	TIMER5A_INDEX,
	TIMER5B_INDEX,
	WIDE_TIMER0A_INDEX,
	WIDE_TIMER0B_INDEX,
	WIDE_TIMER1A_INDEX,
	WIDE_TIMER1B_INDEX,
	WIDE_TIMER2A_INDEX,
	WIDE_TIMER2B_INDEX,
	WIDE_TIMER3A_INDEX,
	WIDE_TIMER3B_INDEX,
	WIDE_TIMER4A_INDEX,
	WIDE_TIMER4B_INDEX,
	WIDE_TIMER5A_INDEX,
	WIDE_TIMER5B_INDEX
}GPT_IndexType;

typedef void(*GPT_NotificationType)(void);

typedef struct {
GPT_ChannelType channelID;
	GPT_ModeType channelMode;
	GPT_ValueType channelTickFreq;
	GPT_ValueType channelTickValMax;
}GPT_ConfigType;

 
#endif  /* GPT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: GPT_Types.h
 *********************************************************************************************************************/
