#include "math.h"
#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <string.h>

void SystemInit(){};
void GPS_Read(double* lat , double* lon);
int R_isEmpty(void);	 
	

int main(void){
	 
 
	
}
 
 
	int R_isEmpty(){
		return (int)(UART0_FR_R &=0x10);
	
}
	void GPS_Read(double* lat , double* lon){
		char DS,a,a1,a2,a3,a4,a5,a6 ,gValues[100],pValue[10][20],*loc;
		const char com[2] =",";
		double Latitude,Longitude,LatitudeResult,LongitudeResult;
		int in=0,res1,res2;
		 
		while (R_isEmpty()){};
		DS = UART0_DR_R;
			if (DS=='$')
			{
				while (R_isEmpty()){};
					
				  a =UART0_DR_R;
					
				if (a=='G')
				{
					while (R_isEmpty()){};
					
					  a1 =UART0_DR_R;
					
						if (a1=='P')
						{
							while (R_isEmpty()){};
					
					     a2 =UART0_DR_R;
							
							if (a2=='G')
							{
								while (R_isEmpty()){};
					
					       a3 =UART0_DR_R;
								
							
							  if (a3 =='L')
							  {
								while (R_isEmpty()){};
					
					       a4 =UART0_DR_R;
									
									if (a4 =='L')
							    {
								  while (R_isEmpty()){};
					
					         a5 =UART0_DR_R;
									
									  if (a5 ==',')
						      	{
								    while (R_isEmpty()){};
					
					           a6 =UART0_DR_R;
									
								    	while (a6 !='*')
						        	{
												 gValues[in]=a6; 	
								      while (R_isEmpty()){};
					        	
					              a6 =UART0_DR_R;			 
									    in++;
							        }
											
											in=0;
											loc = strtok(gValues, com);
											 while( loc != NULL ) {
                       strcpy(pValue[in], loc);
                       loc = strtok(NULL, com );
                       in++;
											 }
											 
											 Latitude =atof(pValue[0]); 
											 res1 = (int)(Latitude/100);
											 res2 =Latitude-(res1*100);
											 LatitudeResult = res1 + (res2/60);
											 
											  *lat= LatitudeResult;
											 
											 Longitude =atof(pValue[2]);
											  res1 = (int)(Longitude/100);
											 res2 =Longitude-(res1*100);
											 LongitudeResult = res1 + (res2/60);
											 
											 *lon=  LongitudeResult;
							 
											
							      }		
					     		 }	
							    }		
							   }				
					   	  }
					   	}			
		     		}
				
					}