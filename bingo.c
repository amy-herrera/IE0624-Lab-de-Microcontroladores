#include <stdio.h>
#include <pic14/pic12f675.h>
#include <math.h> 
#include <stdbool.h>

typedef unsigned int word; 
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);  // WDT y MCLR OFF

void delay (unsigned int tiempo);

void main() {

int D0;
int C1;
int B2;
int A3;

int D4;
int C5;
int B6;
int A7;

int c;
int t;
int u;
int i;
static unsigned char lfsr = 0x8F;
unsigned char bit;

ANSEL = 0;
//CM1CON0,7 = 0;
TRISIO=0b00001000;      
GPIO = 0x00;
c = 0;
t = 0;
u = 0;
  
   
    while(1) {
    
        	       	
        	for (i = 0; i < 1; ++i) {
    		bit = ((lfsr >> 0)^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
		lfsr= (lfsr >> 1) | (bit << 7);

		lfsr = lfsr %100;
	
		u=lfsr%10; 		// Units
        	t=(lfsr/10)%10; 	// Tens
        	
        	if (GP3==0) { 
        	
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
    			
    				//delay(50);	
    				GP5 = ~GP5;
		
				GP0 = D0;
				GP1 = C1;
				GP2 = B2;
				GP4 = A3;
		
				delay(50);
				GP5 = ~GP5;
		
				GP0 = D4;
				GP1 = C5;
				GP2 = B6;
				GP4 = A7;
		
		}
				
             }   
    }
    void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<100;j++);
}

