#include "systemc.h"

#include "mel_vid.h"

void next_cycle (sc_signal<bool> &signal_clk);

int sc_main(int argc, char *argv[])
{
	sc_signal<bool> clk;
	sc_signal<Pixel > p1, p2, out;

	sc_trace_file *my_trace_file;
	my_trace_file =
		sc_create_vcd_trace_file ("trace");
	sc_trace(my_trace_file, clk, "clk");

	sc_trace(my_trace_file, p1,"P1");
	sc_trace(my_trace_file, p2,"P2");
	sc_trace(my_trace_file, out,"Out");


	melanger mel("mel_vid");
	mel.clk(clk);
	mel.p1(p1);
	mel.p2(p2);
	mel.out(out);

	/*****Test du mélangeur*****/
	
	p1=Pixel(12,56,21,58);
	p2=Pixel(221,154,20,23);

	next_cycle(clk);
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



