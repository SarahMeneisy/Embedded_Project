#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "math.h"
#include <string.h>

int main(void){
	 
 
	
	long double res,total=0; 
	double *lat1,*lon1,*lat2,*lon2;
	double distance;
	  char*a;
	  char out[16];
    int i;
    int t;
	
		LCD_init();
	  UART_inti();
	  init();
	 
	
	while (total <100){
 	
	GPS_Read(lat1,lon1);
		delayMs(1000);	
	GPS_Read(lat2,lon2);

	res =distResult(*lat1,*lon1,*lat2,*lon2);
		
		total +=res;
	
	 if (total >= 100.0 ){          
		 
		 distance = ((double) res); 

  snprintf(out, 16, "%f", distance);
	
	
	 
	 while(1){
		if ( res >= 100){

		GPIO_PORTF_DATA_R |=0x02;
		}
	  
        clear_LCD();
        fLine_LCD();
        rCurs_LCD();
        delayMs (500);


        for ( t=0 ; t<15 ; t++)
        {
        LCD_data(a[t]);
        delayMs (1);
        inCurs_LCD();
        
        }

        sLine_LCD();
         



        for (  i=0 ; i<15 ;i++)
        {
        LCD_data(out[t]);
        delayMs (1);
        inCurs_LCD();
         
        }
		}
	 
	 }
 
	}
	
	
	
	
	
}
