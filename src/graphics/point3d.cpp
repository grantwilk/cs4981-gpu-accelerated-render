/* --------------------------------- Header --------------------------------- */


/**
 * @file    point3D.cpp
 * @brief   3D point class
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <cmath>

# include "point3d.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a 3D point at coordinates (0, 0)
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 *
 * @return  The created point
 */
Point3D::Point3D():
    Point3D( 0, 0, 0 )
{}


/**
 * @brief   Creates a 3D point at the specified coordinates
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 * @param   z   The z-coordinate
 *
 * @return  The created point
 */
Point3D::Point3D( double x, double y, double z ):
    Vector3<double>( x, y, z )
{}


/**
 * @brief   Creates a 3D point from a 3D vector of doubles
 *
 * @param   &v  The vector to create the 3D point from
 *
 * @return  The created point
 */
Point3D::Point3D( const Vector3<double> &v ):
    Point3D( v[0], v[1], v[2] )
{}


/**
 * @brief   Creates a 3D point from a 2x1 matrix of doubles
 *
 * @param   &m  The matrix to create the 3D point from
 *
 * @return  The created point
 */
Point3D::Point3D( const Matrix<double> &m ):
    Point3D( m[0][0], m[1][0], m[2][0] )
{
    if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
    {
        throw MatrixException( "Point3D construction matrix size mismatch" );
    }
}


/**
 * @brief   Creates a 3D point from an existing 3D point
 *
 * @param   point   The 3D point to create from
 *
 * @return  The created point
 */
Point3D::Point3D( const Point3D &p ):
    Point3D( p.getX(), p.getY(), p.getZ() )
{}


Point3D::~Point3D() = default;


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a 3D point to this 3D point
 *
 * @param   &p  The 3D point to assign
 *
 * @return  A reference to this 3D point
 */
Point3D &Point3D::operator=( const Point3D &p )
{
    setX( p.getX() );
    setY( p.getY() );
    setZ( p.getZ() );
    return *this;
}


/**
 * @brief   Adds a 3D point to this 3D point and assigns the sum to
 *          this 3D point
 *
 * @param   &p  The 3D point to add
 *
 * @return  A reference to this 3D point
 */
Point3D &Point3D::operator+=( const Point3D &p )
{
    return *this = *this + p;
}


/**
 * @brief   Subtracts a 3D point from this 3D point and assigns the
 *          difference to this 3D point
 *
 * @param   &p  The 3D point to subtract
 *
 * @return  A reference to this 3D point
 */
Point3D &Point3D::operator-=( const Point3D &p )
{
    return *this = *this - p;
}


/**
 * @brief   Adds a 3D point to this 3D point
 *
 * @param   &p  The 3D point to add
 *
 * @return  The sum of the 3D points
 */
Point3D Point3D::operator+( const Point3D &p ) const
{
    return Point3D( getX() + p.getX(), getY() + p.getY(), getZ() + p.getZ() );
}


/**
 * @brief   Subtracts a 3D point from this 3D point
 *
 * @param   &p  The 3D point to subtract
 *
 * @return  The difference of the 3D points
 */
Point3D Point3D::operator-( const Point3D &p ) const
{
    return Point3D( getX() - p.getX(), getY() - p.getY(), getZ() - p.getZ() );
}


/**
 * @brief   Determines if the magnitude of this 3D point is less than the
 *          magnitude of another 3D point
 *
 * @param   &p  The 3D point to compare against
 *
 * @return  True if the magnitude of this 3D point is less than the magnitude
 *          of the other point, false otherwise
 */
