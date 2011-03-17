#include "ram.h"

void ram::read_data()
{
	data_out=ram_data[addr_out.read()];
}


void ram::write_data()
{
	if(!wen)
		ram_data[addr_in.read()]=data_in;
}
