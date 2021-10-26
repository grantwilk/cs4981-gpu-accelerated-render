#ifndef DRAWBASE_H
#define DRAWBASE_H

// forward reference
class GraphicsContext;

class DrawingBase
{
	public:
        DrawingBase() = default;
		virtual ~DrawingBase() = default;
		virtual void paint( GraphicsContext *gc) = 0;
		virtual void keyDown( GraphicsContext *gc, unsigned int keycode) = 0;
		virtual void keyUp( GraphicsContext *gc, unsigned int keycode) = 0;
		virtual void mouseButtonDown( GraphicsContext *gc, unsigned int button, int x, int y) = 0;
		virtual void mouseButtonUp( GraphicsContext *gc, unsigned int button, int x, int y) = 0;
		virtual void mouseMove( GraphicsContext *gc, int x, int y) = 0;
};
#endif
