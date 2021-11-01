/* --------------------------------- Header --------------------------------- */


/**
 * @file    line.cpp
 * @brief   Line shape
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>

# include "line.h"
# include "viewcontext.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a black line from two points
 *
 * @param   &start  The starting point of the line
 * @param   &end    The ending point of the line
 *
 * @return  The created line
 */
Line::Line( const Point3D &start, const Point3D &end ):
Line( start, end, Color( 0, 0, 0 ) )
{}


/**
 * @brief   Creates a colored line from two points
 *
 * @param   &start  The starting point of the line
 * @param   &end    The ending point of the line
 * @param   &color  The color of the line
 *
 * @return  The created line
 */
Line::Line( const Point3D &start, const Point3D &end, const Color &color ):
Shape( color, midpoint( start, end ) ),
verts( Vector2<Point3D*>( start.clone(), end.clone() ) )
{}


/**
 * @brief   Creates a line from an existing line
 *
 * @param   &line   The line to create from
 *
 * @return  The created line
 */
Line::Line( const Line &line ):
Shape( line.color, line.origin ), verts( line.verts )
{}


/**
 * @brief   Line destructor
 *
 * @param   void
 *
 * @return  void
 */
Line::~Line()
{
    Point3D::vector2DeepDelete( verts );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a line to this line
 *
 * @param   &line   The line to assign to this line
 *
 * @return  A reference to this line
 */
Line &Line::operator=( const Line &line )
{
    Point3D::vector2DeepDelete( verts );

    this->verts = Point3D::vector2DeepCopy( line.verts );
    this->color = line.color;
    this->origin = line.origin;

    return *this;
}


/**
 * @brief   Gets an immutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  An immutable reference to the vertex at the specified index
 */
const Point3D &Line::operator[]( unsigned int index ) const
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
Point3D &Line::operator[]( unsigned int index )
{
    return *verts[index];
}


/**
 * @brief   Converts a line to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &line   The line to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Line &line )
{
    line.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Draws this line to an graphics context
 *
 * @param   *gc     The graphics context to draw to
 * @param   *vc     The view context to draw with
 *
 * @return  void
 */
void Line::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    // convert from model to device coordinates
    Point3D start = vc->modelToDevice( *verts[0] );
    Point3D end = vc->modelToDevice( *verts[1] );

    // set color
    // gc->setColor( color.toX11() );

    // draw line
    gc->drawLine(
        ( int ) start.getX(), ( int ) start.getY(),
        ( int ) end.getX(),   ( int ) end.getY()
    );
}


/**
 * @brief   Clones this line
 *
 * @param   void
 *
 * @return  The cloned copy of this line
 */
Line *Line::clone() const
{
    return new Line( *verts[0], *verts[1], color );
}


/**
 * @brief   Converts this line to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Line::out( std::ostream &os ) const
{
    Shape::out( os );
    os << "  VERTICES( " << *verts[0] << " " << *verts[1] << " )";
    return os;
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Determines the midpoint between two points
 *
 * @param   &a   The first point
 * @param   &b   The second point
 *
 * @return  The midpoint between two points
 */
Point3D Line::midpoint( const Point3D &a, const Point3D &b )
{
    return Point3D(
        ( a.getX() + b.getX() ) / 2,
        ( a.getY() + b.getY() ) / 2,
        ( a.getZ() + b.getZ() ) / 2 );
}


/* -------------------------------------------------------------------------- */