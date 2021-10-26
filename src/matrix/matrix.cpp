/* --------------------------------- Header --------------------------------- */


/**
 * @file    matrix.cpp
 * @brief   Templated matrix class
 */


/* -------------------------------- Includes -------------------------------- */


# include "matrix.h"

/* ----------------------- Global Overloaded Operators ---------------------- */


template<typename T>
std::ostream &operator<<( std::ostream& os, const Matrix<T> &m )
{
    m.out( os );
    return os;
}

template<typename T>
Matrix<T> operator*( double s, const Matrix<T> &m )
{
    return m * s;
}


/* -------------------------------------------------------------------------- */