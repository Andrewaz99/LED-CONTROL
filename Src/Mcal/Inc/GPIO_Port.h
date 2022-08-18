/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_Port.h.h
 *       Module:  GPIO_Port.h
 *
 *  Description:  header file for GPIO_Port Module    
 *  
 *********************************************************************************************************************/
#ifndef GPIO_PORT_H
#define GPIO_PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define GPIO_UNLOCK_KEY									0x4C4F434B

#define PORT_PIN_MODE_DIO 							0

//PortF Pin0 alternate modes
#define PF0_PORT_PIN_MODE_U1RTS 				1
#define PF0_PORT_PIN_MODE_SSI1RX 				2
#define PF0_PORT_PIN_MODE_CAN0RX 				3
#define PF0_PORT_PIN_MODE_M1PWM4 				5
#define PF0_PORT_PIN_MODE_PHA0					6
#define PF0_PORT_PIN_MODE_T0CCP0 				7
#define PF0_PORT_PIN_MODE_NMI 					8
#define PF0_PORT_PIN_MODE_C0O 					9

//PortF Pin1 alternate modes
#define PF1_PORT_PIN_MODE_U1CTS 					1
#define PF1_PORT_PIN_MODE_SSI1TX 					2
#define PF1_PORT_PIN_MODE_M1PWM5 					5
#define PF1_PORT_PIN_MODE_PHB0						6
#define PF1_PORT_PIN_MODE_T0CCP1 					7
#define PF1_PORT_PIN_MODE_C1O 						9
#define PF1_PORT_PIN_MODE_TRD1 						14

//PortF Pin2 alternate modes
#define PF2_PORT_PIN_MODE_SSI1CLK 				2
#define PF2_PORT_PIN_MODE_M0FAULT0 				4
#define PF2_PORT_PIN_MODE_M1PWM6					5
#define PF2_PORT_PIN_MODE_T1CCP0 					7
#define PF2_PORT_PIN_MODE_TRD0 						14

//PortF Pin3 alternate modes
#define PF3_PORT_PIN_MODE_SSI1FSS 				2
#define PF3_PORT_PIN_MODE_CAN0TX					3
#define PF3_PORT_PIN_MODE_M1PWM7					5
#define PF3_PORT_PIN_MODE_T1CCP1 					7
#define PF3_PORT_PIN_MODE_TRCLK 					14

//PortF Pin4 alternate modes
#define PF4_PORT_PIN_MODE_M1FAULT0				5
#define PF4_PORT_PIN_MODE_IDX0						5
#define PF4_PORT_PIN_MODE_T2CCP0 					7
#define PF4_PORT_PIN_MODE_USB0EPEN 				8


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
void Port_Init(void);
 
#endif  /* GPIO_PORT_H */

/**********************************************************************************************************************
 *  END OF FILE: GPIO_Port.h
 *********************************************************************************************************************/
