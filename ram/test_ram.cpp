#include "systemc.h"
#include "ram.h"
#include "compt.h"
#include "multiples.h"

void next_cycle (sc_signal<bool> &signal_clk);

int sc_main(int argc, char *argv[])
{
	int i;
    
	sc_signal<bool> clk;
	sc_signal<sc_int<8> > addr_in;
	sc_signal<sc_int<16> > data_in;
	sc_signal<bool> wen;

	sc_signal<sc_int<8> > addr_out;
	sc_signal<sc_int<16> > data_out;


	sc_signal<bool> reset;
	sc_signal<bool> load;
	sc_signal<sc_uint<8> >in_co,out_co, out_m;


	sc_trace_file *my_trace_file;
	my_trace_file =
		sc_create_vcd_trace_file ("trace");
	sc_trace(my_trace_file, clk, "clk");
	sc_trace(my_trace_file, addr_in,"addr_in");
	sc_trace(my_trace_file, data_in,"data_in");
	sc_trace(my_trace_file, wen,"wen");
	sc_trace(my_trace_file, addr_out,"addr_out");
	sc_trace(my_trace_file, data_out,"data_out");

	sc_trace(my_trace_file,reset,"reset");
	sc_trace(my_trace_file,load,"load");
	sc_trace(my_trace_file,in_co,"in_co");
	sc_trace(my_trace_file,out_co,"out_co");
	sc_trace(my_trace_file,out_m,"out_m");

	ram mem("ram_sync");
	mem.clk(clk);
	mem.addr_in(addr_in);
	mem.data_in(data_in);
	mem.wen(wen);
	mem.addr_out(addr_out);
	mem.data_out(data_out);

	compteur cpt("compteur");
	cpt.clk(clk);
	cpt.reset(reset);
	cpt.load(load);
	cpt.in(in_co);
	cpt.out(out_co);
	
	multiples mtp("multiples_2_3");
	mtp.clk(clk);
	mtp.reset(reset);
	mtp.out(out_m);


	load=false;
	reset=false;
	next_cycle(clk);
	reset=true;

	/*****Test de la ram *****/
	wen=1;
	addr_out=0;

	for(i=0; i<17; i++)
		next_cycle(clk);

	addr_in= 10;
	data_in=0b1111000011110000;
	wen=0;
	next_cycle(clk);
	wen=1;

	for(i=0; i<17; i++)
		next_cycle(clk);

	addr_out=10;
	next_cycle(clk);
	/*********/

	for(i=0; i<255; i++)
		next_cycle(clk);
	
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



