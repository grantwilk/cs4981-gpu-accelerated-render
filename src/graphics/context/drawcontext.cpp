/* --------------------------------- Header --------------------------------- */


/**
 * @file    drawcontext.cpp
 * @brief   Context for the active drawing
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <iostream>
# include <cmath>

# include "drawcontext.h"
# include "line.h"
# include "shape.h"
# include "stlreader.h"


/* ----------------------- Constructors / Destructors ----------------------- */


DrawContext::DrawContext( ViewContext *vc ) :
    vc( vc )
{

}


DrawContext::~DrawContext() = default;


/* ---------------------------- Public Functions ---------------------------- */


void DrawContext::paint( GraphicsContext *gc )
{
    // clear the canvas
    gc->clear();

    // update view context
    vc->update();

    // draw 3D axis
    if ( drawAxis ) draw3DAxis( gc );

    // redraw shapes
    gc->setColor( drawColor.toX11() );
    sc.draw( gc, vc );
}


void DrawContext::keyDown( GraphicsContext *gc, unsigned int keycode )
{
    // std::cout << "Key Down: " << keycode << std::endl;

    switch ( keycode )
    {
        // NUMROW 0: set color random
        case DrawContext::KEY_CODE_0:
        {
            std::cout << "COLOR SET: RANDOM" << std::endl;
            double r = (( double ) ( rand() % 100 ) ) / 100;
            double g = (( double ) ( rand() % 100 ) ) / 100;
            double b = (( double ) ( rand() % 100 ) ) / 100;
            setDrawColor( gc, Color( r, g, b ) );
            break;
        }

        // NUMROW 1: set color black
        case DrawContext::KEY_CODE_1:
            std::cout << "COLOR SET: BLACK" << std::endl;
            setDrawColor( gc, Color( 0, 0, 0 ) );
            break;

        // NUMROW 2: set color gray
        case DrawContext::KEY_CODE_2:
            std::cout << "COLOR SET: GRAY" << std::endl;
            setDrawColor( gc, Color( 0.4, 0.4, 0.4 ) );
            break;

        // NUMROW 3: set color white
        case DrawContext::KEY_CODE_3:
            std::cout << "COLOR SET: WHITE" << std::endl;
            setDrawColor( gc, Color( 1, 1, 1 ) );
            break;

        // NUMROW 4: set color red
        case DrawContext::KEY_CODE_4:
            std::cout << "COLOR SET: RED" << std::endl;
            setDrawColor( gc, Color( 1, 0, 0 ) );
            break;

        // NUMROW 5: set color green
        case DrawContext::KEY_CODE_5:
            std::cout << "COLOR SET: GREEN" << std::endl;
            setDrawColor( gc, Color( 0.1, 0.9, 0 ) );
            break;

        // NUMROW 6: set color blue
        case DrawContext::KEY_CODE_6:
            std::cout << "COLOR SET: BLUE" << std::endl;
            setDrawColor( gc, Color( 0.1, 0.3, 1 ) );
            break;

        // NUMROW 7: set color cyan
        case DrawContext::KEY_CODE_7:
            std::cout << "COLOR SET: CYAN" << std::endl;
            setDrawColor( gc, Color( 0, 0.8, 1 ) );
            break;

        // NUMROW 8: set color magenta
        case DrawContext::KEY_CODE_8:
            std::cout << "COLOR SET: MAGENTA" << std::endl;
            setDrawColor( gc, Color( 0.9, 0, 0.9 ) );
            break;

        // NUMROW 9: set color yellow
        case DrawContext::KEY_CODE_9:
            std::cout << "COLOR SET: YELLOW" << std::endl;
            setDrawColor( gc, Color( 1, 0.8, 0 ) );
            break;

        // A: toggle draw axes
        case DrawContext::KEY_CODE_A:
            drawAxis = !drawAxis;
            std::cout << "DRAW 3D AXIS: " << ( drawAxis ? "ENABLED" : "DISABLED" ) << std::endl;
            paint( gc );
            break;

        // O: open drawing
        case DrawContext::KEY_CODE_O:
            fileOpen( gc );
            break;

        // R: reset view
        case DrawContext::KEY_CODE_R:
            vc->resetView();
            paint( gc );
            break;

        // LEFT: left view
        case DrawContext::KEY_CODE_LEFT:
            vc->setRotation( ( -1 * M_PI_2 ), 0 );
            paint( gc );
            break;

        // RIGHT: right view
        case DrawContext::KEY_CODE_RIGHT:
            vc->setRotation( M_PI_2, 0 );
            paint( gc );
            break;

        // UP: top view
        case DrawContext::KEY_CODE_UP:
            vc->setRotation( 0, M_PI_2 );
            paint( gc );
            break;

        // DOWN: bottom view
        case DrawContext::KEY_CODE_DOWN:
            vc->setRotation( 0, ( -1 * M_PI_2 ) );
            paint( gc );
            break;

        default:
            break;
    }
}


void DrawContext::keyUp( GraphicsContext *gc, unsigned int keycode )
{
    // std::cout << "Key Up: " << keycode << std::endl;
}


