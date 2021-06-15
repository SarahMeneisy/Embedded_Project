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
