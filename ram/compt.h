#ifndef COMPT_H
#define COMPT_H

#include "systemc.h"

SC_MODULE(compteur)
{
	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_in<bool> load;
	sc_in<sc_uint<8> > in;
	sc_out<sc_uint<8> > out;

	unsigned char value;

	void compte();

	SC_CTOR(compteur)
	{
		SC_METHOD(compte);
		sensitive<<clk.pos();
	}
};

#endif
