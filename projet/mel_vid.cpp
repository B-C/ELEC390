#include "mel_vid.h"

void melanger::compute()
{
	Pixel pi=p1.read(), pii=p2.read();
	out=pi+pii;
}
