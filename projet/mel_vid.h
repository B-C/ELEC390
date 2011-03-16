#ifndef MEL_VID_H
#define MEL_VID_H

#include "systemc.h"
#include "pixel.h"

SC_MODULE(melanger)
{
	sc_in<bool> clk;

	sc_in<Pixel> p1, p2;
	sc_out<Pixel> out;

	void compute();

	SC_CTOR(melanger)
	{
		SC_METHOD(compute);
		sensitive << clk.pos();
	}
};

#endif
