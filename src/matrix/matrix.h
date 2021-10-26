/* --------------------------------- Header --------------------------------- */


/**
 * @file    matrix.h
 * @brief   Templated matrix class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef MATRIX_MATRIX_H
# define MATRIX_MATRIX_H


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <iostream>
# include <stdexcept>
# include <vector>


/* --------------------------------- Class ---------------------------------- */


class MatrixException : public std::runtime_error
{
public:
    explicit MatrixException( const std::string& msg ):
    std::runtime_error( ( std::string( "Matrix Exception: " ) + msg ).c_str() )
    {}
};


template<typename T>
class Matrix
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Matrix( unsigned int rows, unsigned int cols ):
    rows( rows ), cols( cols ), inner( std::vector<T>( rows * cols ) )
    {}


    Matrix( const Matrix<T> &m ):
    rows( m.rows ), cols( m.cols ), inner( m.inner )
    {}


    virtual ~Matrix() = default;


    /* ------------------------ Overloaded Operators ------------------------ */


    Matrix<T> &operator=( const Matrix<T> &m )
    {
        // reassign row and column counts
        rows = m.rows;
        cols = m.cols;

        // clear inner matrix
        inner.clear();
        inner.resize( rows * cols );

        // push back other matrix inner elements
        for ( unsigned int i = 0; i < m.inner.size(); i++ )
        {
            inner[i] = m.inner[i];
        }

        return *this;
    }


    Matrix<T> &operator+=( const Matrix<T> &m )
    {
        // throw an exception if the matrix row and column count do not match
        if ( ( rows != m.rows ) || ( cols != m.cols ) )
        {
            throw MatrixException( "Matrix addition size mismatch" );
        }

        // sum corresponding elements from each matrix
        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            inner[i] += m.inner[i];
        }

        return *this;
    }


    Matrix<T> &operator-=( const Matrix<T> &m )
    {
        // throw an exception if the matrix row and column count do not match
        if ( ( rows != m.rows ) || ( cols != m.cols ) )
        {
            throw MatrixException( "Matrix subtraction size mismatch" );
        }

        // find difference of corresponding elements from each matrix
        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            inner[i] -= m.inner[i];
        }

        return *this;
    }


    Matrix<T> &operator*=( double s )
    {
        // find difference of corresponding elements from each matrix
        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            inner[i] *= s;
        }

        return *this;
    }


    Matrix<T> operator+( const Matrix<T> &m ) const
    {
        // throw an exception if the matrix row and column count do not match
        if ( ( rows != m.rows ) || ( cols != m.cols ) )
        {
            throw MatrixException( "Matrix addition size mismatch" );
        }

        // sum matrix
        Matrix<T> sum = Matrix<T>( rows, cols );

        // find difference of corresponding elements from each matrix
        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            sum.inner[i] = inner[i] + m.inner[i];
        }

        return sum;
    }


    Matrix<T> operator-( const Matrix<T> &m ) const
    {
        // throw an exception if the matrix row and column count do not match
        if ( ( rows != m.rows ) || ( cols != m.cols ) )
        {
            throw MatrixException( "Matrix subtraction size mismatch" );
        }

        // difference matrix
        Matrix<T> difference = Matrix<T>( rows, cols );

        // find difference of corresponding elements from each matrix
        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            difference.inner[i] = inner[i] - m.inner[i];
        }

        return difference;
    }


    Matrix<T> operator*( const Matrix<T> &m ) const
    {
        // throw an exception if the matrix row and column count do not match
        if ( ( cols != m.rows ) )
        {
            throw MatrixException( "Matrix multiplication size mismatch" );
        }

        // product matrix
        Matrix<T> product = Matrix<T>( rows, m.cols );

        // find difference of corresponding elements from each matrix
        for ( unsigned int row = 0; row < rows; row++ )
        {
            for ( unsigned int col = 0; col < m.cols; col++ )
            {
                T sum = 0;

                for ( unsigned int i = 0; i < m.rows; i++ )
                {
                    sum += ( *this )[row][i] * m[i][col];
                }

                product[row][col] = sum;
            }
        }

        return product;
    }


    Matrix<T> operator*( const double s ) const
    {
        // create a duplicate matrix to store the scalar-product
        Matrix<T> product( *this );

        // execute the scalar-product matrix
        for ( unsigned int i = 0; i < product.inner.size(); i++ )
        {
            product.inner[i] *= s;
        }

        return product;
    }


    Matrix<T> operator~() const
    {
        // create a new matrix with swapped row/column dimensions
        Matrix<T> transpose( cols, rows );

        // execute matrix transpose
        for ( unsigned int col = 0; col < cols; col++ )
        {
            for ( unsigned int row = 0; row < rows; row++ )
            {
                transpose[col][row] = ( *this )[row][col];
            }
        }

        return transpose;
    }


    const T *operator[]( unsigned int row ) const
    {
        // throw an exception if the row index is out of bounds
        if ( row >= rows )
        {
            throw MatrixException( "Matrix row index out of bounds." );
        }

        return &inner[row * cols];
    }


    T *operator[]( unsigned int row )
    {
        // throw an exception if the row index is out of bounds
        if ( row >= rows )
        {
            throw MatrixException( "Matrix row index out of bounds." );
        }

        return &inner[row * cols];
    }


    bool operator==( const Matrix<T> &m ) const
    {
        if ( ( rows != m.rows ) || ( cols != m.cols ) )
        {
            return false;
        }

        for ( unsigned int i = 0; i < inner.size(); i++ )
        {
            if ( inner[i] != m.inner[i] )
            {
                return false;
            }
        }

        return true;
    }


    bool operator!=( const Matrix<T> &m ) const
    {
        return !( *this == m );
    }


    /* ------------------------------ Functions ----------------------------- */


    unsigned int getRows() const
    {
        return rows;
    }


    unsigned int getColumns() const
    {
        return cols;
    }


    virtual std::ostream &out( std::ostream &os ) const
    {
        for ( unsigned int row = 0; row < rows; row++ )
        {
            os << "[ ";
            for ( unsigned int col = 0; col < cols; col++ )
            {
                os << ( *this )[row][col] << " ";
            }
            os << "]" << std::endl;
        }

        return os;
    }


    /* ============================== PROTECTED ============================= */

protected:

    /* ----------------------------- Attributes ----------------------------- */


    unsigned int rows;
    unsigned int cols;
    std::vector<T> inner;


    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


template<typename T>
std::ostream &operator<<( std::ostream &os, const Matrix<T> &m );

template<typename T>
Matrix<T> operator*( double s, const Matrix<T> &m );


/* --------------------------------- Footer --------------------------------- */


# endif // MATRIX_MATRIX_H


/* -------------------------------------------------------------------------- */