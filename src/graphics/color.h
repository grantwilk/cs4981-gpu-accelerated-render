/* --------------------------------- Header --------------------------------- */


/**
 * @file    color.h
 * @brief   Floating point color class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_COLOR_H
# define GRAPHICS_COLOR_H


/* -------------------------------- Includes -------------------------------- */


# include "vector3.h"


/* --------------------------------- Class ---------------------------------- */


class Color : public Vector3<double>
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Color();
    Color( double r, double g, double b );
    Color( const Color &c );

    ~Color() = default;


    /* ------------------------ Overloaded Operators ------------------------ */


    Color &operator=( const Color &c );

    Color &operator+=( const Color &c );
    Color &operator-=( const Color &c );
    Color &operator*=( const Color &c );
    Color &operator/=( const Color &c );

    Color operator+( const Color &c );
    Color operator-( const Color &c );
    Color operator*( const Color &c );
    Color operator/( const Color &c );

    Color operator~();

    bool operator<( const Color &c ) const;
    bool operator<=( const Color &c ) const;
    bool operator>( const Color &c ) const;
    bool operator>=( const Color &c ) const;


    /* ------------------------------ Functions ----------------------------- */


    unsigned int toX11() const;

    double brightness() const;

    std::ostream &out( std::ostream &os ) const;


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


Color operator+( double scalar, const Color &c );
Color operator-( double scalar, const Color &c );
Color operator*( double scalar, const Color &c );
Color operator/( double scalar, const Color &c );

std::ostream &operator<<( std::ostream &os, const Color &c );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_COLOR_H


/* -------------------------------------------------------------------------- */