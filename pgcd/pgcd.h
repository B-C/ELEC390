#ifndef PGCD_H
#define PGCD_H

#include "systemc.h"

unsigned char euclide(unsigned char a, unsigned char b);

SC_MODULE(Pgcd_hl)
{
	sc_in<bool> clk;
	sc_in<unsigned char> x,y;
	sc_out<unsigned char> pgcd;
	sc_in<bool> start;
	sc_out<bool> done;

	void compute();

	SC_CTOR(Pgcd_hl): x("x"),y("y"),pgcd("pgcd"),start("start"),done("done")
	{
		SC_THREAD(compute);
		sensitive << clk.pos();
	}
};

SC_MODULE(Pgcd)
{
	sc_in<bool> clk;
	sc_in<unsigned char> x,y;
	sc_out<unsigned char> pgcd;
	sc_in<bool> start;
	sc_out<bool> done;

	void compute();

	SC_CTOR(Pgcd): x("x"),y("y"),pgcd("pgcd"),start("start"),done("done")
	{
		SC_THREAD(compute);
		sensitive << clk.pos();
	}
};



#endif
