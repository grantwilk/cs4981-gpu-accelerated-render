#ifndef GCONTEXT_H
#define GCONTEXT_H

/**
 * This class is intended to be the abstract base class
 * for a graphical context for various platforms.  Any
 * concrete subclass will need to implement the pure virtual
 * methods to support setting pixels, getting pixel color,
 * setting the drawing mode, and running an event loop to
 * capture mouse and keyboard events directed to the graphics
 * context (or window).  Specific expectations for the various
 * methods are documented below.
 * 
 * Note, naive implementations of a line scan-conversion and a
 * circle scan-conversion are provided here which rely on the
 * concrete setPixel of the implemnting subclass.  These 
 * implementation are expected to be overridden for
 * better performance.
 * 
 * */    


// forward reference - needed because runLoop needs a target for events
class DrawingBase;


class GraphicsContext
{
	public:
		/*********************************************************
		 * Some constants and enums
		 *********************************************************/
		// This enumerated type is an argument to setMode and allows
		// us to support two different drawing modes.  MODE_NORMAL is
		// also call copy-mode and the affect pixel(s) are set to the 
		// color requested.  XOR mode will XOR the new color with the
		// existing color so that the change is reversible.		
		enum drawMode {MODE_NORMAL, MODE_XOR};
	
		// Some colors - for fun
		static const unsigned int BLACK = 0x000000;
		static const unsigned int BLUE = 0x0000FF;
		static const unsigned int GREEN = 0x00FF00;
		static const unsigned int RED = 0xFF0000;
		static const unsigned int CYAN = 0x00FFFF;
		static const unsigned int MAGENTA = 0xFF00FF;
		static const unsigned int YELLOW = 0xFFFF00;
		static const unsigned int GRAY = 0x808080;
		static const unsigned int WHITE = 0xFFFFFF;
	
	
		/*********************************************************
		 * Construction / Destruction
		 *********************************************************/
		// Implementations of this class should include a constructor
		// that creates the drawing canvas (window), sets a background
		// color (which may be configurable), sets a default drawing
		// color (which may be configurable), and start with normal
		// (copy) drawing mode.
	
		// need a virtual destructor to ensure subclasses will have
		// their destructors called properly.  Must be virtual.
		virtual ~GraphicsContext();

		/*********************************************************
		 * Drawing operations
		 *********************************************************/
		
		// Allows the drawing mode to be changed between normal (copy)
		// and xor.  The implementing context should default to normal. 
		virtual void setMode(drawMode newMode) = 0;

		// Set the current color.  Implementations should default to white.
		// color is 24-bit RGB value
		virtual void setColor(unsigned int color) = 0;

		// Set pixel to the current color
		virtual void setPixel(int x, int y) = 0;
		
		// Get 24-bit RGB pixel color at specified location
		// unsigned int will likely be 32-bit on 32-bit systems, and
		// possible 64-bit on some 64-bit systems.  In either case,
		// it is large enough to hold a 16-bit color.
		virtual unsigned int getPixel(int x, int y) = 0;

        virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
        virtual void drawCircle(int x, int y, int radius) = 0;

		// This should reset entire context to the current background
		virtual void clear() = 0;

		// These are the naive implementations that use setPixel,
		// but are overridable should a context have a better-
		// performing version available.


		/*********************************************************
		 * Event loop operations
		 *********************************************************/
		
		// Run Event loop.  This routine will receive events from
		// the implementation and pass them along to the drawing.  It
		// will return when the window is closed or other implementation-
		// specific sequence.
		virtual void runLoop(DrawingBase* drawing) = 0;
		
		// This method will end the current loop if one is running
		// a default version is supplied
		virtual void endLoop();


		/*********************************************************
		 * Utility operations
		 *********************************************************/
		
		// returns the width of the window
		virtual int getWindowWidth() = 0;
		
		// returns the height of the window
		virtual int getWindowHeight() = 0;
		
	protected:
		// this flag is used to control whether the event loop
		// continues to run.
		bool run;
};

#endif
