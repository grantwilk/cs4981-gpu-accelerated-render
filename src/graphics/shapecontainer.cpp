/* --------------------------------- Header --------------------------------- */


/**
 * @file    shapecontainer.cpp
 * @brief   Set container of shape pointers
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <set>
# include <sstream>

# include "line.h"
# include "shape.h"
# include "shapecontainer.h"
# include "triangle.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates an empty shape container
 *
 * @param   void
 *
 * @return  The created shape container
 */
ShapeContainer::ShapeContainer() = default;


/**
 * @brief   Creates a shape container from an existing shape container
 *
 * @param   &sc     The shape container to create from
 *
 * @return  The created shape container
 */
ShapeContainer::ShapeContainer( const ShapeContainer &sc )
{
    add( sc );
}


/**
 * @brief   Shape container destructor
 *
 * @param   void
 *
 * @return  void
 */
ShapeContainer::~ShapeContainer()
{
    std::for_each( shapes.begin(), shapes.end(), [this]( Shape *shape )
       {
           delete shape;
       }
    );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns the shapes from another shape container to this
 *          shape container
 *
 * @param   &sc     The shape container to assign from
 *
 * @return  This shape container
 */
ShapeContainer &ShapeContainer::operator=( const ShapeContainer &sc )
{
    erase();
    add( sc );
    return *this;
}


/**
 * @brief   Converts a shape container to a string and writes it to an
 *          output stream
 *
 * @param   &os     The output stream to write to
 * @param   &sc     The shape container to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const ShapeContainer &sc )
{
    sc.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Adds a shape to this shape container
 *
 * @param   &shape  The shape to add
 *
 * @return  void
 */
void ShapeContainer::add( const Shape &shape )
{
    shapes.insert( shape.clone() );
}


/**
 * @brief   Adds the elements from another shape container to this
 *          shape container
 *
 * @param   &sc  The shape container to add
 *
 * @return  void
 */
void ShapeContainer::add( const ShapeContainer &sc )
{
    std::for_each( sc.shapes.begin(), sc.shapes.end(), [this]( Shape *shape )
       {
           add( *shape );
       }
    );
}


/**
 * @brief   Draws the shapes in this shape container
 *
 * @param   *gc     The graphics context to draw to
 * @param   *vc     The view context to draw with
 *
 * @return  void
 */
void ShapeContainer::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    std::for_each( shapes.begin(), shapes.end(), [gc, vc]( Shape *shape )
       {
           shape->draw( gc, vc );
       }
    );
}


/**
 * @brief   Converts the shapes in this shape container to strings and
 *          outputs them to an output stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &ShapeContainer::out( std::ostream &os ) const
{
    std::for_each( shapes.begin(), shapes.end(), [&os]( Shape *shape )
       {
           shape->out( const_cast<std::ostream&>( os ) );
           os << std::endl;
       }
    );
    return os;
}


/**
 * @brief   Removes all shapes from this shape container
 *
 * @param   void
 *
 * @return  void
 */
void ShapeContainer::erase()
{
    std::for_each( shapes.begin(), shapes.end(), []( Shape *shape )
       {
           delete shape;
       }
    );
    shapes.clear();
}


/**
 * @brief   Gets the size of the shape container
 *
 * @param   void
 *
 * @return  The size of the shape container
 */
unsigned int ShapeContainer::size()
{
    return shapes.size();
}


/* -------------------------------------------------------------------------- */