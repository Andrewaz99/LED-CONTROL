/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl_Lcfg.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"
#include "TM4C123GH6PM.h"
#include "IntCtrl.h"
#include "IntCtrl_Types.h"
#include "Mcu_Hw.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

INTERRUPT_INFO enabledInterrupts[INTCTRL_NO_OF_INTERRUPTS]={
{INT_TIMER0A , ENABLE, PRI_LEVEL1},
{INT_WTIMER0A , ENABLE, PRI_LEVEL1}	
};

SYSHNDCTRL_INFO systemHandlers[PROG_SYS_HANDLERS_NO]={
	
	// intialization of the 7 programmable system handlers
//{system handler no. in vector table,enable/disable,priorty level ,shift in corresponding priorty register,shift in NVIC_SYS_HND_CTRL_R }	
{MEM_MAN_FAULT_NO ,DISABLE ,PRI_LEVEL0 ,SYS_PRI1 ,NVIC_SYS_PRI1_MEM_S ,SYS_HND_CTRL_MEM_SHIFT},
 
{BUS_FAULT_NO ,DISABLE ,PRI_LEVEL0 ,SYS_PRI1 ,NVIC_SYS_PRI1_BUS_S ,SYS_HND_CTRL_BUS_SHIFT},

{USAGE_FAULT_NO ,DISABLE ,PRI_LEVEL4 ,SYS_PRI1 ,NVIC_SYS_PRI1_USAGE_S ,SYS_HND_CTRL_USAGE_SHIFT},

{SVC_NO ,DISABLE ,PRI_LEVEL0 ,SYS_PRI3 ,NVIC_SYS_PRI2_SVC_S ,SYS_HND_CTRL_SVC_SHIFT},

{DEBUG_MON_NO ,DISABLE ,PRI_LEVEL0 ,SYS_PRI3 ,NVIC_SYS_PRI3_DEBUG_S ,SYS_HND_CTRL_MON_SHIFT},

{PEND_SV_NO ,DISABLE ,PRI_LEVEL1 ,SYS_PRI3 ,NVIC_SYS_PRI3_PENDSV_S ,SYS_HND_CTRL_PNDSV_SHIFT},

{SYSTICK_NO ,DISABLE ,PRI_LEVEL2 ,SYS_PRI3 ,NVIC_SYS_PRI3_TICK_S ,SYS_HND_CTRL_TICK_SHIFT }

};
	

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
