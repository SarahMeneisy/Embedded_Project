{

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
