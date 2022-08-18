/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl.h"
#include "Mcu_Hw.h"
#include "IntCtrl_Cfg.h"
#include "TM4C123GH6PM.h"
#include "IntCtrl_Types.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void)
{
	
	// vectkey is used to enable writing to APINT and PRIGROUP bit field  to G3.S1 split (first 4 bits unused)
    APINT = (NVIC_APINT_VECTKEY|PRIORTYSELECTED);
    
    // Assign group\subgroup priority in SCB_SYSPRIx Registers and enables/disables system handlers in SCB_Sys Registers */  
	
	for(uint8 j=0;j<PROG_SYS_HANDLERS_NO;j++){
		*(systemHandlers[j].priortyRegister)|= systemHandlers[j].priortySubpriorty <<systemHandlers[j].priortyShift;
		NVIC_SYS_HND_CTRL_R|= systemHandlers[j].enableDisable <<systemHandlers[j].sysHndCtrlShift;
	}
	//Assign group\subgroup priority inNVIC_PRIx and enables/disables interrupts in NVIC_ENx   */
	for(uint8 i=0;i<INTCTRL_NO_OF_INTERRUPTS;i++){
		uint32 interruptNum=enabledInterrupts[i].vectInterruptNo-16;
		uint32 priortyRegisterCalc=interruptNum/4;
		uint32 priortyField=interruptNum%4;
		*(NVIC_PRI_BASE+priortyRegisterCalc) |=(uint32)(enabledInterrupts[i].priortySubpriorty<<((uint8) 5 + (uint8)(8*priortyField) ));
		uint32 enableRegisterCalc = interruptNum/32;
		uint8 enableField = interruptNum%32;	
		*(NVIC_EN_BASE+enableRegisterCalc)|= (1U<<enableField);
	}
	}
/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
