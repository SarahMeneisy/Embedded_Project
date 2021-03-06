#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
void SystemInit(){};
void UART_inti(void);
int main(){
		 
 	
	}
 
void UART_inti( )
	{  
		 
    GPIO_PORTA_LOCK_R =0x4C4F434B;  
    GPIO_PORTA_CR_R = 0x01;  		    //unlock portA0
		SYSCTL_RCGCUART_R  |= 0x1;      //Activate UART0  (port A)
		SYSCTL_RCGCGPIO_R  |=0X01;      //Activate port A
	 
		UART0_CTL_R =0;                 //Disable UART
		UART0_IBRD_R =104;              //IBRD = int(16000000/(16*9600))=int(104.167);
		UART0_FBRD_R =11;               //FBRD =round(0.167*64)=round(10.688)
		UART0_LCRH_R =0X70;             // Enable FIFO , 8-bit length
		UART0_CTL_R =0X201;             // Enable UART, RXE
		
		GPIO_PORTA_AFSEL_R =0x1;        //Alternative function for A0 
		GPIO_PORTA_PCTL_R =0x1;         //Unable UART for pin A0
		GPIO_PORTA_AMSEL_R =0;          //Disable Analog
		GPIO_PORTA_DIR_R =0;            //DIR = input
		GPIO_PORTA_DEN_R =0x01;         //A0 is Digital
		GPIO_PORTA_PUR_R =0X0;          //Disable pull up 
	 
 	
	}
           