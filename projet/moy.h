#ifndef MOY_H
#define MOY_H

#include <systemc.h>


SC_MODULE(MOY)
{
   
// IO PORTS
    
	sc_in<bool>         clk;
	sc_in<bool>         reset_n;
    
	sc_in<bool>        href_in;
	sc_in<bool>        vref_in;

	sc_out<bool>        href_out;
	sc_out<bool>        vref_out;
    
	sc_in<unsigned char> pixel_in;
	sc_out<unsigned char> pixel_out;

    
    
////////////////////////////////////////////////////
//	constructor
////////////////////////////////////////////////////

	SC_CTOR(MOY)
	{
		SC_CTHREAD(hack, clk.pos());
		reset_signal_is(reset_n, false);
		
		dont_initialize();
	}

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////
private:
	void hack();
};

#endif
