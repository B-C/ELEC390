#ifndef MULTIPLES_H
#define MULTIPLES_H

#include "systemc.h"

SC_MODULE(multiples)
{
	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_out<sc_uint<8> > out;

	unsigned char m3,m2;	

	void next();

	SC_CTOR(multiples)
	{
		SC_METHOD(next);
		sensitive <<  clk.pos();
	}
};

#endif




