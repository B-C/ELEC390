#include "compt.h"

void compteur::compte()
{
	if(!reset)
		value=0;
	else if(load)
		value=in.read();
	else
		value++;

	value%=127;
	out=value;
}
