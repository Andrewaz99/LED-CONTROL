/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCrtl.h
 *       Module:  IntCrtl
 *
 *  Description:  header file for IntCrtl Module    
 *  
 *********************************************************************************************************************/
#ifndef IntCrtl_H
#define IntCrtl_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
//#include "IntCtrl_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define NVIC_PRI_BASE             ((volatile uint32 *)0xE000E400) //address of first NVIC priory setting register
#define NVIC_EN_BASE							((volatile uint32 *)0xE000E100) //address of first NVIC enable register
#define SYS_PRI1           				((volatile uint32 *)0xE000ED18) //address of first SCB priorty register
#define SYS_PRI2         					((volatile uint32 *)0xE000ED1C)
#define SYS_PRI3         					((volatile uint32 *)0xE000ED20)

// number of programmable system handlers 
#define PROG_SYS_HANDLERS_NO    		7U

// the vector table number of system handlers
#define MEM_MAN_FAULT_NO						4U
#define BUS_FAULT_NO								5U
#define USAGE_FAULT_NO							6U
#define SVC_NO								      11U
#define DEBUG_MON_NO								12U
#define PEND_SV_NO									14U
#define SYSTICK_NO									15U

// position of each system handler enable bit in NVIC_SYS_HND_CTRL_R register
#define SYS_HND_CTRL_MEM_SHIFT   16U 
#define SYS_HND_CTRL_BUS_SHIFT   17U  
#define SYS_HND_CTRL_USAGE_SHIFT 18U  
#define SYS_HND_CTRL_SVC_SHIFT   15U 
#define SYS_HND_CTRL_MON_SHIFT   8U  
#define SYS_HND_CTRL_PNDSV_SHIFT 10U  
#define SYS_HND_CTRL_TICK_SHIFT  11U  

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
void IntCrtl_Init(void);
 
#endif  /* IntCrtl_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.h
 *********************************************************************************************************************/
