#include "systemc.h"

#include "shift_reg.h"

void next_cycle (sc_signal<bool> &signal_clk);

int sc_main(int argc, char *argv[])
{
	sc_signal<bool> clk;


	sc_signal<sc_logic> in, out;

	sc_trace_file *my_trace_file;
	my_trace_file =
		sc_create_vcd_trace_file ("trace");
	sc_trace(my_trace_file, clk, "clk");

	sc_trace(my_trace_file, in,"in");
	sc_trace(my_trace_file, out,"out");


	shift_reg sr("registre_ a_decalage");
	sr.clk(clk);
	sr.in(in);
	sr.out(out);
	
	/*****Test du registre à décalage*****/

	for(int i=0 ; i<20 ; i++)
	{
		in=(i%4?(sc_logic)'1':(sc_logic)'0');
		next_cycle(clk);
	}
	/*********/
	
	sc_close_vcd_trace_file (my_trace_file);

	return EXIT_SUCCESS;

}

void next_cycle (sc_signal<bool> &signal_clk)
{
	signal_clk = false;
	sc_start (1, SC_NS);
	signal_clk = true;
	sc_start (1, SC_NS);
}



