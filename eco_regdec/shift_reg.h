#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#include "systemc.h"

SC_MODULE(shift_reg)
{
	sc_in<bool> clk;

	sc_in<sc_logic> in;
	sc_out<sc_logic> out;

	sc_signal<sc_logic> reg[3];

	void reg_0(){reg[0]=in;};
	void reg_1(){reg[1]=reg[0];};
	void reg_2(){reg[2]=reg[1];};
	void reg_3(){out=reg[2];};

	SC_CTOR(shift_reg)
	{
		SC_METHOD(reg_0);
		sensitive << clk.pos();

		SC_METHOD(reg_1);
		sensitive << clk.pos();

		SC_METHOD(reg_2);
		sensitive << clk.pos();

		SC_METHOD(reg_3);
		sensitive << clk.pos();

	}
};

#endif
