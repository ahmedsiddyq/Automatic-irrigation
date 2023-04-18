#include <lcd.h>
#include "eeprom.h"
#include "delay.h"

void timerINT();
void delay (unsigned int d );
void sets();
void dismode();
void custmmodeedit();
void custmmodeset();
void domode(unsigned char);
void servo(unsigned char);
void pumpon(unsigned long cmodeonttt);
void shour();
unsigned int rst (unsigned char ad);
void rti(unsigned char oo );
void restor();
void custmmode0();
void custmmode1();
void custmmode2();
	
unsigned char holemodenum=1;
unsigned char hole0modenum=1;
unsigned char hole1modenum=1;
unsigned char hole2modenum=1;


unsigned char holep0=30;
unsigned char holep1=90;
unsigned char holep2=170;
unsigned char place=0;

unsigned char dosc=0;
unsigned char	seton=0;

unsigned char us=0;
unsigned char angel=0;
unsigned char i=1;
unsigned char ii=1;
unsigned char lass=1;
unsigned char lasssen=1;

unsigned long hour=0;
unsigned long hourf=0;


unsigned int modevolum=5;

unsigned long hourtime=3600000;

unsigned long fshour=0;

unsigned long millis=0;

unsigned long testhont=0;

unsigned char holmodenum=1;

//****************//

//****************//

unsigned int cmodedt=0;
unsigned int cmodeont=5;
//****************//

unsigned int cmode0ont=5;
unsigned int cmode1ont=5;
unsigned int cmode2ont=5;

//****************//
unsigned int cmode0dt=0;
unsigned int cmode1dt=0;
unsigned int cmode2dt=0;

unsigned int cmode0dft=0;
unsigned int cmode1dft=0;
unsigned int cmode2dft=0;


sbit EN = P1^0;
sbit RS = P1^1;
sbit pump=P1^2;
sbit motor=P1^4;

sbit edit=P1^5;

sbit inc=P3^0;
sbit ok=P3^1;
sbit setinput=P3^2;
sbit wlevel=P3^3;
sbit dec=P3^4;
sbit buzzer=P3^5;
sbit sda=P3^6;
sbit scl=P3^7;


/******************
*******************
*******************/

void main()
{
timerINT();
motor=1;	
lcdint();
eeint(AT24C02);

	lcddigt(1,3);
	lcdprint("Thanks To");
	lcddigt(2,2);
	lcdprint("Eng.Safinaz");
	delay(3000);
	lcdcmd(1);
	lcddigt(1,3);
	lcdprint("Thanks To");
	lcddigt(2,2);
	lcdprint("Eng.A-Elsayed");
	delay(3000);
	lcdcmd(1);
	lcddigt(1,4);
	lcdprint("MADE BY");
	lcddigt(2,2);
	lcdprint("'50013 TEAM'");
	delay(3000);
	lcdcmd(1);	

restor();


while(1)
	
{
	if(seton)
	{
	sets();
	seton=0;
	}
	
if (millis-fshour>=hourtime/2)
{
fshour=millis;
shour();
}

lcddigt(1,0);
lcdprint("SC1");
lcddigt(2,0);
 rti(hole0modenum);

lcddigt(1,4);
lcdprint("SC2");
lcddigt(2,4);
rti(hole1modenum);


lcddigt(1,8);
lcdprint("SC3");
lcddigt(2,8);
rti(hole2modenum);

/*
lcddigt(1,12);
lcdvar(hour);
*/
if(hole0modenum!=5&&!seton)
{
		dosc=1;
	place=holep0;
	domode(hole0modenum);
}


if(hole1modenum!=5&&!seton) 
{
		dosc=2;
	place=holep1;
	domode(hole1modenum);

}

if(hole2modenum!=5&&!seton) 
{ 
	dosc=3;
	place=holep2;
	domode(hole2modenum)	;

}

if(!wlevel)
{buzzer=0;}
else
{buzzer=1;}
delay(2000);
lcdcmd(1);

}


}

/*****************************************************
*****************************************************
*****************************************************/

