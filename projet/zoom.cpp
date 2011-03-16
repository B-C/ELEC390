#include "zoom.h"

void ZOOM::send_pixels()
{
	if(!reset_n)
	{
	reset:
		vref_out=href_out=false;
		wait();		
	}
	while(1)
	{
		sem->wait();
		sem->post();

		for(long i=0 ; i<625 ; i++)
			for(long j=0 ; j<874 ; j+=coeff)
			{
				href_out = (i<576) && (j<720);
				vref_out = (i<3);
				
				if((i<576) && (j<720))
					pixel_out = buffer[(i/coeff*(720/coeff)+j/coeff)%size];
				else
					pixel_out = 0;

				wait(coeff);// Send coeff X  
				if(reset_n == false) 
					goto reset;
			}
	}
}

void ZOOM::get_pixels()
{
	if(!reset_n)
	{
	reset:
		if(sem->get_value()==1)
			sem->wait();
		wait();
	}
	while(1)
	{
		while(!vref_in)
		{
			wait();
			if(reset_n == false) 
				goto reset;
		}
		for(long i=0 ; i<(start_i+576/coeff) ; i++)
		{
			for(long j=0 ; j<720 ; j++)
			{
				if(i==start_i && j== start_j)
					sem->post();

				if(i>=start_i && j>=start_i && j<(start_j+720/coeff))
					buffer[((i-start_i)*(720/coeff)+(j-start_j))%size]=pixel_in;

				wait();
				if(reset_n == false) 
					goto reset;
			}
			while(!href_in)
			{
				wait();
				if(reset_n == false) 
					goto reset;
			}
		}
		sem->wait();
	}
}
