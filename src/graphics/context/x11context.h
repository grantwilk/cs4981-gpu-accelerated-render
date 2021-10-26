#ifndef X11_CONTEXT
#define X11_CONTEXT
/**
 * This class is a sample implementation of the GraphicsContext class
 * for the X11 / XWindows system.
 * */    
 
#include <X11/Xlib.h>   // Every Xlib program must include this
#include "gcontext.h"	// base class

class X11Context : public GraphicsContext
{
	public:
		// Default Constructor
		X11Context(unsigned int sizex,unsigned int sizey,unsigned int bg_color);

		// Destructor
		virtual ~X11Context();
		
		// Drawing Operations
		void setMode(drawMode newMode);
		void setColor(unsigned int color);
		void setPixel(int x, int y);
		unsigned int getPixel(int x, int y);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawCircle(int x, int y, int radius);
		void clear();

		/*
		 * These are not currently overridden, but could be as XLib
		 * has much more efficient implementations available.
		 */
		//void drawLine(int x1, int y1, int x2, int y2);
		//void drawCircle(int x, int y, int radius);


		// Event loop functions
		void runLoop(DrawingBase* drawing);
		
		// we will use endLoop provided by base class
		
		// Utility functions
		int getWindowWidth();
		int getWindowHeight();
		

	private:
		// X11 stuff - specific to this context
		Display* display;
		Window window;
		GC graphics_context;
};

#endif
