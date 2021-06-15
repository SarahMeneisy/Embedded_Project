#include "math.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdio.h"
#include "stdint.h"
#include <string.h>




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
	
	
	





