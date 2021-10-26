/* --------------------------------- Header --------------------------------- */


/**
 * @file    color.cpp
 * @brief   Floating point color class
 */


/* -------------------------------- Includes -------------------------------- */


# include <iostream>
# include "color.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a color with channel values (0, 0, 0)
 *
 * @param   void
 *
 * @return  The created color
 */
Color::Color():
Color( 0, 0 ,0 )
{}


/**
 * @brief   Creates a color with the specified channel values
 *
 * @param   r   The color's red channel
 * @param   g   The color's green channel
 * @param   b   The color's blue channel
 *
 * @return  The created color
 */
Color::Color( double r, double g, double b ):
Vector3<double>( r, g, b )
{}


/**
 * @brief   Creates a color from an already existing color
 *
 * @param   &c  The color to create from
 *
 * @return  The created color
 */
Color::Color( const Color &c ):
Color( c.getX(), c.getY(), c.getZ() )
{}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a color to this color
 *
 * @param   &c  The color to assign
 *
 * @return  A reference to this color
 */
Color &Color::operator=( const Color &c )
{
    setX( c.getX() );
    setY( c.getY() );
    setZ( c.getZ() );
    return *this;
}


/**
 * @brief   Adds a color to this color and assigns the sum to this color
 *
 * @param   &c  The color to add
 *
 * @return  A reference to this color
 */
Color &Color::operator+=( const Color &c )
{
    return *this = ( *this ) + c;
}


/**
 * @brief   Subtracts a color from this color and assigns the difference to
 *          this color
 *
 * @param   &c  The color to subtract
 *
 * @return  A reference to this color
 */
Color &Color::operator-=( const Color &c )
{
    return *this = ( *this ) - c;
}


/**
 * @brief   Multiplies a color by this color and assigns the product to
 *          this color
 *
 * @param   &c  The color to multiply by
 *
 * @return  A reference to this color
 */
Color &Color::operator*=( const Color &c )
{
    return *this = ( *this ) * c;
}


/**
 * @brief   Divides this color by another color and assigns the quotient to
 *          this color
 *
 * @param   &c  The color to divide by
 *
 * @return  A reference to this color
 */
Color &Color::operator/=( const Color &c )
{
    return *this = ( *this ) / c;
}


/**
 * @brief   Adds a color to this color
 *
 * @param   &c  The color to add
 *
 * @return  The sum of the colors
 */
Color Color::operator+( const Color &c )
{
    return Color( getX() + c.getX(), getY() + c.getY(), getZ() + c.getZ() );
}


/**
 * @brief   Subtracts a color from this color
 *
 * @param   &c  The color to subtract
 *
 * @return  The difference of the colors
 */
Color Color::operator-( const Color &c )
{
    return Color( getX() - c.getX(), getY() - c.getY(), getZ() - c.getZ() );
}


/**
 * @brief   Multiplies a color by this color
 *
 * @param   &c  The color to multiply by
 *
 * @return  The product of the colors
 */
Color Color::operator*( const Color &c )
{
    return Color( getX() * c.getX(), getY() * c.getY(), getZ() * c.getZ() );
}


/**
 * @brief   Divides this color by another color
 *
 * @param   &c  The color to divide by
 *
 * @return  The quotient of the colors
 */
Color Color::operator/( const Color &c )
{
    return Color( getX() / c.getX(), getY() / c.getY(), getZ() / c.getZ() );
}


/**
 * @brief   Inverts a color
 *
 * @param   void
 *
 * @return  The inverted color
 */
Color Color::operator~()
{
    return Color( 1 - getX(), 1 - getY(), 1 - getZ() );
}


/**
 * @brief   Determines if the average brightness of this color is less than
 *          the average brightness of another color
 *
 * @param   &c   The color to compare against
 *
 * @return  True if the average brightness of this color is less than the
 *          average brightness of another color, false otherwise
 */
bool Color::operator<( const Color &c ) const
{
    return brightness() < c.brightness();
}


/**
 * @brief   Determines if the average brightness of this color is less than or
 *          equal to the average brightness of another color
 *
 * @param   &c   The color to compare against
 *
 * @return  True if the average brightness of this color is less than or equal
 *          to the average brightness of another color, false otherwise
 */
bool Color::operator<=( const Color &c ) const
{
    return brightness() <= c.brightness();
}


/**
 * @brief   Determines if the average brightness of this color is greater than
 *          the average brightness of another color
 *
 * @param   &c   The color to compare against
 *
 * @return  True if the average brightness of this color is greater than the
 *          average brightness of another color, false otherwise
 */
bool Color::operator>( const Color &c ) const
{
    return brightness() > c.brightness();
}


/**
 * @brief   Determines if the average brightness of this color is greater than
 *          or equal to the average brightness of another color
 *
 * @param   &c   The color to compare against
 *
 * @return  True if the average brightness of this color is greater than or
 *          equal to the average brightness of another color, false otherwise
 */
bool Color::operator>=( const Color &c ) const
{
    return brightness() >= c.brightness();
}


/**
 * @brief   Adds each channel of a color to a scalar value
 *
 * @param   scalar  The scalar value to add
 * @param   &c      The color to add to
 *
 * @return  The sum of the scalar and the color
 */
Color operator+( double scalar, const Color &c )
{
    return Color( scalar + c.getX(), scalar + c.getY(), scalar + c.getZ() );
}


/**
 * @brief   Subtracts each channel of a color from a scalar value
 *
 * @param   scalar  The scalar value to subtract from
 * @param   &c      The color to subtract
 *
 * @return  The difference of the scalar and the color
 */
Color operator-( double scalar, const Color &c )
{
return Color( scalar - c.getX(), scalar - c.getY(), scalar - c.getZ() );
}


/**
 * @brief   Multiplies a scalar by each channel of a color
 *
 * @param   scalar  The scalar value to multiply
 * @param   &c      The color to multiply by
 *
 * @return  The product of the scalar and the color
 */
Color operator*( double scalar, const Color &c )
{
return Color( scalar * c.getX(), scalar * c.getY(), scalar * c.getZ() );
}


/**
 * @brief   Divides a scalar value by each channel of a color
 *
 * @param   scalar  The scalar value to divide
 * @param   &c      The color to divide by
 *
 * @return  The quotient of the scalar and the color
 */
Color operator/( double scalar, const Color &c )
{
return Color( scalar / c.getX(), scalar / c.getY(), scalar / c.getZ() );
}


/**
 * @brief   Converts a color to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &c      The color to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Color &c )
{
    c.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Converts this color to an X11 compatible color
 *
 * @param   void
 *
 * @return  An X11 compatible color
 */
unsigned int Color::toX11() const
{
    return  ( ( ( int ) ( getX() * 255 ) ) << 16 ) +
            ( ( ( int ) ( getY() * 255 ) ) << 8 )  +
            ( ( ( int ) ( getZ() * 255 ) ) << 0);
}

/**
 * @brief   Calculates the average brightness of this color
 *
 * @param   void
 *
 * @return  The average brightness of this color
 */
double Color::brightness() const
{
    return ( getX() + getY() + getZ() ) / 3;
}

/**
 * @brief   Converts this color to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &Color::out( std::ostream &os ) const
{
    os << "COLOR(" << getX() << " " << getY() << " " << getZ() << ")";
    return os;
}


/* -------------------------------------------------------------------------- */