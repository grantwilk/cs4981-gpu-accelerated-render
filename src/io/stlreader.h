/* --------------------------------- Header --------------------------------- */


/**
 * @file    stlreader.h
 * @brief   STL file reader
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef IO_STLREADER_H
# define IO_STLREADER_H


/* -------------------------------- Includes -------------------------------- */


# include <string>
# include <fstream>

# include "triangle.h"
# include "shapecontainer.h"


/* --------------------------------- Class ---------------------------------- */


class STLReaderException : public std::runtime_error
{
public:
    explicit STLReaderException( const std::string& msg ):
    std::runtime_error( ( std::string( "STLReader Exception: " ) + msg ).c_str() )
    {}
};


class STLReader
{
    /* =============================== PUBLIC =============================== */

public:

    /* ----------------------------- Attributes ----------------------------- */


    /* --------------------- Constructors / Destructors --------------------- */


    STLReader();
    explicit STLReader( const char *filePath );
    explicit STLReader( const std::string &filePath );
    STLReader( const STLReader &stlReader );

    ~STLReader();


    /* ------------------------------ Functions ----------------------------- */


    void open( const std::string &filePath );
    void close();

    unsigned int getFacetCount();
    Triangle readFacet( unsigned int index );
    ShapeContainer readFacets();


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    std::ifstream *in = new std::ifstream();
    bool isOpen = false;


    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // IO_STLREADER_H


/* -------------------------------------------------------------------------- */