#include "pixel.h"

Pixel Pixel::operator+(const Pixel &p)
{
	Pixel ret(0,0,0,0);

	if(!(a==0&&p.a==0))
	{
		ret.r=(r*a+p.r*p.a)/(a+p.a);
		ret.g=(g*a+p.g*p.a)/(a+p.a);
		ret.b=(b*a+p.b*p.a)/(a+p.a);
		ret.a=(a>p.a)?a:p.a;
	}
	return ret;
}

void Pixel::trace( sc_core::sc_trace_file* tf, const std::string &name) const
{
#define __trace(x) sc_core::sc_trace(tf, x, name+"_"+#x)
	__trace(r);
	__trace(g);
	__trace(b);
	__trace(a);
#undef __trace
}

std::ostream &operator << (std::ostream &o, const Pixel &p)
{
	o  << "R: " << p.r
	   << endl
	   << "G: " << p.g
	   << endl
	   << "B: " << p.b
	   << endl
	   << "A: " << p.a
	   << endl;
	return o;
}

namespace sc_core 
{
	void sc_trace(sc_core::sc_trace_file* tf, const Pixel &P, 
		      const std::string& name)
	{
		P.trace(tf, name);
	}
}