void DrawContext::mouseButtonDown( GraphicsContext *gc, unsigned int button, int x, int y )
{

    // Point2D deviceCoords = Point2D( x, y );
    // Point2D modelCoords = vc->deviceToModel( deviceCoords );
    // std::cout << "Mouse Down: " << button << " at " << deviceCoords << " -> " << modelCoords << std::endl;

    // LMB down - start pan
    if ( ( button == MOUSE_BUTTON_LEFT ) && ( !panActive ) && ( !orbitActive ) )
    {
        panActive = true;
        mouseStartPos = Point2D( x, y );
        lastMouseDelta = Point2D( 0, 0 );
    }

    // MMB down - start orbit
    else if ( ( button == MOUSE_BUTTON_RIGHT ) && ( !panActive ) && ( !orbitActive ) )
    {
        orbitActive = true;
        mouseStartPos = Point2D( x, y );
        lastMouseDelta = Point2D( 0, 0 );
    }

    // scroll forward - zoom in
    else if ( ( button == MOUSE_BUTTON_SCROLL_IN ) && ( !panActive ) && ( !orbitActive ) )
    {
        vc->scale( 1.05, 1.05, 1 );
        paint( gc );
    }

    // scroll backward - zoom out
    else if ( ( button == MOUSE_BUTTON_SCROLL_OUT ) && ( !panActive ) && ( !orbitActive ) )
    {
        vc->scale( 1 / 1.05, 1 / 1.05, 1 );
        paint( gc );
    }
}


void DrawContext::mouseButtonUp( GraphicsContext *gc, unsigned int button, int x, int y )
{
    // std::cout << "Mouse Up: " << button << " at (" << x << ", " << y << ")" << std::endl;

    // LMB up - stop pan
    if ( button == MOUSE_BUTTON_LEFT  )
    {
        double scale = vc->getScale()[0];
        vc->pan(
            lastMouseDelta.getX() / scale,
            -lastMouseDelta.getY() / scale
        );
        paint( gc );
        panActive = false;
    }

    // MMB up - stop orbit
    else if ( button == MOUSE_BUTTON_RIGHT  )
    {
        vc->rotate(
            lastMouseDelta.getY() / 200,
            lastMouseDelta.getX() / 200
        );

        paint( gc );

        orbitActive = false;
    }
}


void DrawContext::mouseMove( GraphicsContext *gc, int x, int y )
{
    // std::cout << "Mouse Move: (" << x << ", " << y << ")" << std::endl;

    // pan handler
    if ( panActive )
    {
        Point2D mouseCurrentPos = Point2D( x, y );
        Point2D mouseDelta = mouseCurrentPos - mouseStartPos;

        if ( std::abs( lastMouseDelta.magnitude() - mouseDelta.magnitude() ) > mouseDeltaThreshold )
        {
            double scale = vc->getScale()[0];
            Vector3<double> currentTranslation = vc->getTranslation();

            vc->pan(
                mouseDelta.getX() / scale,
                -mouseDelta.getY() / scale
            );

            paint( gc );

            vc->setTranslation(
                currentTranslation.getX(),
                currentTranslation.getY(),
                currentTranslation.getZ()
            );

            lastMouseDelta = mouseDelta;
        }
    }

    // orbit handler
    else if ( orbitActive )
    {
        Point2D mouseCurrentPos = Point2D( x, y );
        Point2D mouseDelta = mouseCurrentPos - mouseStartPos;

        if ( std::abs( lastMouseDelta.magnitude() - mouseDelta.magnitude() ) > mouseDeltaThreshold )
        {
            Vector2<double> currentRotation = vc->getRotation();

            vc->rotate(
                mouseDelta.getY() / 200,
                mouseDelta.getX() / 200
            );

            paint( gc );

            vc->setRotation(
                currentRotation.getX(),
                currentRotation.getY()
            );

            lastMouseDelta = mouseDelta;
        }

    }
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Sets the draw color of the view
 *
 * @param   *gc     The graphics context to draw to
 * @param   &c      The draw color
 *
 * @return  void
 */
void DrawContext::setDrawColor( GraphicsContext *gc, const Color &c )
{
    drawColor = c;
    gc->setColor( drawColor.toX11() );
    paint( gc );
}


/**
 * @brief   Draws a 3D axis to a graphics context
 *
 * @param   *gc     The graphics context to draw to
 *
 * @return  void
 */
void DrawContext::draw3DAxis( GraphicsContext *gc )
{
    Point3D origin = Point3D( 0, 0, 0 );
    Point3D xUnitVector = Point3D( 1, 0, 0 );
    Point3D yUnitVector = Point3D( 0, 1, 0 );
    Point3D zUnitVector = Point3D( 0, 0, 1 );

    Line xAxis = Line( origin, xUnitVector );
    Line yAxis = Line( origin, yUnitVector );
    Line zAxis = Line( origin, zUnitVector );

    gc->setColor( Color( 1, 0, 0 ).toX11() );
    xAxis.draw( gc, vc );

    gc->setColor( Color( 0, 1, 0 ).toX11() );
    yAxis.draw( gc, vc );

    gc->setColor( Color( 0, 0, 1 ).toX11() );
    zAxis.draw( gc, vc );
}


/**
 * @brief   Clears the canvas and opens a new drawing from file
 *
 * @param   *gc     The graphics context to draw to
 *
 * @return  void
 */
void DrawContext::fileOpen( GraphicsContext *gc )
{
    // get file name
    std::cout << "OPEN FILE: ";
    std::string fileName;
    std::cin >> fileName;

    // open file and read facets
    STLReader stlReader = STLReader( fileName );
    sc = stlReader.readFacets();

    // reset view and paint
    vc->resetView();
    paint( gc );
}


/* -------------------------------------------------------------------------- */