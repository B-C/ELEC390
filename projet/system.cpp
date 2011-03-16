/**********************************************************************
 * File : system.cpp
 * Date : 12/03/2008
 * Author :  Alexis Polti
 * 
 * This program is released under the GNU public license
 * ENST
 *
 * Testbench pour video_in
 **********************************************************************/

#include "systemc.h"
#include "video_in.h"
#include "video_out.h"
#include "moy.h"
#include "zoom.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


////////////////////////////////////////////////////
//	MAIN
////////////////////////////////////////////////////

int sc_main (int argc, char *argv[])
{

    int	ncycles;
    sc_time pix_period(74, SC_NS);
    
    
    if (argc == 2) {
        ncycles = atoi(argv[1]);
    } else{
        printf("\n");
        printf("The number of simulation cycles must be defined in the command line (-1 for unlimited)\n\n");
        exit(1);
    }
    
    
    
///////////////////////////////////////////////////////
//      Declaration des signaux
//////////////////////////////////////////////////////
        
        sc_clock                        signal_clk("Clock", pix_period);
        sc_signal<bool>                 signal_resetn;
        
        sc_signal<bool>                 signal_vref, signal_href,vref2,href2;
        sc_signal<unsigned char>        signal_pixel,pixel2;
        
        
        
/////////////////////////////////////////////////////////
//	Instanciation des composants
/////////////////////////////////////////////////////////

            VIDEO_IN video_in("VIDEO_IN");
	    VIDEO_OUT video_out("VIDEO_OUT");
//	    MOY hack("Moyenneur");
	    ZOOM hack("Zoom");
	
//////////////////////////////////////////////////////////
//	Connexion des composants
//////////////////////////////////////////////////////////
 
            video_in.clk        (signal_clk);
            video_in.reset_n    (signal_resetn);
            video_in.href       (signal_href);
            video_in.vref       (signal_vref);
            video_in.pixel_out  (signal_pixel);

	    hack.clk(signal_clk);
	    hack.reset_n(signal_resetn);
	    hack.href_in(signal_href);
	    hack.vref_in(signal_vref);
	    hack.pixel_in(signal_pixel);
	    hack.href_out(href2);
	    hack.vref_out(vref2);
	    hack.pixel_out(pixel2);

	    video_out.clk(signal_clk);
	    video_out.reset_n(signal_resetn);
	    video_out.href(href2);
	    video_out.vref(vref2);
	    video_out.pixel_in(pixel2);



            // // open trace file
            // sc_trace_file *my_trace_file;
            // my_trace_file = sc_create_vcd_trace_file ("simulation_trace");
  
            // // chronogrammes signaux CLK et NRESET
            // sc_trace(my_trace_file, signal_clk,         "clk");
            // sc_trace(my_trace_file, signal_resetn,      "reset_n");
  
            // // chronogrammes video
            // sc_trace(my_trace_file, signal_href,        "href");
            // sc_trace(my_trace_file, signal_vref,        "vref");
            // sc_trace(my_trace_file, signal_pixel,       "pixel");

            /* Initialisation de la simulation */
            signal_resetn = true;
            sc_start(pix_period);
            sc_start(pix_period);

            /* Generation d'un reset */
            signal_resetn = false;
            sc_start(pix_period);
            sc_start(pix_period);
            sc_start(pix_period);
            signal_resetn = true;

            /* Lancement de la simulation */
            int i=0;
            while(1) {

                /* Si on a atteint le nombre de cycles demandés, on s'arrête */
                if(ncycles > 0)
                    if(i >= ncycles)
                        break;
                sc_start(pix_period);
                i++;
                
                
            } // end simulation loop

            // Close trace file
            // sc_close_vcd_trace_file (my_trace_file);
            
            
            return EXIT_SUCCESS;
            
};
