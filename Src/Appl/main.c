#include "GPT.h"
#include "GPT_Cfg.h"
#include "IntCtrl.h"
#include "GPIO_Dio.h"
#include "GPIO_Port.h"
#include "Mcu_Hw.h"
void LED_Blink(float32 TimeOn, float32 TimeOff);
void WTimer0A_notification(void);

void WTimer0A_notification(void){
	
	//  check the ISR entry flag(match or timeout)
	
	if(ACCESS_REG(WIDE_TIMER0_BASE,GPTMMIS) & 1U<<GPTMIMR_TAMIM){
	
			// clear intterupt and turn LED on
		ACCESS_REG(WIDE_TIMER0_BASE,GPTMICR)|= 1U<<GPTMMIS_TAMIMIS;
		
		Dio_WriteChannel(PORT_F,CHANNEL1,CHANNEL_HIGH);
	}
		
	else if(ACCESS_REG(WIDE_TIMER0_BASE,GPTMMIS) & 1U<<GPTMIMR_TATOIM){
		
		// clear intterupt and turn LED off
		ACCESS_REG(WIDE_TIMER0_BASE,GPTMICR)|= 1U<<GPTMMIS_TATOMIS;
		
		Dio_WriteChannel(PORT_F,CHANNEL1,CHANNEL_LOW);
		
	}

}


void LED_Blink(float32 TimeOn, float32 TimeOff){
	uint32 onticks,offticks;
	onticks=(uint32)(TimeOn*WIDE_TIMER0_FREQ);
	offticks=(uint32)(TimeOff*WIDE_TIMER0_FREQ);
	
	//set the callback function for WIDE_TIMER0A
	GPT_Notification_Register(&WTimer0A_notification,WIDE_TIMER0); 
	
	// enable interrupts from timeout and match
	GPT_EnableNotificationWithMatch(WIDE_TIMER0);
  
	//start timer with match register initialzed
	GPT_StartTimerWithMatch(WIDE_TIMER0,onticks+offticks,offticks);  
	
}

int main(){
	IntCrtl_Init();	//initialize the NVIC module 
	Port_Init();		//initialize the GPIO pins used in the config files
	GPT_Init();			//initialize	the used GPTs
	
	// LED on and off time in seconds
	float32 OnTime=3;	
	float32 OffTime=1;
	LED_Blink(OnTime,OffTime); // start LED blinking
	
while(1){
}


}
