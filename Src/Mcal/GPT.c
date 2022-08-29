/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GPT
 *        \brief  GPTM Driver
 *
 *      \details  
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "GPT.h"
#include "GPT_Types.h"
#include "GPT_Cfg.h"


/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint32 GPT_Base_Addr[NUM_OF_TIMER_MODULES]={
	TIMER0_BASE,
	TIMER1_BASE,
	TIMER2_BASE,
	TIMER3_BASE,
	TIMER4_BASE,
	TIMER5_BASE,
	WIDE_TIMER0_BASE,
	WIDE_TIMER1_BASE,
	WIDE_TIMER2_BASE,
	WIDE_TIMER3_BASE,
	WIDE_TIMER4_BASE,
	WIDE_TIMER5_BASE,
};

  static GPT_NotificationType GPT_NotificationsPtrs[NUM_OF_TIMER_NOTIFICATION]={
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
};


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/******************************************************************************
* \Syntax          : void GPT_Init(void)                                      
* \Description     : initialize the GPTs (enabling clock, setting direction
*										 ,disable interrupts,select mode)                                                        
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_Init(void){
	
	for(uint8 i=0; i<NO_OF_GPT_ACTIVATED;i++){
		GPT_ChannelType currTimerID=InitalizedTimers[i].channelID;
		uint32 currTimerBase=GPT_Base_Addr[InitalizedTimers[i].channelID];
		
		if(currTimerID/6==0){
			ACCESS_REG(SYSCTL_RCGC_BASE,SYSCTL_GPTM_OFFSET)= 1U<<currTimerID;
			while(!(ACCESS_REG(SYSCTL_PR_BASE,SYSCTL_GPTM_OFFSET)   &   1U<<currTimerID )  ){}	
		}
		else{
			ACCESS_REG(SYSCTL_RCGC_BASE,SYSCTL_WIDE_GPTM_OFFSET)= 1U<<(currTimerID%6);
		while(!(ACCESS_REG(SYSCTL_PR_BASE,SYSCTL_WIDE_GPTM_OFFSET)   &   1U<<(currTimerID%6))  ){}
		}
		
		ACCESS_REG(currTimerBase,GPTMCTL)=0;
		ACCESS_REG(currTimerBase,GPTMCFG)=0x4;
		ACCESS_REG(currTimerBase,GPTMTAMR)|=InitalizedTimers[i].channelMode;
		ACCESS_REG(currTimerBase,GPTMTAMR)|= (1<<GPTMTAMR_TACDIR);
		GPT_DisableNotification(currTimerID);
	}

}

/******************************************************************************
* \Syntax          : void GPT_DisableNotification( GPT_ChannelType Channel )                                      
* \Description     : disable interrupt for a given channel 
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_DisableNotification( GPT_ChannelType Channel )
{
	uint32 currTimerBase=GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMIMR)=0U;

}

/******************************************************************************
* \Syntax          : void GPT_EnableNotification( GPT_ChannelType Channel )                                      
* \Description     : enable interrupt for a given channel on timeout  
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_EnableNotification( GPT_ChannelType Channel )
{
	uint32 currTimerBase=GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMIMR)|=1U<<GPTMIMR_TATOIM;
}
/******************************************************************************
* \Syntax          : void GPT_EnableNotificationWithMatch( GPT_ChannelType Channel )                                      
* \Description     : enable interrupt for a given channel  on timeout and match
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_EnableNotificationWithMatch( GPT_ChannelType Channel )
{
	uint32 currTimerBase=GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMIMR)|=(1U<<GPTMIMR_TATOIM | 1U<<GPTMIMR_TAMIM);
	ACCESS_REG(currTimerBase,GPTMTAMR)|=(1U<<GPTMTAMR_TAMIE);
}

/******************************************************************************
* \Syntax          : void GPT_StartTimer( GPT_ChannelType Channel, GPT_ValueType Value )                                    
* \Description     : start timer with the given timeout period
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType ,GPT_ValueType                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StartTimer( GPT_ChannelType Channel, GPT_ValueType Value ) {
		
	uint32 currTimerBase=GPT_Base_Addr[Channel];
		uint32 currTimerTickFreq=0;
		
	
		for( uint8 i=0; i<NO_OF_GPT_ACTIVATED;i++)
		{
			if (InitalizedTimers[i].channelID == Channel)
			{	
			currTimerTickFreq = InitalizedTimers[i].channelTickFreq;			
			break;
		}
	}
	
	uint32 scaler=(MCU_CLOCK_FREQ/currTimerTickFreq);
	ACCESS_REG(currTimerBase,GPTMTAILR)=Value*scaler ;
	ACCESS_REG(currTimerBase,GPTMCTL) |= 0x1;
}

/******************************************************************************
* \Syntax          : void GPT_StartTimerWithMatch( GPT_ChannelType Channel, GPT_ValueType Value,GPT_ValueType MatchValue )                                    
* \Description     : start timer with the given timeout period and match period
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType  ,GPT_ValueType,GPT_ValueType                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StartTimerWithMatch( GPT_ChannelType Channel, GPT_ValueType Value,GPT_ValueType MatchValue ) {
		
	uint32 currTimerBase=GPT_Base_Addr[Channel];
		uint32 currTimerTickFreq=0;
		
		for( uint8 i=0; i<NO_OF_GPT_ACTIVATED;i++)
		{
			if (InitalizedTimers[i].channelID == Channel)
			{	
			currTimerTickFreq = InitalizedTimers[i].channelTickFreq;			
			break;
		}
	}
	
	uint32 scaler=(MCU_CLOCK_FREQ/currTimerTickFreq);
	ACCESS_REG(currTimerBase,GPTMTAILR)=Value*scaler ;
	ACCESS_REG(currTimerBase,GPTMTAMATCHR)=MatchValue*scaler ;
	ACCESS_REG(currTimerBase,GPTMCTL) |= 1U<<GPTMCTL_TAEN;
}

/******************************************************************************
* \Syntax          : void GPT_StopTimer( GPT_ChannelType Channel )                                    
* \Description     : stop the given timer
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StopTimer( GPT_ChannelType Channel )
{
	
	uint32 currTimerBase = GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMCTL) &=(~(1U<<GPTMCTL_TAEN));
}

/******************************************************************************
* \Syntax          : GPT_ValueType GPT_GetTimeElapsed( GPT_ChannelType Channel )                                    
* \Description     : get the time elapsed since timer start
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                   
* \Parameters (out): GPT_ValueType                                                      
* \Return value:   : GPT_ValueType uint32
*******************************************************************************/
GPT_ValueType GPT_GetTimeElapsed( GPT_ChannelType Channel ){
	
		uint32 currTimerBase=GPT_Base_Addr[Channel];
		GPT_ValueType currTimerTickFreq=0;
		GPT_ValueType currTimerTickValMax=0;
	
	for( uint8 i=0; i<NO_OF_GPT_ACTIVATED;i++)
		{
			if (InitalizedTimers[i].channelID == Channel)
			{	
			currTimerTickFreq = InitalizedTimers[i].channelTickFreq;
			currTimerTickValMax = InitalizedTimers[i].channelTickValMax;				
			break;
		}
	}
	uint32 scaler=(MCU_CLOCK_FREQ/currTimerTickFreq);
	GPT_ValueType elapsed = (ACCESS_REG(currTimerBase,GPTMTAV)/scaler & currTimerTickValMax);
	
return elapsed;
}


