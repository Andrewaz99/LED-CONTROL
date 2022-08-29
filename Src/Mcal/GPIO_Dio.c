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
* \Syntax          : Dio_LevelType Dio_ReadChannel(Dio_PortType Port,Dio_ChannelType Channel)                                      
* \Description     : read a GPIO pin to know whether it's on or off
*                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Dio_PortType ,Dio_ChannelType                       
* \Parameters (out): Dio_LevelType                                                       
* \Return value:   : CHANNEL_HIGH
										 CHANNEL_LOW
*******************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_PortType Port,Dio_ChannelType Channel){
	
	uint32 Curr_GPIO_Addr=GPIO_Port_Base_Addr[Port];
	
	uint32 channel_Offset=1U<<Channel;	
	
	uint32 reading= ACCESS_REG(Curr_GPIO_Addr,channel_Offset*WORD_LENGTH_BYTES);
	
	Dio_LevelType level= (Dio_LevelType)(reading >>Channel);
	
	return level;
}
/******************************************************************************
* \Syntax          : Dio_PortLevelType Dio_ReadPort(Dio_PortType Port)                                      
* \Description     : read a GPIO port's value 
*                                                      
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Dio_PortType                     
* \Parameters (out): Dio_PortLevelType                                                      
* \Return value:   : Dio_PortLevelType
*******************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType Port){
	
	uint32 Curr_GPIO_Addr=GPIO_Port_Base_Addr[Port];
	Dio_PortLevelType portLevel= (Dio_PortLevelType)ACCESS_REG(Curr_GPIO_Addr,GPIODATA);
	return portLevel;
}
/******************************************************************************
* \Syntax          : void Dio_WriteChannel(Dio_PortType Port,Dio_ChannelType Channel,Dio_LevelType ChannelLevel)                                     
* \Description     : write a HIGH or LOW  to a specific pin
*                                                      
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Dio_PortType ,Dio_ChannelType, Dio_LevelType                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Dio_WriteChannel(Dio_PortType Port,Dio_ChannelType Channel,Dio_LevelType ChannelLevel){

	uint32 Curr_GPIO_Addr=GPIO_Port_Base_Addr[Port];
	uint32 channel_Offset=1U<<Channel;	
	 ACCESS_REG(Curr_GPIO_Addr,channel_Offset*WORD_LENGTH_BYTES)= (uint32)ChannelLevel<<Channel;
	return;

}
/******************************************************************************
* \Syntax          : void Dio_WritePort(Dio_PortType Port,Dio_PortLevelType PortLevel)                                      
* \Description     : write a value to the port (set or clear all pins at once) 
*                                                       
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Dio_PortType , Dio_PortLevelType                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Dio_WritePort(Dio_PortType Port,Dio_PortLevelType PortLevel){

	uint32 Curr_GPIO_Addr=GPIO_Port_Base_Addr[Port];
	ACCESS_REG(Curr_GPIO_Addr,GPIODATA)= (uint32)PortLevel;
	return;

}
/******************************************************************************
* \Syntax          : void Dio_FlipChannel(Dio_PortType Port,Dio_ChannelType Channel)                                      
* \Description     : flip the value of the given pin 
*                                                      
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : Dio_PortType, Dio_ChannelType                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
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
