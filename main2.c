#include "math.h"
#include "stdint.h"
#include <ctype.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <string.h>
#include "stdlib.h"
#include <stdbool.h>
#include <stdio.h>


void SystemInit(){};
void UART5_inti(void);
char UART5_read(void);
int GPS_Read(double* time ,double* lat , double* lon);
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
void prepare_LCD(void);
double toRadians( double x);
double distResult(  double x1,   double  y1,
                                 double  x2,   double y2);
void displayDistance(int number,int len);
void displayTime(int number,int len);
double atof(const char *s);
int main(void){
    double *lat1,*lon1, *lat2, *lon2, *time1, *time2,x1=0,x2=0,y1=0,y2=0,timeDif=0,d;
        double res,t1,t2,total=0,e1=0,e2=0,e3=0,e4=0,e5=0,e6=0;
        char*a ="distance: ";
        char*c ="Time: ";
        int re,ftime,fdis;


        LCD_init();
        init();
        UART5_inti();
        prepare_LCD();

        //Initializing the pointers
        lat1=&e1;
        lat2=&e2;
        lon1=&e3;
        lon2=&e4;
        time1=&e5;
        time2=&e6;

        re=GPS_Read(time1 ,lat1,lon1);
        delayMs(4000);
        re=GPS_Read(time2 ,lat2,lon2);

        //assigning the values of the pointers
        x1=*(lat1);
        x2=*(lat2);
        y1=*(lon1);
        y2=*(lon1);
        t1=*(time1);
        t2=*(time2);

        res =distResult(x1,y1,x2,y2);

        while (total <100){

            //calculating the Distance and Time taken
            d = t2-t1;
            timeDif += d;
            total +=res;
            ftime =(int) timeDif;
            fdis =(int) res;

            //Displaying both Distance and Time
            Write_LCD(a ,10);
            displayDistance(fdis,3);

            sLine_LCD();
            delayMs (1);

            Write_LCD(c ,6);
            displayTime(ftime,6);

            //update the data
            re=GPS_Read(time1 ,lat1,lon1);
            x1=*(lat1);
            x2=*(lat2);
            res =distResult(x2,y2,x1,y1);//100
            x2=x1;
            y2=y1;


        }
       //illuminate the led when the distance reach 100 m
       GPIO_PORTF_DATA_R |=0x02;



 }
void UART5_inti(void){


      SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock
      SYSCTL_RCGCUART_R|= SYSCTL_RCGCUART_R5;//UART Module 5 Run Mode Clock

          GPIO_PORTE_LOCK_R=0x4C4F434B;
          GPIO_PORTE_CR_R|=0x30;
          GPIO_PORTE_CR_R|=0x30;             //unlock pinE4,pinE5
          GPIO_PORTE_AFSEL_R|=0x30;          //Alternative function for pinE4,pinE5
          GPIO_PORTE_PCTL_R=0x0011000;            //Unable UART for pinE4,pinE5
          GPIO_PORTE_DEN_R|=0x30;            //pinE4,pinE5 is Digital
          GPIO_PORTE_AMSEL_R =0;             //Disable Analog
          GPIO_PORTE_DIR_R =0x10;             //pinE4 is input

          UART5_CTL_R &= ~UART_CTL_UARTEN;
          UART5_FBRD_R=11;                 //FBRD =round(0.167*64)=round(10.688)
          UART5_IBRD_R=104;                //IBRD = int(16000000/(16*9600))=int(104.167);
          UART5_CC_R = UART_CC_CS_SYSCLK;
          UART5_LCRH_R=(UART_LCRH_WLEN_8|UART_LCRH_FEN); // Enable FIFO , 8-bit length
          UART5_CTL_R|=(UART_CTL_UARTEN | UART_CTL_RXE|UART_CTL_TXE); // Enable UART, RXE,TXE

}

char UART5_read(void){
    while((UART5_FR_R &0x10) !=0);  //wait until RX buffer is not full
    return (unsigned char) (UART5_DR_R&0xFF);
}

int GPS_Read(double* time ,double* lat , double* lon){

            char DS,a,a1,a2,a3,a4,a5,a6 ,gValues[100],pValue[10][20],*loc;

            const char com[2] =",";

            double Latitude,Longitude,LatitudeResult,LongitudeResult,signlat,signlon;

            int in=0,res1,res2;

            while(1){

            DS = UART5_read();

                if (DS=='$')
                { a =UART5_read();

                    if (a=='G')
                    { a1 =UART5_read();

                          if (a1=='P')
                          {  a2 =UART5_read();

                               if (a2=='R')
                               {  a3 =UART5_read();

                                  if (a3 =='M')
                                  { a4 =UART5_read();

                                      if (a4 =='C')
                                    {  a5 =UART5_read();

                                         if (a5 ==',')

                                    {  a6 =UART5_read();

                                         while (a6 !='*')

                                        {  gValues[in]=a6;
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
                                                 if (strcmp(pValue[1],"A")==0){
                                                 *time = atof(pValue[0]);

                                                 Latitude =atof(pValue[2]);
                                                 res1 = (int)(Latitude/100);
                                                 res2 =Latitude-(res1*100);
                                                 LatitudeResult = res1 + (res2/60);
                                                 if (strcmp(pValue[3],"S")==0) signlat *=-1;
                                                 *lat=(LatitudeResult*signlat);;

                                                 Longitude =atof(pValue[4]);
                                                 res1 = (int)(Longitude/100);
                                                 res2 =Longitude-(res1*100);
                                                 LongitudeResult = res1 + (res2/60);
                                                 if ( strcmp(pValue[5],"W")==0 ) signlon*=-1;
                                                 *lon=( LongitudeResult*signlon) ;
                                                return 1;

                                    }}}}}}}}}}
void displayTime(int number,int len){

        char b;

         int n=1,i,j,v;

         for (j=0 ;j<len-1 ;j++){

                        n *=10;
                        }

         for ( i=0 ;i<len+2 ;i++){
         if (i==2 ||i==5)  {
         LCD_data (':');
         delayMs (1);
         inCurs_LCD();
         }
         else{
         v=(number/n);
         b=v +'0';
         LCD_data (b);
         delayMs (1);
         inCurs_LCD();
         number  = number-( v*n) ;
         n=n/10;}

         }

}

void displayDistance(int number,int len)
{

    char b;
     int n=1,i,j,v;
     for (j=0 ;j<len-1 ;j++){
                    n *=10;
                    }

    for ( i=0 ;i<len ;i++){
    v=(number/n);
    b=v +'0';
    LCD_data (b);
    delayMs (1);
    inCurs_LCD();
    number  = number-   v*n ;
    n=n/10;}


}

    void init (void){

        SYSCTL_RCGCGPIO_R |= 0x20;

        while((SYSCTL_PRGPIO_R5& 0x20)== 0x00)  //for checking if port F is connected to clock
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

          void clear_LCD(void){
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
          void prepare_LCD(void){
              clear_LCD();
              fLine_LCD();
              rCurs_LCD();
              delayMs (500);

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
                result = result * Raduis*1000 ;// to covert it from Km to meters
                return result;

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