void sets()
{
unsigned char  y=1;		
for(i=1;i<=3;i++)
	{
		
		switch(i)
{
	case 1 :
		holemodenum=hole0modenum;
	 break;
case 2 :
		holemodenum=hole1modenum;
	 break;
case 3 :
		holemodenum=hole2modenum;
	 break;
default:i=1;
		}
		
lcdcmd(1);
while(ok||holemodenum==4)
{
if(!inc)
{
holemodenum++;
lcdcmd(1);
delay(60);
}
if(!dec)
{
holemodenum--;
lcdcmd(1);
delay(60);
}
if(holemodenum>5)
holemodenum=1;
if(holemodenum<1)
holemodenum=5;
custmmodeedit();

delay(30);
lcddigt(1,0);
lcdchar('<');
lcddigt(1,15);
lcdchar('>');
lcddigt(1,3);
lcdprint("SC");
lcdvar(i);
lcdprint(":");
dismode();
delay(30);


}

switch(i)
{
	case 1 :
		hole0modenum=holemodenum;
	  eesave(0x00,hole0modenum);
	 break;
case 2 :
		hole1modenum=holemodenum;
   eesave(0x01,hole1modenum);

	 break;
case 3 :
		hole2modenum=holemodenum;
    eesave(0x02,hole2modenum);
	 break;
default:i=1;
		}

delay(30);
lcdcmd(1);
		
	if(!ok)
	delay(450);
}
i=1;
seton=0;
while(y)
	{
	lcddigt(1,0);
	lcdprint("Do u want test ?");
	lcddigt(2,0);
	lcdprint("YES:OK");	
	lcddigt(2,9);
	lcdprint("NO:EDIT");		
	ii=1;
		if(!ok)
		{
			for (ii;ii<=3;ii++)
			{
	lcdcmd(1);
	lcddigt(1,5);
	lcdprint("TESTING!");
	lcddigt(2,1);
	lcdprint("SC");
	lcdvar(ii); 		
 
	delay(100);
				
switch(ii)
					
	{
		case 1:
		holmodenum = hole0modenum;
		place=holep0;
		dosc=1;

		break;	
				
		case 2:
		holmodenum = hole1modenum;		
		place=holep1;
		dosc=2;

		break;
		case 3:
		holmodenum=hole2modenum;
		place=holep2 ;
		dosc=3;
   	break;
				}
				
			switch(holmodenum)
			{
				case 1:
				testhont=cmode0ont;
				break;
				case 2:
				testhont=cmode1ont;
				break;
				case 3:
				testhont=cmode2ont;
				break;
			}
			
			
	  pumpon(testhont);
		lcdcmd(1);
			
			
		}
		y=0;
		}
			
	if(!edit)
	y=0;
		}
		ii=1;
		lcdcmd(1);
		
	}

/*****************************************************
*****************************************************
*****************************************************/


void domode(unsigned char m)

{
		switch(m)
	
{

	case 1 :
	custmmode0();
	break;
	
	case 2 :
	custmmode1();
	break;
	
	case 3 :
	custmmode2();
	break;
	
}
}


/*****************************************************
*****************************************************
*****************************************************/

void custmmodeedit()
{
	switch(holemodenum)
		
	{
	
	case 1 :
		
	if(!edit)
	{
	lcdcmd(1);
	custmmodeset();
  }
	break;
	
	case 2:
		
	if(!edit)
	{
	lcdcmd(1);
	custmmodeset();
	}	
	
	break;
	
	case 3 :
		
	if(!edit)
	{lcdcmd(1);
	custmmodeset();
  }
	break;
	
	
	case 4 :
		
	
	if(!edit)
	{
		switch(i)
{
	case 1 :
	angel=holep0;
	 break;
case 2 :
	angel=holep1;
	 break;
case 3 :
	angel=holep2;
	 break;
default:i=1;
		}
		lcdcmd(1);	

	while(ok)
		
	{
	  
if(!inc)
{
angel++;
lcdcmd(1);
}
if(!dec)
{
angel--;
lcdcmd(1);
}
if(angel>180)
angel=1;
if(angel<1)
angel=180;
servo(angel);
delay(5);
lcddigt(2,0);
lcdchar('<');
lcddigt(2,15);
lcdchar('>');
lcddigt(1,2);
lcdprint("'st HOLE ANGEL");
delay(5);
lcddigt(1,1);
lcdvar(i); 
lcddigt(2,5);
lcdvar(angel);
delay(5);
switch(i)
{
	case 1 :
		holep0=angel;
eesave(0x03,holep0);
delay(10);

	 break;
case 2 :
		holep1=angel;
eesave(0x04,holep1);
delay(10);
	 break;


case 3 :

holep2=angel;
eesave(0x05,holep2);
delay(10);
	 break;
default:i=1;
		}

delay(20);
	
	}
	lcdcmd(1);
  }
	
	
	break;
	
	case 5 :

	break;
	
	}

}



