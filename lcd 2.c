#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include <stdint.h>
#include<string.h>
 #define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define LCD_DATA GPIOB
#define LCD_CTRL GPIOA
#define RS = 0X02
#define RW = 0X40
#define EN = 0X80
#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))
#define GPIO_PORTB_DATA_R       (*((volatile uint32_t *)0x400053FC))

void SystemInit(){};
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

int main(void)
{
    LCD_init();


       delayMs(20);
       set8_LCD();
       delayUs(50);
       Display_LCD();
       delayUs(50);
       inCurs_LCD();
       delayUs(50);
       clear_LCD();
       delayMs(5);
       delayMs(20);



        LCD_data('F');
      delayMs (1);
      inCurs_LCD();
        LCD_data('I');
      delayMs (1);
      inCurs_LCD();
        LCD_data('R');
      delayMs (1);
      inCurs_LCD();
        LCD_data('S');
      delayMs (1);
      inCurs_LCD();
        LCD_data('T');
      delayMs (1);
      inCurs_LCD();
        LCD_data(' ');
      delayMs (1);
      inCurs_LCD();
            LCD_data('M');
      delayMs (1);
      inCurs_LCD();
      LCD_data('I');
          delayMs (1);
          inCurs_LCD();
            LCD_data('L');
          delayMs (1);
          inCurs_LCD();
            LCD_data('E');
          delayMs (1);
          inCurs_LCD();
            LCD_data('S');
          delayMs (1);
          inCurs_LCD();
            LCD_data('T');
          delayMs (1);
          inCurs_LCD();
            LCD_data('0');
          delayMs (1);
          inCurs_LCD();
            LCD_data('N');
          delayMs (1);
          inCurs_LCD();
          LCD_data('E');
                 delayMs (1);
                 inCurs_LCD();


      delayMs (500);

}
//                       Write_LCD(buf ,6);
//
//
//
//                       sLine_LCD();
//
//                       delayMs (1);
//
//
//
//                       Write_LCD(b ,6);
//
//                       Write_LCD(buf2 ,8);
//    delayMs(20);
//             set8_LCD();
//             delayUs(50);
//             Display_LCD();
//             delayUs(50);
//             inCurs_LCD();
//             delayUs(50);
//             clear_LCD();
//             delayMs(5);
//             delayMs(20);
////
//////             LCD_data('F');
//////                   delayMs (1);
//////                   inCurs_LCD();
//////                     LCD_data('I');
//////                   delayMs (1);
//////                   inCurs_LCD();
//////                     LCD_data('R');
//////                   delayMs (1);
//////                   inCurs_LCD();
//////                     LCD_data('S');
//////                   delayMs (1);
//////                   inCurs_LCD();
//////                     LCD_data('T');
//////                   delayMs (1);
////
////
//    Write_LCD(a ,10);
//
//    Write_LCD(buf ,6);
//
//
//
//    sLine_LCD();
//
//    delayMs (1);
//
//
//
//    Write_LCD(b ,6);
//
//    Write_LCD(buf2 ,8);
//
//
//
//
//






//    }
//
//    GPIO_PORTF_DATA_R |=0x02;





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
