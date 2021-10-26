/* --------------------------------- Header --------------------------------- */


/**
 * @file    main.cpp
 * @brief   Application Entry Point
 */


/* -------------------------------- Includes -------------------------------- */


# include "drawcontext.h"
# include "viewcontext.h"
# include "x11context.h"

using namespace std;


/* ------------------------------- Functions -------------------------------- */


int main()
{
    /* ---------------- Create Graphics and Drawing Context ----------------- */


    GraphicsContext *gc = new X11Context( 800, 800, X11Context::WHITE );
    ViewContext *vc = new ViewContext( gc );
    DrawContext *dc = new DrawContext( vc );

    /* ---------------------------- Print Header ---------------------------- */

    cout << endl;
    cout << "/* ====== Grant's Spectacular 3D Art Designer ====== */" << endl;
    cout << endl;
    cout << endl;
    cout << "  VIEW CONTROLS:" << endl;
    cout << "  LMB    - Pan" << endl;
    cout << "  MMB    - Orbit" << endl;
    cout << "  SCROLL - Zoom" << endl;
    cout << "  R      - Reset 3D View" << endl;
    cout << "  A      - Toggle 3D Axis" << endl;
    cout << "  CTRL   - Toggle Color Target" << endl;
    cout << endl;
    cout << "  FILE CONTROLS:" << endl;
    cout << "  O - Open File" << endl;
    cout << endl;
    cout << "  COLOR OPTIONS:" << endl;
    cout << "  1 - Black    6 - Blue" << endl;
    cout << "  2 - Gray     7 - Cyan" << endl;
    cout << "  3 - White    8 - Magenta" << endl;
    cout << "  4 - Red      9 - Yellow" << endl;
    cout << "  5 - Green    0 - Random" << endl;
    cout << endl;
    cout << endl;
    cout << "/* ------------------------------------------------- */" << endl;
    cout << endl;

    /* --------------------------- Enter Run Loop --------------------------- */


    gc->runLoop( dc );


    /* ---------------------- Delete Graphics Context ----------------------- */


    delete dc;
    delete vc;
    delete gc;


    /* ---------------------------------------------------------------------- */
}
