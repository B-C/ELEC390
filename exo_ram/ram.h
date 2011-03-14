#ifndef RAM_H
#define RAM_H

#include "systemc.h"

SC_MODULE(ram)
{
	sc_in<bool> clk;

	sc_in<sc_int<8> > addr_in;
	sc_in<sc_int<16> > data_in;
	sc_in<bool> wen;

	sc_in<sc_int<8> > addr_out;
	sc_out<sc_int<16> > data_out;

	void read_data();
	void write_data();

	sc_int<16> ram_data[256];

	SC_CTOR(ram)
	{
		SC_METHOD(read_data);
		sensitive << clk.pos();
		SC_METHOD(write_data);
		sensitive << clk.pos();
	}
};


#endif
