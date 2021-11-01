/* --------------------------------- Header --------------------------------- */


/**
 * @file    shapecontainer.cpp
 * @brief   Set container of shape pointers
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <set>
# include <sstream>
#include <driver_types.h>

# include "cudaerr.cuh"
# include "shape.h"
# include "shapecontainer.h"
# include "triangle.h"


/* ----------------------- Constructors / Destructors ----------------------- */


const unsigned int SHAPE_DIM = 3;
const unsigned int VERT_DIM = 4;


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
 * Pushes this shape container to the GPU device
 */
void ShapeContainer::pushToDevice()
{
    // input shapes buffer
    float inputShapes[shapes.size() * SHAPE_DIM * VERT_DIM];

    // copy each tri to input memory
    for (unsigned int shapeIdx = 0; shapeIdx < shapes.size(); shapeIdx++)
    {
        unsigned int shapeOffset = shapeIdx * SHAPE_DIM * VERT_DIM;
        for (unsigned int vertIdx = 0; vertIdx < SHAPE_DIM; vertIdx++)
        {
            unsigned int vertOffset = vertIdx * VERT_DIM;
            for (unsigned int coordIdx = 0; coordIdx < VERT_DIM; coordIdx++)
            {
                if (coordIdx < VERT_DIM - 1)
                {
                    inputShapes[shapeOffset + vertOffset + coordIdx] =
                        (*(shapes[shapeIdx]))[vertIdx][coordIdx];
                }
                else
                {
                    inputShapes[shapeOffset + vertOffset + coordIdx] = 1;
                }
            }
        }
    }

    // free existing device mallocs if they exist
    if ( d_inputShapes != nullptr)
    {
        HANDLE_CUDA_ERROR(cudaFree(d_inputShapes));
    }
    if ( d_outputShapes != nullptr)
    {
        HANDLE_CUDA_ERROR(cudaFree(d_outputShapes));
    }

    // malloc new input and output
    HANDLE_CUDA_ERROR(
        cudaMalloc(&d_inputShapes, shapes.size() * SHAPE_DIM * VERT_DIM * sizeof(float))
    );
    HANDLE_CUDA_ERROR(
        cudaMalloc(&d_outputShapes, shapes.size() * SHAPE_DIM * VERT_DIM * sizeof(float))
    );

    // copy shapes to device
    HANDLE_CUDA_ERROR(
        cudaMemcpy(
            (void *) d_inputShapes,
            (void *) inputShapes,
            shapes.size() * SHAPE_DIM * VERT_DIM * sizeof(float),
            cudaMemcpyHostToDevice
        )
    );
}


/**
 * @brief   Adds a shape to this shape container
 *
 * @param   &shape  The shape to add
 *
 * @return  void
 */
void ShapeContainer::add( const Shape &shape )
{
    shapes.insert( shapes.end(), shape.clone() );
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
    // input shapes buffer
    float outputShapes[shapes.size() * SHAPE_DIM * VERT_DIM];

    // copy view transform to local
    float viewTransform[VERT_DIM][VERT_DIM];

    for (unsigned int row = 0; row < VERT_DIM; row++)
    {
        for (unsigned int col = 0; col < VERT_DIM; col++)
        {
            viewTransform[row][col] = ViewContext::transform[row][col];
        }
    }

    // copy view transform to device
    HANDLE_CUDA_ERROR(
        cudaMemcpy(
            ( void * ) ViewContext::d_viewTransform,
            ( void * ) viewTransform,
            VERT_DIM * VERT_DIM * sizeof( float ),
            cudaMemcpyHostToDevice
        )
    );

    // zero output matrix
    HANDLE_CUDA_ERROR(
        cudaMemset(d_outputShapes, 0, shapes.size() * SHAPE_DIM * VERT_DIM * sizeof(float))
    );

    // run GPU kernel
    unsigned int blocks = ceil(shapes.size() / 1024.0);

    applyViewTransform<<<blocks, 1024>>>(
        d_inputShapes,
        d_outputShapes,
        ViewContext::d_viewTransform
    );
    HANDLE_CUDA_ERROR(cudaDeviceSynchronize());

    // copy shapes from device
    HANDLE_CUDA_ERROR(
        cudaMemcpy(
            (void *) outputShapes,
            (void *) d_outputShapes,
            shapes.size() * SHAPE_DIM * VERT_DIM * sizeof(float),
            cudaMemcpyDeviceToHost
        )
    );

    // parse output points into output shapes vector
    std::vector<Shape*> parsedShapes;

    for (unsigned int shapeIdx = 0; shapeIdx < shapes.size(); shapeIdx++)
    {
        unsigned int shapeOffset = shapeIdx * SHAPE_DIM * VERT_DIM;

        Point3D verts[3];

        for (unsigned int vertIdx = 0; vertIdx < SHAPE_DIM; vertIdx++)
        {
            unsigned int vertOffset = vertIdx * VERT_DIM;

            verts[vertIdx].setX(outputShapes[shapeOffset + vertOffset + 0]);
            verts[vertIdx].setY(outputShapes[shapeOffset + vertOffset + 1]);
            verts[vertIdx].setZ(outputShapes[shapeOffset + vertOffset + 2]);
        }

        Triangle * tri = new Triangle(verts[0], verts[1], verts[2]);
        parsedShapes.insert(parsedShapes.end(), tri);
    }

    // draw shapes
    std::for_each(parsedShapes.begin(), parsedShapes.end(), [gc](Shape *shape)
       {
           shape->draw(gc);
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


/* ------------------------------ GPU Kernels ------------------------------- */


__global__ void applyViewTransform(
    float * inputShapes, float * outputShapes, float * viewTransform
)
{
    unsigned int shapeIdx = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int shapeOffset = shapeIdx * SHAPE_DIM * VERT_DIM;

    // matrix vector multiplication
    for (unsigned int vertIdx = 0; vertIdx < SHAPE_DIM; vertIdx++)
    {
        unsigned int vertOffset = vertIdx * VERT_DIM;

        for (unsigned int row = 0; row < VERT_DIM; row++)
        {

            unsigned int rowOffset = row * VERT_DIM;

            for (unsigned int i = 0; i < VERT_DIM; i++)
            {
                outputShapes[shapeOffset + vertOffset + row] +=
                    viewTransform[rowOffset + i] * inputShapes[shapeOffset + vertOffset + i];
            }
        }
    }
}


/* -------------------------------------------------------------------------- */