bool Point3D::operator<( const Point3D &p ) const
{
    return magnitude() < p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this 3D point is less than or equal
 *          to the magnitude of another 3D point
 *
 * @param   &p  The 3D point to compare against
 *
 * @return  True if the magnitude of this 3D point is less than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point3D::operator<=( const Point3D &p ) const
{
    return magnitude() <= p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this 3D point is greater than the
 *          magnitude of another 3D point
 *
 * @param   &p  The 3D point to compare against
 *
 * @return  True if the magnitude of this 3D point is greater than the magnitude
 *          of the other point, false otherwise
 */
bool Point3D::operator>( const Point3D &p ) const
{
    return magnitude() > p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this 3D point is greater than or
 *          equal to the magnitude of another 3D point
 *
 * @param   &p  The 3D point to compare against
 *
 * @return  True if the magnitude of this 3D point is greater than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point3D::operator>=( const Point3D &p ) const
{
    return magnitude() >= p.magnitude();
}


/**
 * @brief   Converts a 3D point to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &p      The 3D point to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Point3D &p )
{
    p.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */



/**
 * @brief   Creates a dynamically allocated clone of this 3D point
 *
 * @param   void
 *
 * @return  A pointer to cloned 3D point
 */
Point3D *Point3D::clone() const
{
    return new Point3D( getX(), getY(), getZ() );
}


/**
 * @brief   Calculates a transformed copy of this 3D point
 *
 * @param   &m  The 2D transformation matrix
 *
 * @return  A transformed copy of this 3D point
 */
Point3D Point3D::transform( const Matrix<double> &m ) const
{
    if ( ( m.getRows() != 4 ) || ( m.getColumns() != 4 ) )
    {
        throw MatrixException( "Point3D transformation matrix size mismatch." );
    }

    Matrix<double> transformVector = m * Vector4<double>( getX(), getY(), getZ(), 1 );

    return Point3D( transformVector[0][0], transformVector[1][0], transformVector[2][0] );
}


/**
 * @brief   Gets the magnitude of the vector between the origin and this
 *          3D point
 *
 * @param   void
 *
 * @return  The magnitude of the vector between the origin and this 3D point
 */
double Point3D::magnitude() const
{
    return sqrt( pow( getX(), 2 ) + pow( getY(), 2 ) + pow( getZ(), 2 ) );
}


/**
 * @brief   Gets the angle of the vector between this 3D point and another
 *          3D point in radians
 *
 * @param   void
 *
 * @return  The angle of the vector between this 3D point and another 2D
 *          point in radians
 */
double Point3D::angle( const Point3D &p ) const
{
    double dot = this->dot( p );
    double magSquared = pow( this->magnitude(), 2 );
    double pMagSquared = pow( p.magnitude(), 2 );
    return acos( dot / sqrt( magSquared * pMagSquared ) );
}


/**
 * @brief   Converts this 3D point to a string and writes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &Point3D::out( std::ostream &os ) const
{
    os << "Point3D( " << getX() << " " << getY() << " " << getZ() << " )";
    return os;
}


/**
 * @brief   Performs a deep copy of a vector of 3D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
std::vector<Point3D*> Point3D::vectorDeepCopy( const std::vector<Point3D*> &v )
{
    std::vector<Point3D*> clone = std::vector<Point3D*>();

    std::for_each( v.begin(), v.end(), [&clone]( Point3D *p )
       {
           Point3D *pClone = p->clone();
           clone.push_back( pClone );
       }
    );

    return clone;
}


/**
 * @brief   Performs a deep delete of a vector of 3D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point3D::vectorDeepDelete( const std::vector<Point3D*> &v )
{
    std::for_each( v.begin(), v.end(), []( Point3D *p )
       {
           delete p;
       }
    );
}


/**
 * @brief   Performs a deep copy a 3D vector of 3D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector2<Point3D*> Point3D::vector2DeepCopy( const Vector2<Point3D*> &v )
{
    return Vector2<Point3D*>( v[0]->clone(), v[1]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 3D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point3D::vector2DeepDelete( const Vector2<Point3D*> &v )
{
    delete v.getX();
    delete v.getY();
}


/**
 * @brief   Performs a deep copy a 3D vector of 3D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector3<Point3D*> Point3D::vector3DeepCopy( const Vector3<Point3D*> &v )
{
    return Vector3<Point3D*>( v[0]->clone(), v[1]->clone(), v[2]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 3D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point3D::vector3DeepDelete( const Vector3<Point3D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
}


/**
 * @brief   Performs a deep copy a 4D vector of 3D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector4<Point3D*> Point3D::vector4DeepCopy( const Vector4<Point3D*> &v )
{
    return Vector4<Point3D*>( v[0]->clone(), v[1]->clone(), v[2]->clone(), v[3]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 3D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point3D::vector4DeepDelete( const Vector4<Point3D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
    delete v.getW();
}


/* -------------------------------------------------------------------------- */