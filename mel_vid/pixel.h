#ifndef PIXEL_H
#define PIXEL_H

#include "systemc.h"

struct Pixel
{
	sc_uint<8> r, g, b, a;

	Pixel():r(0),g(0),b(0),a(0){};
	Pixel(sc_uint<8> _r, sc_uint<8> _g, sc_uint<8> _b, sc_uint<8> _a)
		:r(_r),g(_g),b(_b),a(_a){};
	Pixel(const Pixel &p):r(p.r),g(p.g),b(p.b),a(p.a){};

	bool operator==(const Pixel &p){return r==p.r&&g==p.g&&b==p.b&&a==p.a;};
	Pixel operator+(const Pixel &p );
	friend std::ostream &operator << (std::ostream &o, const Pixel &p);

	void trace( sc_core::sc_trace_file* tf, const std::string &name) const;
};

namespace sc_core 
{
	void sc_trace( sc_core::sc_trace_file* tf, const Pixel &P, 
		       const std::string& name );
}

#endif
