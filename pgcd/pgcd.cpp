#include "pgcd.h"

unsigned char euclide(unsigned char x, unsigned char y)
{
	unsigned char r,a,b;


	b=((x<y)? y : x);
	r=((x<y)? x : y);
	
	if(r!=0 && b!=0)
		while(r)
		{
			a=b;
			b=r;
			r=a%b;		
		}

	return b;	
}

void Pgcd_hl::compute()
{
	while(true)
	{
		done=0;
		if(start)
		{
			pgcd=euclide(x.read(),y.read());
			done=1;
		}
		wait();
	}
}

typedef enum{WAITING, COMPUTING, FINISHED} States;

void Pgcd::compute()
{
	unsigned char a,b,r;
	States state =WAITING;

	a=b=r=1;

	while(true)
	{
		switch(state)
		{
		case WAITING:
			done = 0;
			if(start)
			{
				b=y;
				r=x;

				if(r!=0 && b!=0)
					state=COMPUTING;
				else
				{
					b+=r;
					state=FINISHED;
				}
			}
			wait();
			break;

		case COMPUTING:
			a=((b<r)? r: b);
			b=((b<r)? b: r);
			r=a-b;	
			if(r==0) 
				state=FINISHED;

			wait();
			break;
			
		case FINISHED:
			pgcd=b;
			done=1;
			state=WAITING;
			wait();
			break;
		}
	}
}
