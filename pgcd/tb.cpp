#include <iostream>

#include "systemc.h"

#include "pgcd.h"

using namespace std;

void next_cycle (sc_signal<bool> &signal_clk);

int sc_main(int argc, char *argv[])
{
	sc_signal<bool> clk;
	sc_signal<unsigned char> x,y;
	sc_signal<unsigned char> pgcd;
	sc_signal<bool> start;
	sc_signal<bool> done;

	// sc_trace_file *my_trace_file;
	// my_trace_file =
	// 	sc_create_vcd_trace_file ("trace");

	// sc_trace(my_trace_file, clk, "clk");
	// sc_trace(my_trace_file, x, "x");
	// sc_trace(my_trace_file, y, "y");
	// sc_trace(my_trace_file, pgcd, "pgcd");
	// sc_trace(my_trace_file, start, "start");
	// sc_trace(my_trace_file, done, "done");

//	Pgcd_hl calc("PGCD");
	Pgcd calc("PGCD");
	calc.clk(clk);
	calc.x(x);
	calc.y(y);
	calc.pgcd(pgcd);
	calc.start(start);
	calc.done(done);
	
	/*****Test du PGCD (exhaustif) *****/

	long good=0,bad=0;
	

	for(int i= 0 ; i<=0xFF ; i++)
		for(int j=i ; j<=0xFF ; j++)
		{
			x=i;
			y=j;
			start=1;
			next_cycle(clk);
			start=0;

			while(!done)
				next_cycle(clk);

			if(pgcd!=euclide(i,j))
			{
				cerr<<"Error : PGCD("<<i<<","<<j<<") = "
				    <<euclide(i,j)<<" != "<<pgcd<<endl;
				bad++;
			}
			else
				good++;
		}

	cout<<"Done. Good : "<<good<<", bad : "<<bad<<endl;

	/*********/
	
	// sc_close_vcd_trace_file(my_trace_file);

	return EXIT_SUCCESS;

}

void next_cycle (sc_signal<bool> &signal_clk)
{
	signal_clk = false;
	sc_start (1, SC_NS);
	signal_clk = true;
	sc_start (1, SC_NS);
}