/******************************************************************************
* \Syntax          : GPT_ValueType GPT_GetTimeRemaining( GPT_ChannelType Channel                                    
* \Description     : get the time remaining for the timer to timeout
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                   
* \Parameters (out): GPT_ValueType                                                      
* \Return value:   : GPT_ValueType uint32
*******************************************************************************/
GPT_ValueType GPT_GetTimeRemaining( GPT_ChannelType Channel ){
	
		uint32 currTimerBase=GPT_Base_Addr[Channel];
		GPT_ValueType currTimerTickFreq=0;
		GPT_ValueType currTimerTickValMax=0;
	
	for( uint8 i=0; i<NO_OF_GPT_ACTIVATED;i++)
		{
			if (InitalizedTimers[i].channelID == Channel)
			{	
			currTimerTickFreq = InitalizedTimers[i].channelTickFreq;
			currTimerTickValMax = InitalizedTimers[i].channelTickValMax;				
			break;
		}
	}
	uint32 scaler=(MCU_CLOCK_FREQ/currTimerTickFreq);
	
	
	GPT_ValueType intervalVal=ACCESS_REG(currTimerBase,GPTMTAILR);
	GPT_ValueType currVal=ACCESS_REG(currTimerBase,GPTMTAV);
	GPT_ValueType remaining = ((intervalVal-currVal)/scaler & currTimerTickValMax);
	
return remaining;
}

/******************************************************************************
* \Syntax          : void GPT_Notification_Register (GPT_NotificationType FuncPointer,GPT_IndexType TimerIndex)                                   
* \Description     : registers a callback function for the given timer
*										                                                         
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : GPT_ChannelType                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_Notification_Register (GPT_NotificationType FuncPointer,GPT_ChannelType Timer){
	
	GPT_NotificationsPtrs[Timer]=FuncPointer;
}


// WTIMER0A_Handler which calls the callback function if not set to null

 void WTIMER0A_Handler(void){
	if(GPT_NotificationsPtrs[WIDE_TIMER0]!=NULL_PTR){
		(GPT_NotificationsPtrs[WIDE_TIMER0])();
	}

}

/**********************************************************************************************************************
 *  END OF FILE: GPT.c
 *********************************************************************************************************************/
