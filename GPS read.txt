#include "math.h"
#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <string.h>

void SystemInit(){};
void GPS_Read(double* lat , double* lon);
char UART5_read(void); 
	

int main(void){
	 
 
	
}
 
 
	char UART5_read(void){

    while((UART5_FR_R & 0x10) == 0x10);



    return UART5_DR_R & 0xFF;

}
	int GPS_Read(double* time ,double* lat , double* lon){

            char DS,a,a1,a2,a3,a4,a5,a6 ,gValues[100],pValue[10][20],*loc,x,y ;

            const char com[2] =",";

            double Latitude,Longitude,LatitudeResult,LongitudeResult,signlat,signlon,la,lo;

            int in=0,res1,res2;



            while(1){

            DS = UART5_read();

                if (DS=='$')

                {

                      a =UART5_read();

                    if (a=='G')

                    {




                          a1 =UART5_read();



                            if (a1=='P')

                            {





                             a2 =UART5_read();



                                if (a2=='R')

                                {





                               a3 =UART5_read();





                                  if (a3 =='M')

                                  {




                               a4 =UART5_read();



                                        if (a4 =='C')

                                    {





                                 a5 =UART5_read();



                                          if (a5 ==',')

                                    {




                                   a6 =UART5_read();



                                            while (a6 !='*')

                                        {

                                                     gValues[in]=a6;





                                      a6 =UART5_read();

                                            in++;

                                        }



                                                 in=0;

                                                 loc = strtok(gValues, com);

                                                 while( loc != NULL ) {

                                                 strcpy(pValue[in], loc);

                                                 loc = strtok(NULL, com );

                                                 in++;

                                                 }

                                                 if (pValue[1]=='A'){



                                                 *time = atof(pValue[0]);

                                                 Latitude =atof(pValue[2]);

                                                 res1 = (int)(Latitude/100);

                                                 res2 =Latitude-(res1*100);

                                                 LatitudeResult = res1 + (res2/60);



                                                 x = pValue[3][0];

                                                 if ( x =='S' ) signlat *=-1;

                                                 *lat=(LatitudeResult*signlat);;

                                                 







                                                 Longitude =atof(pValue[4]);

                                                  res1 = (int)(Longitude/100);

                                                 res2 =Longitude-(res1*100);

                                                 LongitudeResult = res1 + (res2/60);



                                                 y = pValue[5][0];

                                                 if ( y =='W' ) signlon*=-1;

                                                 *lon=( LongitudeResult*signlon) ;

                                                




                                                return 1;



                                    }}}}}}}}}}
