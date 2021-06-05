#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"


void SystemInit(){}
	void init (void){
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R5& 0x20)== 0x00) //for checking if port F is connected to clock
	{
		
	}
	GPIO_PORTF_LOCK_R = 0x4C4F434F;
	GPIO_PORTF_CR_R = 0x02;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DIR_R = 0x02;
	GPIO_PORTF_DEN_R = 0x02; 
	
	

	
	}
	int main () {
		int x = 105 ;// ditance > 100 so red led turns on (pf1), in second milestone, x will be a variable
		init();
	while (1){
		if ( x >= 100){

		GPIO_PORTF_DATA_R |=0x02;
		}
		}
	
	}
