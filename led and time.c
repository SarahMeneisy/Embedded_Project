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





          char* displayTime(char arr[],int n){

              int i,j=0;

              char* s;

              for(i=0;i<n+2 ;i++){

                  if (i==2 || i==5)

                  s[i]=':';

                  else

                  {

                   s[i]=arr[j]  ;

                   j++;

                  }



              }

              return s;



          }
