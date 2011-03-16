#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"


SC_MODULE(VIDEO_OUT)
{
   
// IO PORTS
    
	sc_in<bool>         clk;
	sc_in<bool>         reset_n;
    
	sc_in<bool>        href;
	sc_in<bool>        vref;
    
	sc_in<unsigned char> pixel_in;
    
    
////////////////////////////////////////////////////
//	constructor
////////////////////////////////////////////////////

	SC_CTOR(VIDEO_OUT)
	{
		SC_THREAD (gen_images);
		sensitive << clk.pos();
		sensitive << reset_n.neg();
		dont_initialize();

		base_name = "wallace_out";
            
		current_image_number = 0;
		image.pixel = NULL;
		
		std::cerr<<"Successful Instanciation of VIDEO_OUT module"<<std::endl;
	}

////////////////////////////////////////////////////
//	methods and structural parameters
////////////////////////////////////////////////////
private:
	void gen_images();    

	void write_images();

	
	const char *        base_name;              // nom de base des images d'entree
	int                 current_image_number;   // numero de l'image courante
	
	Image               image;
};

#endif
