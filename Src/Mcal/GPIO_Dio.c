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
#include "GPIO_Dio.h"
#include "Gpio_Dio_Types.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint32 GPIO_Port_Base_Addr[]={
	 GPIO_PORTA_BASE,
	GPIO_PORTB_BASE,
	GPIO_PORTC_BASE,
	GPIO_PORTD_BASE,
	GPIO_PORTE_BASE,
	GPIO_PORTF_BASE

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
Dio_LevelType Dio_ReadChannel(Dio_PortType Port,Dio_ChannelType Channel){
	
	volatile uint32* Curr_GPIO_Addr=(volatile uint32*)GPIO_Port_Base_Addr[Port];
	uint32 channel_Offset=1U<<Channel;	
	uint32 reading= *(Curr_GPIO_Addr+channel_Offset);
	Dio_LevelType level= (Dio_LevelType)(reading >>Channel);
	return level;
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType Port){
	
	volatile uint32* Curr_GPIO_Addr=(volatile uint32*) GPIO_Port_Base_Addr[Port];
	uint8 reading= (uint8)(*(Curr_GPIO_Addr+USE_ALL_PINS/4));
	Dio_PortLevelType portLevel= reading;
	return portLevel;
}

void Dio_WriteChannel(Dio_PortType Port,Dio_ChannelType Channel,Dio_LevelType ChannelLevel){

	volatile uint32* Curr_GPIO_Addr=(volatile uint32*) GPIO_Port_Base_Addr[Port];
	uint32 channel_Offset=1U<<Channel;	
	*(Curr_GPIO_Addr+channel_Offset)= (uint32)ChannelLevel<<Channel;
	return;

}
void Dio_WritePort(Dio_PortType Port,Dio_PortLevelType PortLevel){

	volatile uint32* Curr_GPIO_Addr=(volatile uint32*) GPIO_Port_Base_Addr[Port];
	*(Curr_GPIO_Addr+USE_ALL_PINS/4)= (uint32)PortLevel;
	return;

}
void Dio_FlipChannel(Dio_PortType Port,Dio_ChannelType Channel){

	if(Dio_ReadChannel(Port,Channel)==CHANNEL_HIGH){
		Dio_WriteChannel(Port,Channel,CHANNEL_LOW);
	}
	else{
		Dio_WriteChannel(Port,Channel,CHANNEL_HIGH);
}
return;
}



/**********************************************************************************************************************
 *  END OF FILE: GPIO_Dio.c
 *********************************************************************************************************************/
