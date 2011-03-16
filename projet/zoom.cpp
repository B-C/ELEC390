#include "zoom.h"

void ZOOM::hack()
{
	unsigned char *buffer=new unsigned char[720/2*576/2];

	if(!reset_n)
	{
		vref_out=href_out=false;
		wait();
	}
	while(1)
	{
		while(!vref_in)
			wait();
		for(long i=0 ; i<576 ; i++)
		{
			vref_out = (i<3);
			href_out=true;
			for(long j=0 ; j<720 ; j++)
			{
				if(j<(720/2) && i<(576/2))
					buffer[i*576/2+j]=pixel_in;
				
				pixel_out=buffer[i/2*576/2+j/2];

				wait();
			}			
			href_out=false;

			while(!href_in)
				wait();
		}
	}
}
