/* --------------------------------- Header --------------------------------- */


/**
 * @file    triangle.cpp
 * @brief   Triangle shape
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>
# include "color.h"
# include "triangle.h"


/* --------------------- Constructors / Destructors --------------------- */


/**
 * @brief   Creates a black triangle from three points
 *
 * @param   &start  The starting point of the triangle
 * @param   &mid    The middle point of the triangle
 * @param   &end    The ending point of the triangle
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Point3D &start, const Point3D &mid, const Point3D &end ):
Triangle( start, mid, end, Color( 0, 0, 0 ) )
{}


/**
 * @brief   Creates a colored triangle from three points
 *
 * @param   &start  The starting point of the triangle
 * @param   &mid    The middle point of the triangle
 * @param   &end    The ending point of the triangle
 * @param   &color  The color of the triangle
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Point3D &start, const Point3D &mid, const Point3D &end, const Color &color ):
Shape( color, midpoint( start, mid, end ) ),
verts( Vector3<Point3D*>( start.clone(), mid.clone(), end.clone() ) )
{}


/**
 * @brief   Creates a triangle from an existing triangle
 *
 * @param   &triangle   The triangle to create from
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Triangle &triangle ) :
Shape( triangle.color, triangle.origin ), verts( triangle.verts )
{}


/**
 * @brief   Triangle destructor
 *
 * @param   void
 *
 * @return  void
 */
Triangle::~Triangle()
{
    Point3D::vector3DeepDelete( verts );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a triangle to this triangle
 *
 * @param   &triangle   The triangle to assign to this triangle
 *
 * @return  A reference to this triangle
 */
Triangle &Triangle::operator=( const Triangle &triangle )
{
    Point3D::vector3DeepDelete( verts );

    this->verts = Point3D::vector3DeepCopy( triangle.verts );
    this->color = triangle.color;
    this->origin = triangle.origin;

    return *this;
}


/**
 * @brief   Gets an immutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  An immutable reference to the vertex at the specified index
 */
const Point3D &Triangle::operator[]( unsigned int index ) const
{
    return *verts[index];
}


/**
 * @brief   Gets a mutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  A mutable reference to the vertex at the specified index
 */
Point3D &Triangle::operator[]( unsigned int index )
{
    return *verts[index];
}


/**
 * @brief   Converts a triangle to a string and writes it to an output stream
 *
 * @param   &os         The output stream to write to
 * @param   &triangle   The triangle to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Triangle &triangle )
{
    triangle.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Draws this shape to a graphics context
 *
 * @param   *gc     The graphics context to draw to
 * @param   *vc     The view context to draw with
 *
 * @return  void
 */
void Triangle::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    // convert from model to device coordinates
    Point3D start = vc->modelToDevice( *verts[0] );
    Point3D mid = vc->modelToDevice( *verts[1] );
    Point3D end = vc->modelToDevice( *verts[2] );

    // set color
    // gc->setColor( color.toX11() );

    // draw lines
    gc->drawLine( ( int ) start.getX(), ( int ) start.getY(),
                  ( int ) mid.getX(),   ( int ) mid.getY() );

    gc->drawLine( ( int ) mid.getX(),   ( int ) mid.getY(),
                  ( int ) end.getX(),   ( int ) end.getY() );

    gc->drawLine( ( int ) end.getX(),   ( int ) end.getY(),
                  ( int ) start.getX(), ( int ) start.getY() );
}


/**
 * @brief   Clones this triangle
 *
 * @param   void
 *
 * @return  The cloned copy of this triangle
 */
Triangle *Triangle::clone() const
{
    return new Triangle( *verts[0], *verts[1], *verts[2], color );
}


/**
 * @brief   Converts this triangle to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Triangle::out( std::ostream &os ) const
{
    Shape::out( os );
    os << "  VERTICES( " << *verts[0] << " "
                         << *verts[1] << " "
                         << *verts[2] << " )";
    return os;
}


/* ---------------------------- Private Functions --------------------------- */

/**
 * @brief   Determines the midpoint between three points
 *
 * @param   &a  The first point
 * @param   &b  The second point
 * @param   &c  The third point
 *
 * @return  The midpoint between three points
 */
Point3D Triangle::midpoint( const Point3D &a, const Point3D &b, const Point3D &c )
{
    return Point3D(
        ( a.getX() + b.getX() + c.getX() ) / 3,
        ( a.getY() + b.getY() + c.getY() ) / 3,
        ( a.getZ() + b.getZ() + c.getZ() ) / 3 );
}

/* -------------------------------------------------------------------------- */