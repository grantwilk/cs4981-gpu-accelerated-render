/* --------------------------------- Header --------------------------------- */


/**
 * @file    point2d.h
 * @brief   2D point class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_POINT2D_H
# define GRAPHICS_POINT2D_H


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "matrix.h"
# include "vector2.h"
# include "vector3.h"
# include "vector4.h"


/* --------------------------------- Class ---------------------------------- */


class Point2D : public Vector2<float>
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Point2D();
    Point2D( float x, float y );
    explicit Point2D( const Vector2<float> &v );
    explicit Point2D( const Matrix<float> &m );
    Point2D( const Point2D &p );

    ~Point2D() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Point2D &operator=( const Point2D &p );

    Point2D &operator+=( const Point2D &p );
    Point2D &operator-=( const Point2D &p );

    Point2D operator+( const Point2D &p ) const;
    Point2D operator-( const Point2D &p ) const;

    bool operator<( const Point2D &p ) const;
    bool operator<=( const Point2D &p ) const;
    bool operator>( const Point2D &p ) const;
    bool operator>=( const Point2D &p ) const;

    /* ------------------------------ Functions ----------------------------- */


    Point2D *clone() const;

    Point2D transform( const Matrix<float> &m ) const;

    float magnitude() const;
    float angle( const Point2D &p ) const;

    std::ostream &out( std::ostream &os ) const override;

    static std::vector<Point2D*> vectorDeepCopy( const std::vector<Point2D*> &v );
    static void vectorDeepDelete( const std::vector<Point2D*> &v );

    static Vector2<Point2D*> vector2DeepCopy( const Vector2<Point2D*> &v );
    static void vector2DeepDelete( const Vector2<Point2D*> &v );

    static Vector3<Point2D*> vector3DeepCopy( const Vector3<Point2D*> &v );
    static void vector3DeepDelete( const Vector3<Point2D*> &v );

    static Vector4<Point2D*> vector4DeepCopy( const Vector4<Point2D*> &v );
    static void vector4DeepDelete( const Vector4<Point2D*> &v );


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Point2D &p );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_POINT2D_H


/* -------------------------------------------------------------------------- */