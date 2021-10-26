/* --------------------------------- Header --------------------------------- */


/**
 * @file    shapecontainer.h
 * @brief   Set container of shape pointers
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_SHAPECONTAINER_H
# define GRAPHICS_SHAPECONTAINER_H


/* -------------------------------- Includes -------------------------------- */


# include <set>

# include "gcontext.h"
# include "viewcontext.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class ShapeContainer
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    ShapeContainer();
    ShapeContainer( const ShapeContainer &sc );

    ~ShapeContainer();


    /* ------------------------ Overloaded Operators ------------------------ */


    ShapeContainer &operator=( const ShapeContainer &sc );


    /* ------------------------------ Functions ----------------------------- */


    void add( const Shape &shape );
    void add( const ShapeContainer &sc );
    unsigned int size();

    void draw( GraphicsContext *gc, ViewContext *vc ) const;

    std::ostream &out( std::ostream &os ) const;

    void erase();


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    std::set<Shape*> shapes = std::set<Shape*>();


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const ShapeContainer &sc );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_SHAPECONTAINER_H


/* -------------------------------------------------------------------------- */