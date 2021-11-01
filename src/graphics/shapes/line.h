/* --------------------------------- Header --------------------------------- */


/**
 * @file    line.h
 * @brief   2D line shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_LINE_H
# define SHAPE_LINE_H


/* -------------------------------- Includes -------------------------------- */


# include "point3d.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class Line : public Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Line( const Point3D &start, const Point3D &end );
    Line( const Point3D &start, const Point3D &end, const Color &color );
    Line( const Line &line );

    ~Line() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Line &operator=( const Line &line );

    const Point3D &operator[]( unsigned int index ) const override;
    Point3D &operator[]( unsigned int index ) override;


    /* ------------------------------ Functions ----------------------------- */


    void draw( GraphicsContext *gc ) const override;
    Line *clone() const override;

    std::ostream &out( std::ostream &os ) const override;


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Vector2<Point3D*> verts;


    /* ------------------------------ Functions ----------------------------- */


    static Point3D midpoint( const Point3D &a, const Point3D &b );


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Line &line );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_LINE_H


/* -------------------------------------------------------------------------- */
