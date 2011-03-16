#include "moy.h"


typedef enum{WAITING_F,WAITING_L,FIRST_LINE, 
	     MIDDLE_LINES_P1, MIDDLE_LINES, MIDDLE_LINES_P720,
	     LAST_LINE} State;

void MOY::hack()
{
	State state;
	long count_c=0,count_l=0;


	unsigned char buffer[2][720], pixel_2=0, pixel_1=0;
	short up,dn;

	if(!reset_n)
	{
		state=WAITING_F;
		
		up=0;dn=1;
		for(int i= 0 ; i<720 ; i++)
			buffer[up][i]=0;
		wait();
	}
	while(1)
	{
		switch(state)
		{

/******************************************************************************/
		case WAITING_F:
			href_out=false;
			vref_out=false;

			if(vref_in)
			{			
				count_l=count_c=0;
				state=FIRST_LINE;
			}
			else
				wait();
			break;

/******************************************************************************/

		case FIRST_LINE:
			buffer[dn][count_c]=pixel_in;

			count_c++;
			if(count_c==720)
				state=WAITING_L;

			wait();
			break;

/******************************************************************************/

		case WAITING_L:
			href_out=false;

			if(count_l==575)
			{
				wait(56);
				count_c=0;
				state=LAST_LINE;
			}
			else
			{
				if(href_in)
				{
					count_l++;
					count_c=0;
					state=MIDDLE_LINES_P1;					
				}
				else
					wait();
			}
			break;

/******************************************************************************/

		case MIDDLE_LINES_P1:
			pixel_1=pixel_in;
			wait();

			/** synchro **/
			href_out=true;
			if(count_l<4)
				vref_out=true;
			else
				vref_out=false;
			/**         **/
			state=MIDDLE_LINES;
			break;

/******************************************************************************/
			
		case MIDDLE_LINES:

			if(count_c==0)
				pixel_out=( 
					buffer[up][0]+buffer[up][1]+
					             +buffer[dn][1]+
					pixel_1      +pixel_in     
					)/5;
	
			else
			{
				pixel_out=(
					buffer[up][count_c-1]+buffer[up][count_c]+buffer[up][count_c+1]+
					buffer[dn][count_c-1]+                    buffer[dn][count_c+1]+
					pixel_2              +pixel_1            +pixel_in             
					)/8;
				
				buffer[up][count_c-1]=pixel_2;
			}


			pixel_2=pixel_1;
			pixel_1=pixel_in;


			count_c++;
			if(count_c==719)
				state=MIDDLE_LINES_P720;
			
			wait();
			break;

/******************************************************************************/

		case MIDDLE_LINES_P720:
			pixel_out=(buffer[up][718]+buffer[up][719]+
				   buffer[dn][718]+
				   pixel_2        + pixel_1       )/5;

			buffer[up][718]=pixel_2;
			buffer[up][719]=pixel_1;

			/* Swap the 2 buffers */
			up=1-up;
			dn=1-dn;

			state=WAITING_L;
			wait();
			break;

/******************************************************************************/

		case LAST_LINE:
			
			href_out=true;

			pixel_out=(
				(count_c==0?0:buffer[up][count_c-1])+buffer[up][count_c]+(count_c==719?0:buffer[up][count_c+1])+
				(count_c==0?0:buffer[dn][count_c-1])+                    (count_c==719?0:buffer[dn][count_c+1]))
				/5;

			if(count_c>0)
				buffer[up][count_c-1]=0;

			count_c++;
			if(count_c==720)
			{
				buffer[up][719]=0;
				state=WAITING_F;
			}

			wait();
			break;

/******************************************************************************/
		}
	}
}
