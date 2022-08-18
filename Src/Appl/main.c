#include "GPT.h"
#include "IntCtrl.h"
#include "GPIO_Dio.h"
#include "GPIO_Port.h"



int main(){
	IntCrtl_Init();
	Port_Init();
	GPT_Init();
	GPT_EnableNotification(WIDE_TIMER0);
	GPT_StartTimer(WIDE_TIMER0,1000);
while(1){
int x=5;}


}
