/* Provides a simple drawing context for X11/XWindows
 * You must have the X11 dev libraries installed.  If missing,
 * 'sudo apt-get install libx11-dev' should help.
 */

#include <iostream>
#include <X11/Xlib.h> // Every Xlib program must include this
#include <X11/Xutil.h> // needed for XGetPixel
#include <X11/XKBlib.h> // needed for keyboard setup

#include "drawbase.h"
#include "point2d.h"
#include "x11context.h"



/**
 * The only constructor provided.  Allows size of window and background
 * color be specified.
 * */
X11Context::X11Context(unsigned int sizex=400,unsigned int sizey=400,
						unsigned int bg_color=X11Context::BLACK)
{
	// Open the display
	display = XOpenDisplay(NULL);
	
	if (!display)
	{
		throw "Unable to open display";
	}
	// Holding a key in gives repeated key_press commands but only
	// one key_release
	int supported;
	
	XkbSetDetectableAutoRepeat(display,true,&supported);

	// Create a window - we will assume the color map is in RGB mode.  
	window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 
				 sizex, sizey, 0, 0 , bg_color);

	// Sign up for MapNotify events
	XSelectInput(display, window, StructureNotifyMask);

	// Put the window on the screen
	XMapWindow(display, window);

	// Create a "Graphics Context"
	graphics_context = XCreateGC(display, window, 0, NULL);

	// Default color to white
	XSetForeground( display, graphics_context, X11Context::WHITE);

	// Wait for MapNotify event
	for(;;) 
	{
		XEvent e;
		XNextEvent(display, &e);
		if (e.type == MapNotify)
		break;
	}

	// We also want exposure, mouse, and keyboard events
	XSelectInput(display, window, ExposureMask|
								ButtonPressMask|
								ButtonReleaseMask|
								KeyPressMask|
								KeyReleaseMask|
								PointerMotionMask);

	// We need this to get the WM_DELETE_WINDOW message from the
	// window manager in case user click the X icon
	Atom atomKill = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &atomKill, 1);

	return;
}


// Destructor  - shut down window and connection to server
X11Context::~X11Context()
{
	XFreeGC(display, graphics_context);
	XDestroyWindow(display,window);
	XCloseDisplay(display);
}


// Set the drawing mode - argument is enumerated
void X11Context::setMode(drawMode newMode)
{
	if ( newMode == X11Context::MODE_NORMAL)
	{
		XSetFunction(display,graphics_context,GXcopy);
	}
	else
	{
		XSetFunction(display,graphics_context,GXxor);
	}
}


// Set drawing color - assume colormap is 24 bit RGB
void X11Context::setColor(unsigned int color)
{
	// Go ahead and set color here - better performance than setting
	// on every setPixel 
    XSetForeground(display, graphics_context, color);
}


// Set a pixel in the current color
void X11Context::setPixel(int x, int y)
{
	XDrawPoint(display, window, graphics_context, x, y);
	XFlush(display);
}


// Get the color of a pixel
unsigned int X11Context::getPixel(int x, int y)
{
	XImage *image;
	image = XGetImage (display, window, x, y, 1, 1, AllPlanes, XYPixmap);
	XColor color;
	color.pixel = XGetPixel (image, 0, 0);
	XFree (image);
	XQueryColor (display, DefaultColormap(display, DefaultScreen (display)),
					&color);
	// I now have RGB values, but, they are 16 bits each, I only want 8-bits
	// each since I want a 24-bit RGB color value
	unsigned int pixcolor = color.red & 0xff00;
	pixcolor |= (color.green >> 8);
	pixcolor <<= 8;
	pixcolor |= (color.blue >> 8);
	return pixcolor;
}


// Draw a line in the current color
void X11Context::drawLine(int x1, int y1, int x2, int y2)
{
    XDrawLine(display, window, graphics_context, x1, y1, x2, y2);
    XFlush(display);
}


// Draw a circle in the current color
void X11Context::drawCircle(int x, int y, int radius)
{
    XDrawArc(display, window, graphics_context, x-radius,
             y-radius, radius*2, radius*2, 0, 360*64);
    XFlush(display);
}


// Clear graphics context
void X11Context::clear()
{
	XClearWindow(display, window);
	XFlush(display);
}


// Run event loop
void X11Context::runLoop(DrawingBase* drawing)
{
	run = true;
	
    drawing->paint(this);
	
	while(run)
	{
		XEvent e;
		XNextEvent(display, &e);

		// Exposure event - lets not worry about region
		if (e.type == Expose)
			drawing->paint(this);

		// Key Down
		else if (e.type == KeyPress)
			drawing->keyDown(this,XLookupKeysym((XKeyEvent*)&e,
					(((e.xkey.state&0x01)&&!(e.xkey.state&0x02))||
					(!(e.xkey.state&0x01)&&(e.xkey.state&0x02)))?1:0));
	 
		// Key Up
		else if (e.type == KeyRelease){
			drawing->keyUp(this,XLookupKeysym((XKeyEvent*)&e,
					(((e.xkey.state&0x01)&&!(e.xkey.state&0x02))||
					(!(e.xkey.state&0x01)&&(e.xkey.state&0x02)))?1:0));
				}

		// Mouse Button Down
		else if (e.type == ButtonPress)
			drawing->mouseButtonDown(this,
			e.xbutton.button,
			e.xbutton.x,
			e.xbutton.y);
			
		// Mouse Button Up
		else if (e.type == ButtonRelease)
			drawing->mouseButtonUp(this,
			e.xbutton.button,
			e.xbutton.x,
			e.xbutton.y);
			
		// Mouse Move	
		else if (e.type == MotionNotify)
			drawing->mouseMove(this,
			e.xmotion.x,
			e.xmotion.y);

		// This will respond to the WM_DELETE_WINDOW from the
		// window manager.
		else if (e.type == ClientMessage)
		break;
	}
}


// Get the width of the window
int X11Context::getWindowWidth()
{
	XWindowAttributes window_attributes;
	XGetWindowAttributes(display,window, &window_attributes);
	return window_attributes.width;
}


// Get the height of the window
int X11Context::getWindowHeight()
{
	XWindowAttributes window_attributes;
	XGetWindowAttributes(display,window, &window_attributes);
	return window_attributes.height;
}