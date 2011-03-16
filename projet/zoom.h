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

	void init(long _coeff)
	{
		SC_THREAD(get_pixels);
		sensitive << clk.pos();
		sensitive << reset_n;

		SC_THREAD(send_pixels);
		sensitive << clk.pos();
		sensitive << reset_n;

		coeff=_coeff;

		size=720/coeff*576/coeff  /2  +720/coeff;
		
		buffer=new unsigned char[size];

		sem=new sc_semaphore(1);
		sem->wait();
	}

	ZOOM(sc_module_name name, long _coeff):sc_module(name)
	{
		init(_coeff);

		start_i=(576-576/coeff)/2;
		start_j=(720-720/coeff)/2;
	}


	ZOOM(sc_module_name name, long i, long j, long _coeff):sc_module(name)
	{
		init(_coeff);

		start_i=(i<576/coeff)?i:0;
		start_j=(j<720/coeff)?j:0;
	}

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////


	SC_HAS_PROCESS(ZOOM);

private:
	long start_i, start_j,coeff;
	long size;
	unsigned char *buffer;
	sc_semaphore *sem;

	void get_pixels();
	void send_pixels();
};

#endif
