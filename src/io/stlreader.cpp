/* --------------------------------- Header --------------------------------- */


/**
 * @file    stlreader.cpp
 * @brief   STL file reader
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>

# include "stlreader.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates an STL reader
 *
 * @param   void
 *
 * @return  The created STL reader
 */
STLReader::STLReader() = default;


/**
 * @brief   Creates an STL reader opens the specified STL file
 *
 * @param   *filePath   The path of the STL file to open
 *
 * @return  The created STL reader
 */
STLReader::STLReader( const char *filePath )
{
    open( ( std::string& ) filePath );
}


/**
 * @brief   Creates an STL reader opens the specified STL file
 *
 * @param   &filePath   The path of the STL file to open
 *
 * @return  The created STL reader
 */
STLReader::STLReader( const std::string &filePath )
{
    open( filePath );
}


/**
 * @brief   Creates an STL reader from an existing STL reader
 *
 * @param   &stlReader  The STL reader to create from
 *
 * @return  The created STL reader
 */
STLReader::STLReader( const STLReader &stlReader ) = default;


/**
 * @brief   STL reader destructor
 *
 * @param   void
 *
 * @return  void
 */
STLReader::~STLReader()
{
    // close if a file is open
    if ( isOpen ) close();

    // free file stream
    delete in;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Opens an STL file in this STL reader
 *
 * @param   &filePath   The path of the STL file to open
 *
 * @return  void
 */
void STLReader::open( const std::string &filePath )
{
    // close file if already open
    if ( isOpen ) close();

    // open an input file stream
    in->open( filePath.c_str() );

    // throw error if file fails to open
    if ( !in )
    {
        throw STLReaderException( "File does not exist." );
    }

    // set open flag
    isOpen = true;
}


/**
 * @brief   Closes this STL reader
 *
 * @param   void
 *
 * @return  void
 */
void STLReader::close()
{
    // close input file stream
    in->close();

    // clear open flag
    isOpen = false;
}


/**
 * @brief   Gets the number of facets in the currently opened STL file
 *
 * @param   void
 *
 * @return  The number of facets in the currently opened STL file
 */
unsigned int STLReader::getFacetCount()
{
    // throw an exception if not open
    if ( !isOpen )
    {
        throw STLReaderException( "No open file." );
    }

    // initialize facet count
    unsigned int facetCount = 0;

    // count facets
    while ( *in )
    {
        std::string line;
        getline( *in, line );

        std::string token;
        std::stringstream ss = std::stringstream( line );
        ss >> token;

        if ( ( token == "facet" ) ) facetCount++;
    }

    // seek back to the beginning of the input stream
    in->clear();
    in->seekg( 0 );

    return facetCount;
}


Triangle STLReader::readFacet( unsigned int index )
{
    // throw an exception if not open
    if ( !isOpen )
    {
        throw STLReaderException( "No open file." );
    }

    // iterate to facet at index
    unsigned int facetCount = 0;

    while ( *in && ( facetCount <= index ) )
    {
        std::string line;
        getline( *in, line );

        std::string token;
        std::stringstream ss = std::stringstream( line );
        ss >> token;

        if ( ( token == "facet" ) ) facetCount++;
    }

    // throw end-of-file exception
    if ( !*in )
    {
        throw STLReaderException( "Facet index out of range." );
    }

    // advance the stream 1 position
    std::string garbage;
    getline( *in, garbage );

    // create array of 3D points to store vertices
    Point3D verts[3];

    // read the vertices
    for ( unsigned int i = 0; i < 3; i++ )
    {
        // get string stream for current vertex string
        std::string vertexString;
        getline( *in, vertexString );

        std::string token;
        std::stringstream ss = std::stringstream( vertexString );
        ss >> token;

        // throw an exception if vertex string is invalid
        if ( token != "vertex" )
        {
            throw STLReaderException( "Invalid or corrupt file format." );
        }

        // read vertex coords
        double x;
        double y;
        double z;

        ss >> x;
        ss >> y;
        ss >> z;

        // create vertex
        verts[i] = Point3D( x, y, z );
    }

    // seek back to the beginning of the input stream
    in->clear();
    in->seekg( 0 );

    // create a facet from the verts
    Triangle facet = Triangle( verts[0], verts[1], verts[2] );

    return facet;
}


ShapeContainer STLReader::readFacets()
{
    // throw an exception if not open
    if ( !isOpen )
    {
        throw STLReaderException( "No open file." );
    }

    // create shape container
    ShapeContainer sc = ShapeContainer();

    // advance to next facet line
    while ( *in )
    {
        // get line
        std::string line;
        getline( *in, line );

        std::string token;
        std::stringstream ss = std::stringstream( line );
        ss >> token;

        // process if facet
        if (( token == "facet" ))
        {
            // advance the stream 1 position
            getline( *in, line );

            // create array of 3D points to store vertices
            Point3D verts[3];

            // read the vertices
            for ( unsigned int i = 0; i < 3; i++ )
            {
                // get string stream for current vertex string
                getline( *in, line );

                ss = std::stringstream( line );
                ss >> token;

                // throw an exception if vertex string is invalid
                if ( token != "vertex" )
                {
                    throw STLReaderException( "Invalid or corrupt file format." );
                }

                // read vertex coords
                double x;
                double y;
                double z;

                ss >> x;
                ss >> y;
                ss >> z;

                // create vertex
                verts[i] = Point3D( x, y, z );
            }

            // create a facet from the verts
            Triangle facet = Triangle( verts[0], verts[1], verts[2] );

            // add the facet to the shape container
            sc.add( facet );
        }
    }

    return sc;
}


/* -------------------------------------------------------------------------- */