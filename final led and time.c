
#include "math.h"

#include "stdint.h"

#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <string.h>


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

void displayTime(int number,int len){

        char b;

         int n=1,i,j,v;

         for (j=0 ;j<len-1 ;j++){

                        n *=10 
                        }

                        for ( i=0 ;i<len+2 ;i++){

                            if (i==2 ||i==5)  {
                                LCD_data (':');

                            delayMs (1);

                         inCurs_LCD();
                                                  }
                            else
                            { v=(number/n);
                              b=v +'0';
                             LCD_data (b);
                             delayMs (1);

                              inCurs_LCD();

                            number  = number-   v*n ;
                            n=n/10;
                            }
                            }
