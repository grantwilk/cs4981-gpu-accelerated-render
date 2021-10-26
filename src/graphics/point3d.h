/* --------------------------------- Header --------------------------------- */


/**
 * @file    point3D.h
 * @brief   2D point class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_POINT3D_H
# define GRAPHICS_POINT3D_H


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "vector2.h"
# include "vector3.h"
# include "vector4.h"


/* --------------------------------- Class ---------------------------------- */


class Point3D : public Vector3<double>
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Point3D();
    Point3D( double x, double y, double z );
    explicit Point3D( const Vector3<double> &v );
    explicit Point3D( const Matrix<double> &m );
    Point3D( const Point3D &p );

    ~Point3D() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Point3D &operator=( const Point3D &p );

    Point3D &operator+=( const Point3D &p );
    Point3D &operator-=( const Point3D &p );

    Point3D operator+( const Point3D &p ) const;
    Point3D operator-( const Point3D &p ) const;

    bool operator<( const Point3D &p ) const;
    bool operator<=( const Point3D &p ) const;
    bool operator>( const Point3D &p ) const;
    bool operator>=( const Point3D &p ) const;

    /* ------------------------------ Functions ----------------------------- */


    Point3D *clone() const;

    Point3D transform( const Matrix<double> &m ) const;

    double magnitude() const;
    double angle( const Point3D &p ) const;

    std::ostream &out( std::ostream &os ) const override;

    static std::vector<Point3D*> vectorDeepCopy( const std::vector<Point3D*> &v );
    static void vectorDeepDelete( const std::vector<Point3D*> &v );

    static Vector2<Point3D*> vector2DeepCopy( const Vector2<Point3D*> &v );
    static void vector2DeepDelete( const Vector2<Point3D*> &v );

    static Vector3<Point3D*> vector3DeepCopy( const Vector3<Point3D*> &v );
    static void vector3DeepDelete( const Vector3<Point3D*> &v );

    static Vector4<Point3D*> vector4DeepCopy( const Vector4<Point3D*> &v );
    static void vector4DeepDelete( const Vector4<Point3D*> &v );


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Point3D &p );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_POINT3D_H


/* -------------------------------------------------------------------------- */