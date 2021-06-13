#include "math.h"

#include "stdint.h"

#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <string.h>


void SystemInit(){};

int GPS_Read(double* time ,double* lat , double* lon);

void UART5_inti(void);

char UART5_read(void);

void init (void);

void delayUs (int s);

void delayMs (int s);

void LCD_command (unsigned char command);

void LCD_data (unsigned char data );

void LCD_init(void);

void clear_LCD(void);

void rCurs_LCD(void);

void inCurs_LCD(void);

void Display_LCD(void);

void fLine_LCD(void);

void sLine_LCD(void);

void set8_LCD(void);

void wakeUp_LCD(void);

void Write_LCD(char* s,int len);

char* displayTime(char arr[],int n);

 double toRadians( double x);

double distResult(  double x1,   double  y1,

                                 double  x2,   double y2);
char * toArray(int number,int len);
double atof(const char *s);
int main(void)

{



    double res,total=456.57;

    double *lat1,*lon1, *lat2, *lon2, *time1, *time2,x1=0,x2=0,y1=0,y2=0,timeDif=456.78,d;

      char*a ="distance: ";

     char*b ="time: ";

     char* t,*to,*ds;
    int re,ftime,fdis,al;



    LCD_init();

   init();
   UART5_inti();


    while (total <100){


    re=GPS_Read(time1 ,lat1,lon1);

        delayMs(1000);

    re=GPS_Read(time2 ,lat2,lon2);

 x1=*(lat1);

  x2=*(lat2);

  y1=*(lon1);

  y2=*(lon1);





    res =distResult(x1,y1,x2,y2);



    d = time2-time1;

    timeDif += d;

    total +=res;

      ftime =(int) timeDif;
      fdis =(int) total;

      to =toArray(ftime,6);
      ds =toArray(fdis,3);

                 clear_LCD();
                 fLine_LCD();
                 rCurs_LCD();
                 delayMs (500);


                 Write_LCD(a ,10);
                 Write_LCD(ds ,3);

                    sLine_LCD();

                    delayMs (1);

                    Write_LCD(b ,6);

    }

    GPIO_PORTF_DATA_R |=0x02;



}

void UART5_inti(void){

    SYSCTL_RCGCUART_R |= 0x02;
      while((SYSCTL_PRUART_R & 0x02) == 0);
      SYSCTL_RCGCGPIO_R |= 0x02;
          while((SYSCTL_PRGPIO_R & 0x02) == 0);

      GPIO_PORTE_CR_R |= 0x1F;
      GPIO_PORTE_AMSEL_R &= ~0x1F;
      GPIO_PORTE_AFSEL_R |= 0x30;
      GPIO_PORTE_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFF) | (GPIO_PCTL_PB0_U1RX | GPIO_PCTL_PB1_U1TX);
      GPIO_PORTE_DEN_R |= 0x1F;
      GPIO_PORTE_DIR_R |= 0x1E;
      GPIO_PORTE_DIR_R &= ~0x10;

      UART5_CTL_R &= ~UART_CTL_UARTEN;
      //set buad rate devider
      UART5_IBRD_R = 104;
      UART5_FBRD_R = 11;
        UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
      UART5_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);

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

                                                 //lat= &la;







                                                 Longitude =atof(pValue[4]);

                                                  res1 = (int)(Longitude/100);

                                                 res2 =Longitude-(res1*100);

                                                 LongitudeResult = res1 + (res2/60);



                                                 y = pValue[5][0];

                                                 if ( y =='W' ) signlon*=-1;

                                                 *lon=( LongitudeResult*signlon) ;

                                                 //lon = &lo ;





                                                return 1;



                                    }}}}}}}}}}

