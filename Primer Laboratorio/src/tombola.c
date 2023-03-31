#include <stdio.h>
#include <pic14/pic12f683.h>
#include <math.h> 
#include <stdbool.h>

typedef unsigned int word; 
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);  // WDT y MCLR OFF

void delay (unsigned int tiempo);
unsigned char randomNumberGen();


int D0;
int C1;
int B2;
int A3;

int D4;
int C5;
int B6;
int A7;
int n;

void main() {

ANSEL = 0;
CMCON0 = 0x07;
TRISIO=0b00001000;      
GPIO = 0x00;

int t;
int u;
int n;
int num;
int counter;

D0 = 0;
C1 = 0;
B2 = 0;
A3 = 0;

D4 = 0;
C5 = 0;
B6 = 0;
A7 = 0;

t = 0;
u = 0;
n = 2;
t = 0;
u = 0;
n = 2;
counter = 0;



    while(1) {			
    					
	   	    	    	

        	if (GP3==0) {
        			delay(100);
        				
        			
        		if (counter <= 15) {
        			
      				num = randomNumberGen();
				u=num%10; 			// Units
        			t=(num/10)%10; 		// Tens
        	
       			counter = counter+1;
      	            }
      	            
      	            else {
        	   		delay(100);
				u=9; 			// Units
        			t=9; 			// Tens	
        	    		counter = 0;
        	    
        	    		}
			
			switch (u) { 
    					case 0:
    				
    						D0 = 0;
						C1 = 0;
						B2 = 0;
						A3 = 0;
						break;	
							
    					case 1:
    				
    						D0 = 1;
						C1 = 0;
						B2 = 0;
						A3 = 0;
						break;	
					
    					case 2:
    				
    						D0 = 0;
						C1 = 1;
						B2 = 0;
						A3 = 0;
						break;	
					
    					case 3:
    				
    						D0 = 1;
						C1 = 1;
						B2 = 0;
						A3 = 0;
						break;
						
					case 4:		
    						D0 = 0;
						C1 = 0;
						B2 = 1;
						A3 = 0;
						break;
						
					case 5: 		
    						D0 = 1;
						C1 = 0;
						B2 = 1;
						A3 = 0;
						break;	
					
					case 6:
				
    						D0 = 0;
						C1 = 1;
						B2 = 1;
						A3 = 0;
						break;	
				
					case 7:
				
    						D0 = 1;
						C1 = 1;
						B2 = 1;
						A3 = 0;
						break;	
					
					case 8:	
    						D0 = 0;
						C1 = 0;
						B2 = 0;
						A3 = 1;
						break;	
					
					case 9:
    						D0 = 1;
						C1 = 0;
						B2 = 0;
						A3 = 1;
						break;	
    			}	
    			
    			
    				switch (t) { 
    				
    					case 0:
    						D4 = 0;
						C5 = 0;
						B6 = 0;
						A7 = 0;
						break;	
							
    					case 1:
    				
    						D4 = 1;
						C5 = 0;
						B6 = 0;
						A7 = 0;
						break;	
					
    					case 2:
    				
    						D4 = 0;
						C5 = 1;
						B6 = 0;
						A7 = 0;
						break;	
					
    					case 3:
    				
    						D4 = 1;
						C5 = 1;
						B6 = 0;
						A7 = 0;
						break;
						
					case 4:		
    						D4 = 0;
						C5 = 0;
						B6 = 1;
						A7 = 0;
						break;
						
					case 5: 		
    						D4 = 1;
						C5 = 0;
						B6 = 1;
						A7 = 0;
						break;	
					
					case 6:
				
    						D4 = 0;
						C5 = 1;
						B6 = 1;
						A7 = 0;
						break;	
				
					case 7:
				
    						D4 = 1;
						C5 = 1;
						B6 = 1;
						A7 = 0;
						break;	
					
					case 8:	
    						D4 = 0;
						C5 = 0;
						B6 = 0;
						A7 = 1;
						break;	
					
					case 9:
    						D4 = 1;
						C5 = 0;
						B6 = 0;
						A7 = 1;
						break;	
    				
    					}
  					
  				
       				
             }   
             
             				delay(10);
    					GP5 = ~GP5;
					
					GP0 = D0;
					GP1 = C1;
					GP2 = B2;
					GP4 = A3;
					
					delay(10);
					
					GP5 = ~GP5;
					
					GP0 = D4;
					GP1 = C5;
					GP2 = B6;
					GP4 = A7;   
             				
    }
     }

unsigned char randomNumberGen(){
			
    			n |= n == 0;
			n ^= (n & 0x07) << 5;
			n ^= n >> 3;
			
			n ^= (n & 0x03) << 6;
			n = n & 0xff;

return n;

}
    
void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}