/*****************************************************
*****************************************************
*****************************************************/

 void custmmodeset(  )
 {
 
switch(holemodenum)
{
	case 1 :
modevolum=cmode0ont*5;
cmodedt=cmode0dt;
break;
	case 2 :
modevolum=cmode1ont*5;
cmodedt=cmode1dt;

break;
	case 3 :
modevolum=cmode2ont*5;
cmodedt=cmode2dt;
break;
}

	 
	while(ok)
		
{
	  
if(!inc)
{
modevolum=modevolum+5;
lcdcmd(1);
}
if(!dec)
{
modevolum=modevolum-5;
lcdcmd(1);
}

delay(20);
lcddigt(2,0);
lcdchar('<');
lcddigt(2,15);
lcdchar('>');

lcddigt(1,2);
lcdprint("Save");
lcdvar(holemodenum);
lcdprint("PATCH"); 
delay(20);
lcddigt(2,5);
lcdvar(modevolum);
lcdprint("mL");
delay(50);
cmodeont=(modevolum/5);
}

delay(500);



	while(ok)
{
	
if(!inc)
{
cmodedt++;
 lcdcmd(1);
}
if(!dec)
{
cmodedt--;
lcdcmd(1);
}

delay(20);
lcddigt(2,0);
lcdchar('<');
lcddigt(2,15);
lcdchar('>');

lcddigt(1,1);
lcdprint("Save");
lcdvar(holemodenum);
lcdprint(" PIROUD");
delay(20);
 
lcddigt(2,5);
lcdvar(cmodedt);
lcdprint("Hour");
delay(35);
}

delay(300);
lcdcmd(1);

switch(holemodenum)
{
	case 1 :
cmode0ont=cmodeont;
cmode0dt=cmodedt;
eesave(0x10,cmode0dt);
eesave(0x11,(cmode0dt>>8));
	
eesave(0x12,cmode0ont);
eesave(0x13,(cmode0ont>>8));
	
break;
	case 2 :
cmode1ont=cmodeont;
cmode1dt=cmodedt;
	
eesave(0x14,cmode1dt);
eesave(0x15,(cmode1dt>>8));
	
eesave(0x16,cmode1ont);
eesave(0x17,(cmode1ont>>8));
	
break;
	
	case 3 :
cmode2ont=cmodeont;
cmode2dt=cmodedt;

eesave(0x18,cmode2dt);
eesave(0x19,(cmode2dt>>8));
	
eesave(0x1A,cmode2ont);
eesave(0x1B,(cmode2ont>>8));
break;
}

}

/*****************************************************
*****************************************************
*****************************************************/


void custmmode0()
{
	
if((hour-cmode0dft)>=cmode0dt)
	{
    pumpon(cmode0ont);
	cmode0dft=hour;
	}
	
}

void custmmode1()
{

	if((hour-cmode1dft)>=cmode1dt)
	{
    pumpon(cmode1ont);

	cmode1dft=hour;
	}
}


void custmmode2()
{	
if((hour-cmode2dft)>=cmode2dt)
	{
  pumpon(cmode2ont);
	cmode2dft=hour;
	}
}


void pumpon(unsigned long cmodeonttt)
{
	
	unsigned long cmodeontft=millis;
	while((((millis-cmodeontft)/1000)<cmodeonttt)&&!seton)
	{
	lcdcmd(1);
   lcddigt(1,4);
	lcdprint("pumbing..");
		lcddigt(2,6);
	switch (dosc)
	{
		case  1:
		lcdprint("SC1");
		break;
		
		case 2:
		lcdprint("SC2");
		break;
		
		case 3:
		lcdprint("SC3");
		break;
		
	}
	
	servo(place);
	delay(500);
	pump=0;
	}
	pump=1;
	delay(100);

}


/*****************************************************
*****************************************************
*****************************************************/



void rti(unsigned char oo )
{
switch(oo)
{	
	case 1 :
	lcdvar(cmode0dt-(hour-cmode0dft));	
	break;
	
	case 2 :
		lcdvar(cmode1dt-(hour-cmode1dft));
	break;
		
	case 3 :
		lcdvar(cmode2dt-(hour-cmode2dft));
	break;
	
	case 5 :
	lcdprint("off");
	break;
}
}


void dismode()
	
{
switch (holemodenum)
	
{

	case 1:
  lcdprint("Save 1");
	lcddigt(2,0);
	lcdprint("OK");
	lcddigt(2,12);
	lcdprint("EDIT");
	break;

	case 2:
    lcdprint("Save 2");
	lcddigt(2,0);
	lcdprint("OK");
  lcddigt(2,12);
	lcdprint("EDIT");
	break;

	case 3:
    lcdprint("Save 3");
		lcddigt(2,0);
	lcdprint("OK");
	lcddigt(2,12);
	lcdprint("EDIT");
	break;

	case 4:
  lcdprint("position");
  lcddigt(2,12);
	lcdprint("EDIT");
	break;
	
	case 5:
  lcdprint("OFF");
	lcddigt(2,12);
	lcddigt(2,0);
	lcdprint("OK");
	break;

	default:lcdprint("fuck");
}

}



void shour()
{
	
	
	eesave(0x06,hour);
	eesave(0x07,hour>>8);
	eesave(0x08,hour>>16);
	eesave(0x09,hour>>24);
  
	eesave(0x70,cmode0dft);
	eesave(0x71,cmode0dft>>8);
	
	eesave(0x72,cmode1dft);
	eesave(0x73,cmode1dft>>8);
	
	eesave(0x74,cmode2dft);
	eesave(0x75,cmode2dft>>8);

}

