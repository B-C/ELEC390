#include "multiples.h"

void multiples::next()
{
	if(!reset||(m2==0xFE))
	{
		m3=3;
		m2=4;
		out=2;
	}
	else
	{
		if(m2!=m3)
		{
			if(m2<m3)
			{
				out=m2;
				m2+=2;
			}
			else
			{
				out=m3;
				m3+=3;
			}
		}
		else
		{
			out=m2;
			m2+=2;
			m3+=3;
		}
	}
}
