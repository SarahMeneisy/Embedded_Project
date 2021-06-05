#include "math.h"
#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
 

void SystemInit(){};
long double toRadians(long double x);
long double distResult(long double x1, long double y1, 
					long double x2, long double y2);

int main(void){
	 
	long double x1,x2,y1,y2,res;
	x1=53.32055555555556;
	x2=53.31861111111111;
	y1=-1.7297222222222221;
	y2=-1.6997222222222223;
  res =distResult(x1,y1,x2,y2); // 	We assumed 2 points so that distnce > 100, to turn the led on in the first milestone
	 
	 
	
	
}


long double toRadians(long double x){
	const long double PI=3.14159265359;
	 long double rad= PI/180;
	return x*rad;
	
	
}
long double distResult(long double x1, long double y1, 
					long double x2, long double y2) 
{ 
	 long double disY,disX,result,Raduis ;   
	x1 = toRadians(x1); 
	y1 = toRadians(y1); 
	x2 = toRadians(x2); 
	y2 = toRadians(y2); 
	            
  disY = y2 - y1;   //distance of longitude 	             
  disX = x2 - x1; 	 //distance of latitude 
 
	result = pow(sin(disX / 2), 2) + 
						cos(x1) * cos(x2) * 
						pow(sin(disY / 2), 2); 
	result = 2 * asin(sqrt(result)); 
 
	Raduis = 6371;
	 
	result = result * Raduis*1000 ; // to covert it from Km to meters

	return result; 
}