unsigned int rst (unsigned char ad)
{
unsigned int ti=0;
ti|= eeread(ad+1);
ti=ti<<8;
ti|= eeread(ad);
return ti;
}


void restor()
{

EA=0;

	hole0modenum = eeread(0x00);
	hole1modenum = eeread(0x01);
	hole2modenum = eeread(0x02);
	
	holep0 = eeread(0x03);
	holep1 = eeread(0x04);
	holep2 = eeread(0x05);
	

  hour=0;
	hour|= eeread(0x09);

	hour= hour<<8;

	hour|=   eeread(0x08);
	hour= hour<<8;

	hour|=  eeread(0x07);
	hour= hour<<8;
	
	hour|= eeread(0x06);
	
	
  cmode0dt= rst(0x10);	
   
	cmode1dt= rst(0x14);

	cmode2dt= rst(0x18);

	cmode0ont= rst(0x12);
	
	cmode1ont= rst(0x16);

	cmode2ont= rst(0x1A);
	
		
	cmode0dft= rst(0x70);	
   
	cmode1dft= rst(0x72);

	cmode2dft= rst(0x74);
	
	EA=1;

}

/*****************************************************
*****************************************************
*****************************************************/
void servo( unsigned char ang)
{
	
unsigned int Tics = 64735-(ang * 23);

unsigned char LOWREG = Tics & 0x00FF ;
unsigned char HREG = (Tics>>8) & 0x00FF ;
unsigned long ftime=millis;
	while (millis-ftime<100)
	{
unsigned long ftimme = millis;
		TH1=HREG;
		TL1=LOWREG;
		TR1=1;
    motor=1;
	while (millis-ftimme<20)
	{}
	}

}


void timerINT()
{
TMOD=0x11;
IE=0x8A;
TH0 =0xF8;
TL0=0x30;
EX0=1;
IT0=1;
IT1=0;	
TR1=0;
TR0=1;

}



void delay ( unsigned int d )

{
	
unsigned long  fimillis=millis;

while((millis-fimillis)<d)
{}
	
}


void Timer (void)interrupt 1
 
 { 
	millis++;	
	TR0=0;
	TF0=0;
	TH0 =0xF8;
	TL0=0x39;
	TR0=1;
	
	if(millis-hourf>hourtime)
	{
	hour++;
	hourf=millis;
if(!lass)		
{
	lcdcmd(1);
	lcddigt(1,3);
	lcdprint("Demo mood!");
	DELAY_ms(1500);
	lcdcmd(1);
}
	}
		
	
 }
 
 void Timer1 (void) interrupt 3

{
	motor=0;
	TR1=0;
	TF1=0;
}



void water (void) interrupt 2
{
while(!wlevel)
{
buzzer=0;
}
buzzer=1;
IE=0;
}







void set (void) interrupt 0
	
{
unsigned char zeb=6;
seton=1;
IE0=0;
DELAY_ms(50);
if(!edit)
{
	hour=0;
	for(zeb=6;zeb<=9;zeb++)
	{	
	eesave(zeb,0x00);
	}
	seton=0;
	lcdcmd(1);
	lcddigt(1,3);
	lcdprint("Time clear !");
	DELAY_ms(3000);
	lcdcmd(1);
}
DELAY_ms(50);

if(!ok)
{	seton=0;
	DELAY_ms(50);
	if(lass)
	{
	seton=0;
	lcdcmd(1);
	lcddigt(1,3);
	lcdprint("Demo ON !");
	hourtime=3600;
	DELAY_ms(3000);
	lass=!lass;
	lcdcmd(1);
	}
	else
	{
	lcdcmd(1);
	lcddigt(1,3);
	lcdprint("Demo OFF !");
	hourtime=3600000;
	DELAY_ms(3000);
	lass=!lass;
	lcdcmd(1);
	seton=0;
	}	
}

if(!inc)
{
	seton=0;
	DELAY_ms(50);
	if(lasssen)
	{
	seton=0;
	lcdcmd(1);
	lcddigt(1,1);
	lcdprint("water sensor");
	lcddigt(2,5);
	lcdprint(" ON!");
	EX1=1;
	DELAY_ms(3000);
	lasssen=!lasssen;
	lcdcmd(1);
	}
	else
	{
	lcdcmd(1);
	lcddigt(1,1);
	lcdprint("water sensor");
	lcddigt(2,5);
	lcdprint("OFF !");
	EX1=0;
	DELAY_ms(3000);
	lasssen=!lasssen;
	lcdcmd(1);
	seton=0;
	}	
}
}
