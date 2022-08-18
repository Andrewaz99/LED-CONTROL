/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
 #include "Platform_Types.h"
 #include "IntCtrl.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
// number of used interrupts in this driver
#define INTCTRL_NO_OF_INTERRUPTS					2
// select priorty grouping split 
// select from tm4c123gh6pm.h 
// 3.5 split corresponds to xxx.yyyyy binary split
// which corresponds to xxx in PRIGROUP bitfield in APINT (8 groups 1 sungroup) in our aplication

#define PRIORTYSELECTED										NVIC_APINT_PRIGROUP_3_5 


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 typedef struct {
	uint32 vectInterruptNo; 
	uint32 enableDisable ;
	uint32 priortySubpriorty;	 
 }INTERRUPT_INFO;
 
  typedef struct {
	uint32 vectInterruptNo; 
	uint32 enableDisable;
	uint32 priortySubpriorty;
	volatile uint32* priortyRegister;
	uint32 priortyShift;
	uint32 sysHndCtrlShift;
 }SYSHNDCTRL_INFO;
 
extern  INTERRUPT_INFO enabledInterrupts[INTCTRL_NO_OF_INTERRUPTS];
extern  SYSHNDCTRL_INFO systemHandlers[PROG_SYS_HANDLERS_NO];
 

 
#endif  /* INTCTRL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Cfg.h
 *********************************************************************************************************************/
