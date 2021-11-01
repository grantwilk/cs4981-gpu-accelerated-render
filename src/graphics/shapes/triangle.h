/* --------------------------------- Header --------------------------------- */


/**
 * @file    triangle.h
 * @brief   2D triangle shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_TRIANGLE_H
# define SHAPE_TRIANGLE_H


/* -------------------------------- Includes -------------------------------- */


# include "point3d.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class Triangle : public Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Triangle( const Point3D &start, const Point3D &mid, const Point3D &end );
    Triangle( const Point3D &start, const Point3D &mid, const Point3D &end, const Color &color );
    Triangle( const Triangle &tri );

    ~Triangle() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Triangle &operator=( const Triangle &triangle );

    const Point3D &operator[]( unsigned int index ) const override;
    Point3D &operator[]( unsigned int index ) override;


    /* ------------------------------ Functions ----------------------------- */


    void draw( GraphicsContext *gc ) const override;
    Triangle *clone() const override;

    std::ostream &out( std::ostream &os ) const override;


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Vector3<Point3D*> verts;


    /* ------------------------------ Functions ----------------------------- */


    static Point3D midpoint( const Point3D &a, const Point3D &b, const Point3D &c );


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Triangle &triangle );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_TRIANGLE_H


/* -------------------------------------------------------------------------- */
