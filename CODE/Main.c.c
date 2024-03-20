#include "reg51.h"

#define SegOne   0xfe     // define digit 4
#define SegTwo   0xfd			// digit 3
#define SegThree 0xfb     // digit 2
#define SegFour  0xf7	    // digit 1


sbit rd_adc=P1^0; 				// Read(RD) pin of ADC0804
sbit wr_adc=P1^1; 				// Write(WR) pin of ADC0804
sbit intr_adc=P1^2; 			// Interrupt(INTR) pin of ADC0804


sbit set=P1^3;       			// Set Button pin declaration
sbit inc=P1^4; 						// Increament Button pin declaration
sbit dec=P1^5;						// Decreament Button pin declaration
sbit reset=P1^6;					// Reset Button pin declaration


sbit buzzer=P1^7;					// Buzzer  pin declaration



// delay for seven segment display
void DELAY_ms(unsigned int ms_Count) 
{
	unsigned int i, j;

    for (i = 0; i < ms_Count; i++) 
    {
			
      for (j = 0; j < 100; j++);
			
    }
}



// delay for adc
void delay(unsigned int z)
{
	
  unsigned int p,q;
	
  for(p=0;p<z;p++)    //repeat for 'z' times
  {
		
    for(q=0;q<1375;q++);   //repeat for 1375 times
		
  }
	
}




// main function

int main()
{
		
	// declaring 7 segment value and variable
  char hexvalue[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
	int num, temp,i,st=0;               
	unsigned int value, cnt=35, set_value=35;   
	//declare end 
		
	P0=0xFF;    //make Port 0 as input port for ADC_data 
		
  while (1)   // continue loop
  {
		//send LOW to HIGH pulse on WR pin
		wr_adc=0;   
		delay(1);
		wr_adc=1;   
		//
			
		while(intr_adc==1);               //wait for End of Conversion
		rd_adc=0;                        //make RD = 0 to read the data from ADC0804
		value=P0; 											//copy ADC _data
		value = value*0.488;           //ADC ref
		
		
    for (i = 0; i < 100; i++)
		{
                
			num = value;								// value is copied to num 
      temp = num / 1000;				 // for getting thousand'th digit 
      num = num % 1000;						
      P3 = SegOne; 								// send _data to control pins
      P2 = hexvalue[temp];        //send _data to d0 to d7       
      DELAY_ms(1);             
         
			temp = num / 100;							// for getting hundred'th digit 
      num = num % 100;
      P3 = SegTwo; 
      P2 = hexvalue[temp];
      DELAY_ms(1);
			         
			temp = num / 10;							// for getting tenth digit 
      P3 = SegThree;
      P2 = hexvalue[temp];
      DELAY_ms(1);
  
			temp = num % 10;							// 0'th digit
      P3 = SegFour;
      P2 = hexvalue[temp];
      DELAY_ms(1);                              
            
		}
      		
		rd_adc=1;   											//make RD = 1 for the next cycle
		
			


// buzzer 		
		if(value>=set_value)
		{
			
			buzzer=1;         // value >= set_value then buzzer will on
				
		}
				
		else	
		{
					
			buzzer=0;			// value < setvalue then buzzer is off
				
		}			
		// buzzer end
		
		
		
		if(set==0)			
		{
					
			st=1;							// if set button pressed  then st = 1
				
		}			
				
				
		while(st!=0)        // while st is equal to 1 		
		{
			
			if(inc==0)	
			{
						
				cnt++;					// increament
					
			}
					
			else if(dec==0)		
			{
						
				cnt--;        // decreament
					
			}
			
			else if(reset==0)		
			{
					
			set_value=35;			// set default value if reset button pressed 	
			cnt=35;	
		
			}
					
					
			for (i = 0; i < 100; i++)      
			{
                
				num = cnt;   
				temp = num / 1000;
        num = num % 1000;
        P3 = SegOne; 
        P2 = hexvalue[temp];               
        DELAY_ms(1);

        temp = num / 100;
        num = num % 100;
        P3 = SegTwo; 
        P2 = hexvalue[temp];
        DELAY_ms(1);

        temp = num / 10;
        P3 = SegThree;
        P2 = hexvalue[temp];
        DELAY_ms(1);

        temp = num % 10;
        P3 = SegFour;
        P2 = hexvalue[temp];
        DELAY_ms(1);                              
            
			}
						
			if(set==0)		
			{
				
				set_value=cnt;	
				st=0;
						
			}
				
		}
    
	}

}
