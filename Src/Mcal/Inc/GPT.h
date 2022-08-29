/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_Port.h.h
 *       Module:  GPIO_Port.h
 *
 *  Description:  header file for GPIO_Port Module    
 *  
 *********************************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "GPT_Types.h"



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
	#define NUM_OF_TIMER_NOTIFICATION			12
	#define NUM_OF_TIMER_MODULES					12
	
	//Register specific bitfield shift
	
	#define GPTMTAMR_TACDIR							4U
	#define GPTMCTL_TAEN								0U
	#define GPTMIMR_TAMIM								4U
	#define GPTMIMR_TATOIM							0U
	#define GPTMMIS_TATOMIS							0U
	#define GPTMMIS_TAMIMIS							4U
	#define GPTMTAMR_TAMIE							5U
	
	

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 void GPT_Init(void);
 
 void GPT_DisableNotification( GPT_ChannelType Channel );
	 
 void GPT_EnableNotification( GPT_ChannelType Channel );
 
 void GPT_EnableNotificationWithMatch( GPT_ChannelType Channel );
 
void GPT_StartTimer( GPT_ChannelType Channel, GPT_ValueType Value ) ;

void GPT_StartTimerWithMatch( GPT_ChannelType Channel, GPT_ValueType Value,GPT_ValueType MatchValue );

void GPT_StopTimer( GPT_ChannelType Channel );

GPT_ValueType GPT_GetTimeElapsed( GPT_ChannelType Channel );

GPT_ValueType GPT_GetTimeRemaining( GPT_ChannelType Channel );

void GPT_Notification_Register (GPT_NotificationType FuncPointer,GPT_ChannelType Timer);

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

 
#endif  /* GPIO_PORT_H */

/**********************************************************************************************************************
 *  END OF FILE: GPIO_Port.h
 *********************************************************************************************************************/
