/* --------------------------------- Header --------------------------------- */


/**
 * @file    vector3.h
 * @brief   Templated 3D vector class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef MATRIX_VECTOR3_H
# define MATRIX_VECTOR3_H


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "matrix.h"


/* --------------------------------- Class ---------------------------------- */


template<typename T>
class Vector3: public Matrix<T>
{

    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Vector3():
        Vector3<T>( 0, 0, 0 )
    {}


    Vector3( const T x, const T y, const T z ):
        Matrix<T>( 3, 1 )
    {
        ( *this )[0] = x;
        ( *this )[1] = y;
        ( *this )[2] = z;
    }


    explicit Vector3( const Matrix<T> &m ) :
        Vector3<T>( 0, 0, 0 )
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 construction size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];
        ( *this )[2] = m[2][0];
    }


    Vector3( const Vector3<T> &v ):
        Vector3<T>( v[0], v[1], v[2] )
    {}


    virtual ~Vector3() = default;


    /* ------------------------ Overloaded Operators ------------------------ */


    Vector3<T> &operator=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 assignment size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];
        ( *this )[2] = m[2][0];

        return *this;
    }


    Vector3<T> &operator+=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 addition size mismatch." );
        }

        ( *this )[0] += m[0][0];
        ( *this )[1] += m[1][0];
        ( *this )[2] += m[2][0];

        return *this;
    }


    Vector3<T> &operator-=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 addition size mismatch." );
        }

        ( *this )[0] -= m[0][0];
        ( *this )[1] -= m[1][0];
        ( *this )[2] -= m[2][0];

        return *this;
    }


    Vector3<T> &operator*=( double s )
    {
        ( *this )[0] *= s;
        ( *this )[1] *= s;
        ( *this )[2] *= s;
        return *this;
    }


    Vector3<T> operator+( const Matrix<T> &m ) const
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 addition size mismatch." );
        }

        Vector3<T> sum = Vector3<T>();

        sum[0] = ( *this )[0] + m[0][0];
        sum[1] = ( *this )[1] + m[1][0];
        sum[2] = ( *this )[2] + m[2][0];

        return sum;
    }


    Vector3<T> operator-( const Matrix<T> &m ) const
    {
        if ( ( m.getRows() != 3 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector3 addition size mismatch." );
        }

        Vector3<T> sum = Vector3<T>();

        sum[0] = ( *this )[0] - m[0][0];
        sum[1] = ( *this )[1] - m[1][0];
        sum[2] = ( *this )[2] - m[2][0];

        return sum;
    }


    Vector3<T> operator*( const double s ) const
    {
        Vector3<T> product = Vector3<T>();

        product[0] = ( *this )[0] * s;
        product[1] = ( *this )[1] * s;
        product[2] = ( *this )[2] * s;

        return product;
    }


    Matrix<T> operator*( const Matrix<T> &m ) const
    {
        return Matrix<T>::operator*( m );
    }


    Matrix<T> operator~() const
    {
        return Matrix<T>::operator~();
    }


    const T &operator[]( unsigned int index ) const
    {
        if ( index > 3 )
        {
            throw MatrixException( "Vector3 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    T &operator[]( unsigned int index )
    {
        if ( index > 3 )
        {
            throw MatrixException( "Vector3 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    /* ------------------------------ Functions ----------------------------- */


    T dot( const Vector3<T> &v ) const
    {
        return  ( getX() * v.getX() ) +
                ( getY() * v.getY() ) +
                ( getZ() * v.getZ() );
    }


    Vector3<T> cross( const Vector3<T> &v ) const
    {
        T crossX = getY() * v.getZ() - getZ() * v.getY();
        T crossY = getZ() * v.getX() - getX() * v.getZ();
        T crossZ = getX() * v.getY() - getY() * v.getX();
        return Vector3<T>( crossX, crossY, crossZ );
    }


    T getX() const
    {
        return ( *this )[0];
    }


    T getY() const
    {
        return ( *this )[1];
    }


    T getZ() const
    {
        return ( *this )[2];
    }


    void setX( const T x )
    {
        ( *this )[0] = x;
    }


    void setY( const T y )
    {
        ( *this )[1] = y;
    }


    void setZ( const T z )
    {
        ( *this )[2] = z;
    }


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // MATRIX_VECTOR3_H


/* -------------------------------------------------------------------------- */