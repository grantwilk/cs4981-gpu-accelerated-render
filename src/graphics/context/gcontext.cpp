/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include <algorithm>
#include "gcontext.h"

using namespace std;

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}

void GraphicsContext::endLoop()
{
	run = false;
}


