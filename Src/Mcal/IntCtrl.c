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
* \Description     : initialize NVIC Module by passing the Configuration 
*                    into NVIC registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void)
{
	
	// vectkey is used to enable writing to APINT and PRIGROUP bit field  to set the priorty split

	ACCESS_REG(CORTEXM4_PERI_BASE_ADDRESS,NVIC_APINT) = (NVIC_APINT_VECTKEY|PRIORTYSELECTED);
    
	//Assign group\subgroup priority inNVIC_PRIx and enables/disables interrupts in NVIC_ENx   */
	for(uint8 i=0;i<INTCTRL_NO_OF_INTERRUPTS;i++){
		// calculate IRQ number
		uint32 interruptNum=enabledInterrupts[i].vectInterruptNo-16;
		// calculate which priorty register in NVIC
		uint32 priortyRegisterCalc=interruptNum/INTERRUPTS_PER_PROIRTY_REG;
		
		uint32 priortyField=interruptNum%INTERRUPTS_PER_PROIRTY_REG;
		
		ACCESS_REG(NVIC_PRI_BASE,priortyRegisterCalc*WORD_LENGTH_BYTES)|=(uint32)(enabledInterrupts[i].priortySubpriorty<<(( 5U + (8U*priortyField) )));
		
		// calculate which enable register in NVIC
		uint32 enableRegisterCalc = interruptNum/INTERRUPTS_PER_ENABLE_REG;
		
		uint8 enableField = interruptNum%INTERRUPTS_PER_ENABLE_REG;	
		
		ACCESS_REG(NVIC_EN_BASE,enableRegisterCalc*WORD_LENGTH_BYTES)|= (1U<<enableField);
	}
	}
/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