char * toArray(int number,int len)
{
    char* numberArray;

     int n;
     n=10*len;
      int  i;
     for ( i=0 ;i<len ;i++){


         numberArray[i]=number/n +'0';
         n=n/10;
     }
    return numberArray;
}

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

    void delayUs (int s ){

        int i,j;

           for( i=0;i<s  ;i++){

               for( j=0; j<3 ;j++){}

               }

    }

    void delayMs (int s){



        int i,j;

        for( i=0;i<s ;i++){

            for( j=0; j<3180 ;j++){}

            }

    }

            void LCD_init (void)

            {



                SYSCTL_RCGCGPIO_R |=0x03;



                GPIO_PORTB_DIR_R   =0XFF;

                GPIO_PORTB_DEN_R   =0xFF;

                GPIO_PORTB_AFSEL_R =0;

                GPIO_PORTB_PCTL_R  =0;

                GPIO_PORTB_AMSEL_R =0;





                GPIO_PORTA_DIR_R   |=0xE0;

                GPIO_PORTA_DEN_R   |=0xE0;

                GPIO_PORTA_AFSEL_R &=0x1F;

                GPIO_PORTA_PCTL_R  &=0x1F;

                GPIO_PORTA_AMSEL_R &=0x1F;

            }

             void LCD_command (unsigned char com)

             {

                 GPIO_PORTA_DATA_R &=0x1F;

                 GPIO_PORTB_DATA_R  =com;

                 GPIO_PORTA_DATA_R |=0x80;

                 delayUs(0);

                 GPIO_PORTA_DATA_R &= 0x7F;



                 if(com <4){

                     delayMs(2);

                 }

                 else

                 {

                     delayMs(37);

                 }

             }

          void LCD_data (unsigned char data )

             {

                 GPIO_PORTA_DATA_R |=0x20;

                 GPIO_PORTB_DATA_R  =data;

                 GPIO_PORTA_DATA_R |=0x80;

                 delayUs(0);

                 GPIO_PORTA_DATA_R &=0x7F;

             }

          void clear_LCD(void)

          {

              LCD_command(0x01);



          }

          void rCurs_LCD(void){

              LCD_command(0x02);

          }

          void inCurs_LCD(void){

              LCD_command(0x06);

          }

          void Display_LCD(void){

              LCD_command(0x0F);

          }

          void fLine_LCD(void){

              LCD_command(0x80);

          }

          void sLine_LCD(void){

              LCD_command(0xC0);

          }

          void set8_LCD(void){



              LCD_command(0x38);

          }

          void wakeUp_LCD(void){



              LCD_command(0x30);

          }

          void Write_LCD(char* s,int len){

              int t;

              for ( t=0 ; t<len ; t++)

                    {

                    LCD_data(s[t]);

                    delayMs (1);

                    inCurs_LCD();



                    }





          }



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

            double toRadians( double x){



                const double PI=3.1415;

                double rad= (double)(PI/180);

                return x*rad;



            }

             double distResult(  double x1,   double  y1,

                                  double  x2,   double y2)

            {

                double disY,disX,result,Raduis ;

                x1 = toRadians(x1);

                y1 = toRadians(y1);

                x2 = toRadians(x2);

                y2 = toRadians(y2);



                 disY = y2 - y1;                //distance of longitude

               disX = x2 - x1;                //distance of latitude



                result = pow(sin(disX / 2), 2) +

                                    cos(x1) * cos(x2) *

                                    pow(sin(disY / 2), 2);



                result = 2 * asin(sqrt(result));



                Raduis = 6371;



                result = result * Raduis*1000 ;



                return result;                 // to covert it from Km to meters

            }

             double atof(const char *s)
             {
             double a = 0.0;
             int e = 0;
             int c;
             while ((c = *s++) != '\0' && isdigit(c)) {
             a = a*10.0 + (c - '0');
             }
             if (c == '.') {
             while ((c = *s++) != '\0' && isdigit(c)) {
             a = a*10.0 + (c - '0');
             e = e-1;
             }
             }
             if (c == 'e' || c == 'E') {
             int sign = 1;
             int i = 0;
             c = *s++;
             if (c == '+')
             c = *s++;
             else if (c == '-') {
             c = *s++;
             sign = -1;
             }
             while (isdigit(c)) {
             i = i*10 + (c - '0');
             c = *s++;
             }
             e += i*sign;
             }
             while (e > 0) {
             a *= 10.0;
             e--;
             }
             while (e < 0) {
             a *= 0.1;
             e++;
             }
             return a;
             }
 
