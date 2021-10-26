/* --------------------------------- Header --------------------------------- */


/**
 * @file    vector4.h
 * @brief   Templated 4D vector class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef MATRIX_VECTOR4_H
# define MATRIX_VECTOR4_H


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "matrix.h"


/* --------------------------------- Class ---------------------------------- */


template<typename T>
class Vector4: public Matrix<T>
{

    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Vector4():
        Vector4<T>( 0, 0, 0, 0 )
    {}


    Vector4( const T x, const T y, const T z, const T w ):
        Matrix<T>( 4, 1 )
    {
        ( *this )[0] = x;
        ( *this )[1] = y;
        ( *this )[2] = z;
        ( *this )[3] = w;
    }


    explicit Vector4( const Matrix<T> &m ) :
        Vector4<T>( 0, 0, 0, 0 )
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 construction size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];
        ( *this )[2] = m[2][0];
        ( *this )[3] = m[3][0];
    }


    Vector4( const Vector4<T> &v ):
        Vector4<T>( v[0], v[1], v[2], v[3] )
    {}


    virtual ~Vector4() = default;


    /* ------------------------ Overloaded Operators ------------------------ */


    Vector4<T> &operator=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 assignment size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];
        ( *this )[2] = m[2][0];
        ( *this )[3] = m[3][0];

        return *this;
    }


    Vector4<T> &operator+=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 addition size mismatch." );
        }

        ( *this )[0] += m[0][0];
        ( *this )[1] += m[1][0];
        ( *this )[2] += m[2][0];
        ( *this )[3] += m[3][0];

        return *this;
    }


    Vector4<T> &operator-=( const Matrix<T> &m )
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 addition size mismatch." );
        }

        ( *this )[0] -= m[0][0];
        ( *this )[1] -= m[1][0];
        ( *this )[2] -= m[2][0];
        ( *this )[3] -= m[3][0];

        return *this;
    }


    Vector4<T> &operator*=( double s )
    {
        ( *this )[0] *= s;
        ( *this )[1] *= s;
        ( *this )[2] *= s;
        ( *this )[3] *= s;
        return *this;
    }


    Vector4<T> operator+( const Matrix<T> &m ) const
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 addition size mismatch." );
        }

        Vector4<T> sum = Vector4<T>();

        sum[0] = ( *this )[0] + m[0][0];
        sum[1] = ( *this )[1] + m[1][0];
        sum[2] = ( *this )[2] + m[2][0];
        sum[3] = ( *this )[3] + m[3][0];

        return sum;
    }


    Vector4<T> operator-( const Matrix<T> &m ) const
    {
        if ( ( m.getRows() != 4 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector4 addition size mismatch." );
        }

        Vector4<T> sum = Vector4<T>();

        sum[0] = ( *this )[0] - m[0][0];
        sum[1] = ( *this )[1] - m[1][0];
        sum[2] = ( *this )[2] - m[2][0];
        sum[3] = ( *this )[3] - m[3][0];

        return sum;
    }


    Vector4<T> operator*( const double s ) const
    {
        Vector4<T> product = Vector4<T>();

        product[0] = ( *this )[0] * s;
        product[1] = ( *this )[1] * s;
        product[2] = ( *this )[2] * s;
        product[3] = ( *this )[3] * s;

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
        if ( index > 4 )
        {
            throw MatrixException( "Vector4 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    T &operator[]( unsigned int index )
    {
        if ( index > 4 )
        {
            throw MatrixException( "Vector4 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    /* ------------------------------ Functions ----------------------------- */


    T dot( const Vector4<T> &v ) const
    {
        return  ( getX() * v.getX() ) +
                ( getY() * v.getY() ) +
                ( getZ() * v.getZ() ) +
                ( getW() * v.getW() );
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


    T getW() const
    {
        return ( *this )[3];
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


    void setW( const T w )
    {
        ( *this )[3] = w;
    }


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // MATRIX_VECTOR4_H


/* -------------------------------------------------------------------------- */