#ifndef ZOOM_H
#define ZOOMx_H

#include <systemc.h>


SC_MODULE(ZOOM)
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

	SC_CTOR(ZOOM)
	{
		SC_CTHREAD(hack, clk.pos());
		reset_signal_is(reset_n, false);
	}

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////
private:
	void hack();
};

#endif
