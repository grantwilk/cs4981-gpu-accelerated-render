/* --------------------------------- Header --------------------------------- */


/**
 * @file    point2d.cpp
 * @brief   2D point class
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <cmath>

# include "point2d.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a 2D point at coordinates (0, 0)
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 *
 * @return  The created point
 */
Point2D::Point2D():
Point2D( 0, 0 )
{}


/**
 * @brief   Creates a 2D point at the specified coordinates
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 *
 * @return  The created point
 */
Point2D::Point2D( double x, double y ):
Vector2<double>( x, y )
{}


/**
 * @brief   Creates a 2D point from a 2D vector of doubles
 *
 * @param   &v  The vector to create the 2D point from
 *
 * @return  The created point
 */
Point2D::Point2D( const Vector2<double> &v ):
Point2D( v[0], v[1] )
{}


/**
 * @brief   Creates a 2D point from a 2x1 matrix of doubles
 *
 * @param   &m  The matrix to create the 2D point from
 *
 * @return  The created point
 */
Point2D::Point2D( const Matrix<double> &m ):
Point2D( m[0][0], m[1][0] )
{
    if ( ( m.getRows() != 2 ) || ( m.getColumns() != 1 ) )
    {
        throw MatrixException( "Point2D construction matrix size mismatch" );
    }
}


/**
 * @brief   Creates a 2D point from an existing 2D point
 *
 * @param   point   The 2D point to create from
 *
 * @return  The created point
 */
Point2D::Point2D( const Point2D &p ):
Point2D( p.getX(), p.getY() )
{}


Point2D::~Point2D() = default;


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a point to this point
 *
 * @param   &point  The point to assign
 *
 * @return  A reference to this point
 */
Point2D &Point2D::operator=( const Point2D &p )
{
    setX( p.getX() );
    setY( p.getY() );
    return *this;
}


/**
 * @brief   Adds a 2D point to this 2D point and assigns the sum to
 *          this 2D point
 *
 * @param   &point  The 2D point to add
 *
 * @return  A reference to this 2D point
 */
Point2D &Point2D::operator+=( const Point2D &p )
{
    return *this = *this + p;
}


/**
 * @brief   Subtracts a 2D point from this 2D point and assigns the
 *          difference to this 2D point
 *
 * @param   &point  The 2D point to subtract
 *
 * @return  A reference to this 2D point
 */
Point2D &Point2D::operator-=( const Point2D &p )
{
    return *this = *this - p;
}


/**
 * @brief   Adds a 2D point to this 2D point
 *
 * @param   &point  The 2D point to add
 *
 * @return  The sum of the 2D points
 */
Point2D Point2D::operator+( const Point2D &p ) const
{
    return Point2D( getX() + p.getX(), getY() + p.getY() );
}


/**
 * @brief   Subtracts a 2D point from this 2D point
 *
 * @param   &point  The 2D point to subtract
 *
 * @return  The difference of the 2D points
 */
Point2D Point2D::operator-( const Point2D &p ) const
{
    return Point2D( getX() - p.getX(), getY() - p.getY() );
}


/**
 * @brief   Determines if the magnitude of this point is less than the
 *          magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is less than the magnitude
 *          of the other point, false otherwise
 */
bool Point2D::operator<( const Point2D &p ) const
{
    return magnitude() < p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is less than or equal
 *          to the magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is less than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point2D::operator<=( const Point2D &p ) const
{
    return magnitude() <= p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is greater than the
 *          magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is greater than the magnitude
 *          of the other point, false otherwise
 */
bool Point2D::operator>( const Point2D &p ) const
{
    return magnitude() > p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is greater than or
 *          equal to the magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is greater than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point2D::operator>=( const Point2D &p ) const
{
    return magnitude() >= p.magnitude();
}


/**
 * @brief   Converts a 2D point to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &point  The 2D point to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Point2D &p )
{
    p.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */



/**
 * @brief   Creates a dynamically allocated clone of this 2D point
 *
 * @param   void
 *
 * @return  A pointer to cloned 2D point
 */
Point2D *Point2D::clone() const
{
    return new Point2D( getX(), getY() );
}


/**
 * @brief   Calculates a transformed copy of this 2D point
 *
 * @param   &m  The 2D transformation matrix
 *
 * @return  A transformed copy of this 2D point
 */
Point2D Point2D::transform( const Matrix<double> &m ) const
{
    if ( ( m.getRows() != 3 ) || ( m.getColumns() != 3 ) )
    {
        throw MatrixException( "Point2D transformation matrix size mismatch." );
    }

    Matrix<double> transformVector = m * Vector3<double>( getX(), getY(), 1 );

    return Point2D( transformVector[0][0], transformVector[1][0] );
}


/**
 * @brief   Gets the magnitude of the vector between the origin and this
 *          2D point
 *
 * @param   void
 *
 * @return  The magnitude of the vector between the origin and this 2D point
 */
double Point2D::magnitude() const
{
    return sqrt( pow( getX(), 2 ) + pow( getY(), 2 ) );
}


/**
 * @brief   Gets the magnitude of the angle between the origin-vector formed by
 *          this 2D point and the origin-vector formed by another 2D point in
 *          radians
 *
 * @param   void
 *
 * @return  The angle of the origin-vector formed by this 2D point and the
 *          origin-vector formed by another 2D point in radians
 */
double Point2D::angle( const Point2D &p ) const
{
    double dot = this->dot( p );
    double det = getX() * p.getY() - getY() * p.getX();
    return atan2( det, dot );
}


/**
 * @brief   Converts this 2D point to a string and writes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &Point2D::out( std::ostream &os ) const
{
    os << "POINT2D( " << getX() << " " << getY() << " )";
    return os;
}


/**
 * @brief   Performs a deep copy of a vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
std::vector<Point2D*> Point2D::vectorDeepCopy( const std::vector<Point2D*> &v )
{
    std::vector<Point2D*> clone = std::vector<Point2D*>();

    std::for_each( v.begin(), v.end(), [&clone]( Point2D *p )
                   {
                       Point2D *pClone = p->clone();
                       clone.push_back( pClone );
                   }
    );

    return clone;
}


/**
 * @brief   Performs a deep delete of a vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vectorDeepDelete( const std::vector<Point2D*> &v )
{
    std::for_each( v.begin(), v.end(), []( Point2D *p )
                   {
                       delete p;
                   }
    );
}


/**
 * @brief   Performs a deep copy a 2D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector2<Point2D*> Point2D::vector2DeepCopy( const Vector2<Point2D*> &v )
{
    return Vector2<Point2D*>( v[0]->clone(), v[1]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 2D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector2DeepDelete( const Vector2<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
}


/**
 * @brief   Performs a deep copy a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector3<Point2D*> Point2D::vector3DeepCopy( const Vector3<Point2D*> &v )
{
    return Vector3<Point2D*>( v[0]->clone(), v[1]->clone(), v[2]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector3DeepDelete( const Vector3<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
}


/**
 * @brief   Performs a deep copy a 4D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector4<Point2D*> Point2D::vector4DeepCopy( const Vector4<Point2D*> &v )
{
    return Vector4<Point2D*>( v[0]->clone(), v[1]->clone(), v[2]->clone(), v[3]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector4DeepDelete( const Vector4<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
    delete v.getW();
}


/* -------------------------------------------------------------------------- */