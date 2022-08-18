/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_Port_Types.h
 *       Module:  GPIO_Port
 *
 *  Description:  <>     
 *  
 *********************************************************************************************************************/
#ifndef GPIO_PORT_TYPES_H
#define GPIO_PORT_TYPES_H

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
		PIN0,
		PIN1,
		PIN2,
		PIN3,
		PIN4,
		PIN5,
		PIN6,
		PIN7
		}Port_PinType;
	
	typedef enum{
		PORTA,
		PORTB,
		PORTC,
		PORTD,
		PORTE,
		PORTF
		}Port_PortType;
typedef enum{
	INPUT,
	OUTPUT
}Port_PinDirectionType; 

typedef enum{
	PDR,
	PUR,
	OD
}Port_PinInternalAttachType; 

typedef enum{
	OUT_2mA,
	OUT_4mA,
	OUT_8mA
	
}Port_PinOutputCurrentType; 

typedef uint8 Port_PinModeType;

	typedef enum{
		 PIN_LOW,
		 PIN_HIGH
		}Port_PinLevelType;
	
	typedef enum{
		 DIGITAL,
		 ANALOG
		}Port_DataType;

		
typedef struct {
Port_PortType portNo;
Port_PinType pinNo;
Port_PinDirectionType pinDir;
Port_PinInternalAttachType pinAttach;
Port_PinModeType pinMode;
Port_PinOutputCurrentType pinOutCurrent;
	Port_DataType pinDataType;
}Port_ConfigType;
 
#endif  /* GPIO_PORT */

/**********************************************************************************************************************
 *  END OF FILE: GPIO_Port_Types.h
 *********************************************************************************************************************/
