/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GPIO_Port.c
 *        \brief  GPIO Port Driver
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
#include "GPIO_Port.h"
#include "GPIO_Port_Types.h"
#include "GPIO_Port_Cfg.h"
#include "TM4C123GH6PM.h"

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
void Port_Init (void){

for(int i=0; i<GPIO_PORT_NO_OF_PINS_USED;i++){
	uint32 currPortBase=GPIO_Port_Base_Addr[InitializedPins[i].portNo];
	uint32 pinVal=1U<<InitializedPins[i].pinNo;
	
	
		//connect clock to port if not connected
	uint32 checkClock=(1U<<InitializedPins[i].portNo) & ACCESS_REG(SYSCTL_RCGC_BASE,SYSCTL_GPIO_OFFSET);
	if(checkClock==0){
	ACCESS_REG(SYSCTL_RCGC_BASE,SYSCTL_GPIO_OFFSET)|=(1U<<InitializedPins[i].portNo);
		while(!(ACCESS_REG(SYSCTL_PR_BASE,SYSCTL_GPIO_OFFSET)   &   1U<<InitializedPins[i].portNo)  ){}
	}
	
	//if the pin to be initialized is uncommited, it should be commited to enable adjustments of certain registers
	uint32 commitOfPin=(ACCESS_REG(currPortBase,GPIOCR)&(pinVal));
	if(commitOfPin==0){
	ACCESS_REG(currPortBase,GPIOLOCK)=GPIO_UNLOCK_KEY;
	ACCESS_REG(currPortBase,GPIOCR)|= pinVal;
	}
	
	// set pin direction 
	ACCESS_REG(currPortBase,GPIODIR)|=(uint32)(InitializedPins[i].pinDir)<<InitializedPins[i].pinNo;
	
	
	//set internal attachment of pin
	if(InitializedPins[i].pinAttach==PUR){
	ACCESS_REG(currPortBase,GPIOPUR)|=pinVal;
	}
	else if(InitializedPins[i].pinAttach==PDR){
	ACCESS_REG(currPortBase,GPIOPDR)|=pinVal;
	}
	else if (InitializedPins[i].pinAttach==OD){
	ACCESS_REG(currPortBase,GPIOODR)|=pinVal;
	}
	// set pin mode 
	if( InitializedPins[i].pinMode != PORT_PIN_MODE_DIO){
	ACCESS_REG(currPortBase,GPIOAFSEL)|=pinVal;
	ACCESS_REG(currPortBase,GPIOPCTL)|=	(uint32)(InitializedPins[i].pinMode)<<(InitializedPins[i].pinNo*PMC_SIZE);	
	}
	
	//set pin out current
	
	/*if (InitializedPins[i].pinOutCurrent==OUT_2mA){
	ACCESS_REG(currPortBase,GPIODR2R)|=pinVal;
	}
	else*/
		if(InitializedPins[i].pinOutCurrent==OUT_4mA){
		ACCESS_REG(currPortBase,GPIODR4R)|=pinVal;
	}
	else if(InitializedPins[i].pinOutCurrent==OUT_8mA){
		ACCESS_REG(currPortBase,GPIODR8R)|=pinVal;
	}
	if(InitializedPins[i].pinDataType==DIGITAL){
	ACCESS_REG(currPortBase,GPIODEN)|=	pinVal;
	}
	else if(InitializedPins[i].pinDataType==ANALOG){
		ACCESS_REG(currPortBase,GPIOAMSEL)|=	pinVal;
	}

}

}

/**********************************************************************************************************************
 *  END OF FILE: GPIO_Port.c
 *********************************************************************************************************************/
