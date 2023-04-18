#include <reg51.h>

extern bit RS;                                                                   
extern bit EN;  


void Lcd_Delay(int a)
{
    int j;
    int i;
    for(i=0;i<a;i++)
    {
        for(j=0;j<100;j++)
        {
        }
    }
}

void lcdcmd(char a)
{ 
  RS = 0;             // => RS = 0
  P2=a;             //Data transfer
  EN  = 1;             // => E = 1
  Lcd_Delay(10);
  EN  = 0;             // => E = 0
}


void lcddigt(char a, char b)
{
	if(a == 1)
	  lcdcmd(0x80 + b);
	else if(a == 2)
		lcdcmd(0xC0 + b);
}

void lcdint()
{
	P2=0x00;
	RS = 0;
	Lcd_Delay(200);
	///////////// Reset process from datasheet /////////
  lcdcmd(0x30);
	Lcd_Delay(50);
  lcdcmd(0x30);
	Lcd_Delay(110);
  lcdcmd(0x30);
  /////////////////////////////////////////////////////
  lcdcmd(0x38);    //function set
  lcdcmd(0x0C);    //display on,cursor off,blink off
  lcdcmd(0x01);    //clear display
  lcdcmd(0x06);    //entry mode, set increment
}

void lcdchar(unsigned char a)
{
   RS = 1;             // => RS = 1
   P2=a;             //Data transfer
   EN  = 1;             // => E = 1
   Lcd_Delay(10);
   EN  = 0;             // => E = 04
}

void lcdprint(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	 lcdchar(a[i]);
}



void lcdvar(unsigned int dag )
{
	
	unsigned long deev=10000;
	int i;
	for(i=1;i<=5;i++)
	{
switch((dag/deev)%10)
{
	case 0 :
		if((dag/(deev*10))!=0)
		{
			lcdchar('0');
		}	
	
	break;

	case 1 :
	lcdchar('1');
	break;
	
	case 2 :
		
	lcdchar('2');
	
	break;
	
	case 3 :
		
	lcdchar('3');
	
	break;
	
	case 4 :
		
	lcdchar('4');
	
	break;
	
	case 5 :
		
	lcdchar('5');
	
	break;
	
	case 6 :
		
	lcdchar('6');
	
	break;
	
	case 7 :
		
	lcdchar('7');
	
	break;
	
	case 8 :
		
	lcdchar('8');
	
	break;
	
	case 9 :
		
	lcdchar('9');
	
	break;
}
deev=deev/10;
}
		if(dag==0)
		{
			lcdchar('0');
		}
}
void Lcd_Shift_Right()
{
	lcdcmd(0x1C);
}

void Lcd_Shift_Left()
{
	lcdcmd(0x18);
}
//End LCD 8 Bit Interfacing Functions

