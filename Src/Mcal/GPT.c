/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IGPIO_Dio
 *        \brief  Dio Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
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
#include "TM4C123GH6PM.h"
#include "GPIO_Dio.h"






/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint32 GPT_Base_Addr[]={
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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static uint8 flag=0;
static uint32 ilrs[2]={1000,7000};
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
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
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
		ACCESS_REG(currTimerBase,GPTMTAMR)|= (1<<TACDIR);
		GPT_DisableNotification(currTimerID);
	}

}


void GPT_DisableNotification( GPT_ChannelType Channel )
{
	uint32 currTimerBase=GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMIMR)=0x0;

}


void GPT_EnableNotification( GPT_ChannelType Channel )
{
	uint32 currTimerBase=GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMIMR)=0x1;
}

void GPT_StartTimer( GPT_ChannelType Channel, GPT_ValueType Value ) {
		
	uint32 currTimerBase=GPT_Base_Addr[Channel];
		//uint8	checkWide=Channel/6;
		//GPT_ChannelType timerNo=Channel%6;
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



void GPT_StopTimer( GPT_ChannelType Channel )
{
	
	uint32 currTimerBase = GPT_Base_Addr[Channel];
	ACCESS_REG(currTimerBase,GPTMCTL) &=(~(1U<<TAEN));
}


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



GPT_ValueType GPT_GetTimeRemainig( GPT_ChannelType Channel ){
	
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

 void TIMER0A_Handler(void){
	int x=7;
	 
}

 void WTIMER0A_Handler(void){
	 flag=flag ^1U;
	 ACCESS_REG(WIDE_TIMER0_BASE,GPTMTAILR)=ilrs[flag]*16U;
	 Dio_FlipChannel(PORT_F,CHANNEL1);
	ACCESS_REG(WIDE_TIMER0_BASE,GPTMICR)|=0x1;
}

/**********************************************************************************************************************
 *  END OF FILE: GPIO_Dio.c
 *********************************************************************************************************************/
