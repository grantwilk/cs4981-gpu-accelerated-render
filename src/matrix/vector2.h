/* --------------------------------- Header --------------------------------- */


/**
 * @file    vector2.h
 * @brief   Templated 2D vector class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef MATRIX_VECTOR2_H
# define MATRIX_VECTOR2_H


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "matrix.h"


/* --------------------------------- Class ---------------------------------- */


template<typename T>
class Vector2 : public Matrix<T>
{

    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Vector2() :
        Vector2<T>( 0, 0 )
    {}


    Vector2( const T x, const T y ) :
        Matrix<T>( 2, 1 )
    {
        ( *this )[0] = x;
        ( *this )[1] = y;
    }


    explicit Vector2( const Matrix<T> &m ) :
        Vector2<T>( 0, 0 )
    {
        if ( ( m.getRows() != 2 ) || ( m.getColumns() != 1 ) )
        {
            throw MatrixException( "Vector2 construction size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];
    }


    Vector2( const Vector2<T> &v ) :
        Vector2<T>( v[0], v[1] )
    {}


    virtual ~Vector2() = default;


    /* ------------------------ Overloaded Operators ------------------------ */


    Vector2<T> &operator=( const Matrix<T> &m )
    {
        if (( m.getRows() != 2 ) || ( m.getColumns() != 1 ))
        {
            throw MatrixException( "Vector2 assignment size mismatch." );
        }

        ( *this )[0] = m[0][0];
        ( *this )[1] = m[1][0];

        return *this;
    }


    Vector2<T> &operator+=( const Matrix<T> &m )
    {
        if (( m.getRows() != 2 ) || ( m.getColumns() != 1 ))
        {
            throw MatrixException( "Vector2 addition size mismatch." );
        }

        ( *this )[0] += m[0][0];
        ( *this )[1] += m[1][0];

        return *this;
    }


    Vector2<T> &operator-=( const Matrix<T> &m )
    {
        if (( m.getRows() != 2 ) || ( m.getColumns() != 1 ))
        {
            throw MatrixException( "Vector2 addition size mismatch." );
        }

        ( *this )[0] -= m[0][0];
        ( *this )[1] -= m[1][0];

        return *this;
    }


    Vector2<T> &operator*=( double s )
    {
        ( *this )[0] *= s;
        ( *this )[1] *= s;
        return *this;
    }


    Vector2<T> operator+( const Matrix<T> &m ) const
    {
        if (( m.getRows() != 2 ) || ( m.getColumns() != 1 ))
        {
            throw MatrixException( "Vector2 addition size mismatch." );
        }

        Vector2<T> sum = Vector2<T>();

        sum[0] = ( *this )[0] + m[0][0];
        sum[1] = ( *this )[1] + m[1][0];

        return sum;
    }


    Vector2<T> operator-( const Matrix<T> &m ) const
    {
        if (( m.getRows() != 2 ) || ( m.getColumns() != 1 ))
        {
            throw MatrixException( "Vector2 addition size mismatch." );
        }

        Vector2<T> sum = Vector2<T>();

        sum[0] = ( *this )[0] - m[0][0];
        sum[1] = ( *this )[1] - m[1][0];

        return sum;
    }


    Matrix<T> operator*( const Matrix<T> &m ) const
    {
        return Matrix<T>::operator*( m );
    }


    Vector2<T> operator*( const double s ) const
    {
        Vector2<T> product = Vector2<T>();

        product[0] = ( *this )[0] * s;
        product[1] = ( *this )[1] * s;

        return product;
    }


    Matrix<T> operator~() const
    {
        return Matrix<T>::operator~();
    }


    const T &operator[]( unsigned int index ) const
    {
        if ( index > 2 )
        {
            throw MatrixException( "Vector2 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    T &operator[]( unsigned int index )
    {
        if ( index > 2 )
        {
            throw MatrixException( "Vector2 index out of bounds." );
        }

        return Matrix<T>::operator[]( index )[0];
    }


    /* ------------------------------ Functions ----------------------------- */


    T dot( const Vector2<T> &v ) const
    {
        return  ( getX() * v.getX() ) +
                ( getY() * v.getY() );
    }


    T getX() const
    {
        return ( *this )[0];
    }


    T getY() const
    {
        return ( *this )[1];
    }


    void setX( const T x )
    {
        ( *this )[0] = x;
    }


    void setY( const T y )
    {
        ( *this )[1] = y;
    }


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // MATRIX_VECTOR2_H


/* -------------------------------------------------------------------------- */