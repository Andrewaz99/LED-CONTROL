/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
// #include "TM4C123GH6PM.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



	

#define MCU_CLOCK_FREQ													16000000U

// architecture word size for this microcontroller TM$C123GH6PM
#define WORD_SIZE 															4U
// interrupt priorty levels
#define PRI_LEVEL0															0U
#define PRI_LEVEL1															1U
#define PRI_LEVEL2															2U
#define PRI_LEVEL3															3U
#define PRI_LEVEL4															4U
#define PRI_LEVEL5															5U
#define PRI_LEVEL6															6U
#define PRI_LEVEL7															7U


/**************************************
GPIO base addresses and offser
***************************************/
// GPIO port bases
#define GPIO_PORTA_BASE  0x40004000
#define GPIO_PORTB_BASE  0x40005000
#define GPIO_PORTC_BASE  0x40006000
#define GPIO_PORTD_BASE  0x40007000
#define GPIO_PORTE_BASE  0x40024000
#define GPIO_PORTF_BASE  0x40025000
	
//GPIO registers offset from base
#define GPIODATA     			0x3FC 
#define GPIODIR        		0x400 
#define GPIOAFSEL      		0x420 
#define GPIODR2R        	0x500 
#define GPIODR4R        	0x504 
#define GPIODR8R        	0x508 
#define GPIOODR         	0x50C 
#define GPIOPUR         	0x510 
#define GPIOPDR         	0x514 
#define GPIOSLR         	0x518 
#define GPIODEN         	0x51C 
#define GPIOLOCK        	0x520 
#define GPIOCR          	0x524 
#define GPIOAMSEL 				0x528
#define GPIOPCTL        	0x52C 

/**************************************
System Control Module base addresses and offsets
***************************************/
#define SYSCTL_BASE							0x400FE000	//base of system control module
#define SYSCTL_RCGC_BASE				0x400FE600 // base of run mode clock gating control registers
#define SYSCTL_PR_BASE					0x400FEA00 // base of peripheral ready registers

// offset from base adresses 
#define SYSCTL_GPTM_OFFSET						0x4
#define SYSCTL_GPIO_OFFSET						0x8
#define SYSCTL_WIDE_GPTM_OFFSET				0x5C



/**************************************
GPTM base addresses and offsets
***************************************/
#define TIMER0_BASE						0x40030000
#define	TIMER1_BASE						0x40031000
#define	TIMER2_BASE						0x40032000
#define	TIMER3_BASE						0x40033000
#define	TIMER4_BASE						0x40034000
#define	TIMER5_BASE						0x40035000
#define	WIDE_TIMER0_BASE			0x40036000
#define	WIDE_TIMER1_BASE			0x40037000
#define	WIDE_TIMER2_BASE			0x4004C000
#define	WIDE_TIMER3_BASE			0x4004D000
#define	WIDE_TIMER4_BASE			0x4004E000
#define	WIDE_TIMER5_BASE			0x4004F000

// Offsets from base addresses
#define GPTMCFG					0x000
#define GPTMTAMR				0x004
#define GPTMTBMR				0x008
#define GPTMCTL					0x00C
#define GPTMIMR					0x018
#define GPTMRIS					0x01C
#define GPTMMIS					0x020
#define GPTMICR					0x024
#define GPTMTAILR				0x028
#define GPTMTBILR				0x02C
#define GPTMTAMATCHR		0x030
#define GPTMTAR					0x048
#define GPTMTAV					0x050


/**************************************
NVIC base addresses and offsets
***************************************/
#define CORTEXM4_PERI_BASE_ADDRESS             		0xE000E000
#define NVIC_PRI_BASE             								0xE000E400 
#define NVIC_EN_BASE															0xE000E100 
#define NVIC_APINT                                0xD0C






/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define ACCESS_REG(Base,Offset)		*((volatile uint32*)(Base+Offset))

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
void TIMER0A_Handler(void);
void WTIMER0A_Handler(void);


 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
