/* --------------------------------- Header --------------------------------- */


/**
 * @file    drawcontext.h
 * @brief   Context for the active drawing
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_CONTEXT_DRAWCONTEXT_H
# define GRAPHICS_CONTEXT_DRAWCONTEXT_H


/* -------------------------------- Includes -------------------------------- */


# include <vector>

# include "color.h"
# include "drawbase.h"
# include "point2d.h"
# include "shapecontainer.h"
# include "viewcontext.h"
#include "drawcontext.h"


/* --------------------------------- Class ---------------------------------- */


class DrawContext : public DrawingBase
{
    /* =============================== PUBLIC =============================== */

public:

    /* ----------------------------- Attributes ----------------------------- */


    static constexpr unsigned int KEY_CODE_0 = 48;
    static constexpr unsigned int KEY_CODE_1 = 49;
    static constexpr unsigned int KEY_CODE_2 = 50;
    static constexpr unsigned int KEY_CODE_3 = 51;
    static constexpr unsigned int KEY_CODE_4 = 52;
    static constexpr unsigned int KEY_CODE_5 = 53;
    static constexpr unsigned int KEY_CODE_6 = 54;
    static constexpr unsigned int KEY_CODE_7 = 55;
    static constexpr unsigned int KEY_CODE_8 = 56;
    static constexpr unsigned int KEY_CODE_9 = 57;

    static constexpr unsigned int KEY_CODE_A = 97;
    static constexpr unsigned int KEY_CODE_C = 99;
    static constexpr unsigned int KEY_CODE_O = 111;
    static constexpr unsigned int KEY_CODE_R = 114;
    static constexpr unsigned int KEY_CODE_S = 115;
    static constexpr unsigned int KEY_CODE_X = 120;
    static constexpr unsigned int KEY_CODE_Y = 121;

    static constexpr unsigned int KEY_CODE_ENTER = 65293;
    static constexpr unsigned int KEY_CODE_ESC = 65307;

    static constexpr unsigned int KEY_CODE_LEFT = 65361;
    static constexpr unsigned int KEY_CODE_UP = 65362;
    static constexpr unsigned int KEY_CODE_RIGHT = 65363;
    static constexpr unsigned int KEY_CODE_DOWN = 65364;

    static constexpr unsigned int KEY_CODE_SHIFT = 65505;
    static constexpr unsigned int KEY_CODE_LCTRL = 65507;
    static constexpr unsigned int KEY_CODE_RCTRL = 65508;

    static constexpr unsigned int MOUSE_BUTTON_LEFT = 1;
    static constexpr unsigned int MOUSE_BUTTON_CENTER = 2;
    static constexpr unsigned int MOUSE_BUTTON_RIGHT = 3;
    static constexpr unsigned int MOUSE_BUTTON_SCROLL_IN = 4;
    static constexpr unsigned int MOUSE_BUTTON_SCROLL_OUT = 5;


    /* --------------------- Constructors / Destructors --------------------- */


    explicit DrawContext( ViewContext *vc );
    ~DrawContext() override;


    /* ------------------------------ Functions ----------------------------- */


    void paint( GraphicsContext *gc ) override;
    void keyDown( GraphicsContext *gc, unsigned int keycode ) override;
    void keyUp( GraphicsContext *gc, unsigned int keycode ) override;
    void mouseButtonDown( GraphicsContext *gc, unsigned int button, int x, int y ) override;
    void mouseButtonUp( GraphicsContext *gc, unsigned int button, int x, int y ) override;
    void mouseMove( GraphicsContext *gc, int x, int y ) override;


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Color drawColor = Color( 0, 0, 0 );

    ShapeContainer sc = ShapeContainer();

    ViewContext *vc;

    bool drawAxis = true;

    bool panActive = false;
    bool orbitActive = false;

    Point2D mouseStartPos = Point2D( 0, 0 );
    Point2D lastMouseDelta = Point2D( 0, 0 );

    static constexpr unsigned int mouseDeltaThreshold = 8;


    /* ------------------------------ Functions ----------------------------- */


    void setDrawColor( GraphicsContext *gc, const Color &c );

    void draw3DAxis( GraphicsContext *gc );

    void fileOpen( GraphicsContext *gc );


    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_CONTEXT_DRAWCONTEXT_H


/* -------------------------------------------------------------------------- */