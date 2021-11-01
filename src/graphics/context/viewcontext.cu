/* --------------------------------- Header --------------------------------- */


/**
 * @file    viewcontext.cpp
 * @brief   View context for view transformations
 */


/* -------------------------------- Includes -------------------------------- */


# include <cmath>

# include "cudaerr.cuh"
# include "viewcontext.h"

/* ---------------------------- Static Variables ---------------------------- */


float * ViewContext::d_viewTransform = nullptr;
Matrix<float> ViewContext::transform = Matrix<float>(4, 4);
Matrix<float> ViewContext::invTransform = Matrix<float>(4, 4);


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a view context object
 *
 * @param   *gc     The graphics context to pair with this view context
 *
 * @return  The created view context
 */
ViewContext::ViewContext( GraphicsContext *gc ) :
    gc( gc )
{
    HANDLE_CUDA_ERROR(
        cudaMalloc(&d_viewTransform, 4 * 4 * sizeof(float))
    );

    update();
}


/**
 * @brief   View context destructor
 *
 * @param   void
 *
 * @return  void
 */
ViewContext::~ViewContext() = default;


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Transforms a 3D model point to a 3D device point through the view
 *          context's view transformation matrix
 *
 * @param   &p  The 3D model point to transform
 *
 * @return  The transformed 3D device point
 */
Point3D ViewContext::modelToDevice( const Point3D &p )
{
    return p.transform( transform );
}


/**
 * @brief   Transforms a 3D device point to a 3D model point through the view
 *          context's view transformation matrix
 *
 * @param   &p  The 3D device point to transform
 *
 * @return  The transformed 3D model point
 */
Point3D ViewContext::deviceToModel( const Point3D &p )
{
    return p.transform( invTransform );
}


/**
 * @brief   Gets a unit vector pointing in the direction of the view plane's look direction
 *
 * @param   void
 *
 * @return  A unit vector pointing in direction of the view plane's look direction
 */
Point3D ViewContext::getLookVector()
{
    Point3D lookVector = Point3D( 0, 0, 1 );
    return lookVector.transform( genInvViewRotationMatrix() );
}


/**
 * @brief   Applies a view translation to the transformation matrix
 *
 * @param   x   The magnitude of the translation along the +x axis in model units
 * @param   y   The magnitude of the translation along the +y axis in model units
 * @param   z   The magnitude of the translation along the +z axis in model units
 *
 * @return  void
 */
void ViewContext::translate( float x, float y, float z )
{
    setTranslation(
        viewTranslationX + x,
        viewTranslationY + y,
        viewTranslationZ + z
    );
}


/**
 * @brief   Applies a view rotation to the transformation matrix
 *
 * @param   x   The magnitude of the rotation along the +x axis in radians
 * @param   y   The magnitude of the rotation along the +y axis in radians
 *
 * @return  void
 */
void ViewContext::rotate( float x, float y )
{
    setRotation(
        viewRotationX + x,
        viewRotationY + y
    );
}


/**
 * @brief   Applies a view scale to the transformation matrix
 *
 * @param   x   The magnitude of the scale along the +x axis
 * @param   y   The magnitude of the scale along the +y axis
 * @param   z   The magnitude of the scale along the +y axis
 *
 * @return  void
 */
void ViewContext::scale( float x, float y, float z )
{
    setScale(
        viewScaleX * x,
        viewScaleY * y,
        viewScaleZ * z
    );
}


/**
 * @brief   Translates the view along the x and y axis as pertains to the view
 *          plane of the view transform
 *
 * @param   x   The magnitude of the translation on the view plane's +x axis
 * @param   y   The magnitude of the translation on the view plane's +y axis
 *
 * @return  void
 */
void ViewContext::pan( float x, float y )
{
    panX( x );
    panY( y );
}


/**
 * @brief   Sets the translation of the view context's transformation matrix
 *
 * @param   x   The view transform translation along the +x axis in model units
 * @param   y   The view transform translation along the +y axis in model units
 * @param   z   The view transform translation along the +z axis in model units
 *
 * @return  void
 */
void ViewContext::setTranslation( float x, float y, float z )
{
    viewTranslationX = x;
    viewTranslationY = y;
    viewTranslationZ = z;
    update();
}


/**
 * @brief   Sets the rotation of the view context's transformation matrix
 *
 * @param   x   The view transform rotation along the +x axis in radians
 * @param   y   The view transform rotation along the +y axis in radians
 *
 * @return  void
 */
void ViewContext::setRotation( float x, float y )
{
    // adjust for rotations greater than pi rads
    while ( x > ( 2 * M_PI ) ) x -= 2 * M_PI;
    while ( y > ( 2 * M_PI ) ) y -= 2 * M_PI;

    // adjust for rotations less than negative pi rads
    while ( x < 0 ) x += 2 * M_PI;
    while ( y < 0 ) y += 2 * M_PI;

    // set rotations
    viewRotationX = x;
    viewRotationY = y;

    update();
}


/**
 * @brief   Sets the scale of the view context's transformation matrix
 *
 * @param   x   The view transformation scale along the +x axis
 * @param   y   The view transformation scale along the +y axis
 * @param   z   The view transformation scale along the +z axis
 *
 * @return  void
 */
void ViewContext::setScale( float x, float y, float z )
{
    viewScaleX = x;
    viewScaleY = y;
    viewScaleZ = z;
    update();
}


/**
 * @brief   Gets the view translation of the view context's transformation
 *          matrix
 *
 * @param   void
 *
 * @return  The translation of the view context's transformation matrix as a
 *          Vector3
 */
Vector3<float> ViewContext::getTranslation() const
{
    return Vector3<float>(
        viewTranslationX,
        viewTranslationY,
        viewTranslationZ
    );
}


/**
 * @brief   Gets the view rotation of the view context's transformation matrix
 *
 * @param   void
 *
 * @return  The rotation of the view context's transformation matrix as a
 *          Vector3
 */
Vector2<float> ViewContext::getRotation() const
{
    return Vector2<float>(
        viewRotationX,
        viewRotationY
    );
}


/**
 * @brief   Gets the view scale of the view context's transformation matrix
 *
 * @param   void
 *
 * @return  The scale of the view context's transformation matrix as a Vector3
 */
Vector3<float> ViewContext::getScale() const
{
    return Vector3<float>(
        viewScaleX,
        viewScaleY,
        viewScaleZ
    );
}


/**
 * @brief   Resets the view translation of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetTranslation()
{
    setTranslation(
        DEFAULT_VIEW_TRANSLATION_X,
        DEFAULT_VIEW_TRANSLATION_Y,
        DEFAULT_VIEW_TRANSLATION_Z
    );
}


/**
 * @brief   Resets the view rotation of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetRotation()
{
    setRotation(
        DEFAULT_VIEW_ROTATION_X,
        DEFAULT_VIEW_ROTATION_Y
    );
}


/**
 * @brief   Resets the view scale of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetScale()
{
    setScale(
        DEFAULT_VIEW_SCALE_X,
        DEFAULT_VIEW_SCALE_Y,
        DEFAULT_VIEW_SCALE_Z
    );
}


/**
 * @brief   Resets the view transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetView()
{
    resetTranslation();
    resetRotation();
    resetScale();
}


/**
 * @brief   Updates the view context's transformation matrices
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::update()
{
    // determine transformation matrix
    transform =
            genScreenTranslationMatrix() *
            genScreenFlipMatrix()        *
            genViewScaleMatrix()         *
            genViewRotationMatrix()      *
            genViewTranslationMatrix();

    // determine inverse transformation matrix
    invTransform =
            genInvViewTranslationMatrix()    *
            genInvViewRotationMatrix()       *
            genInvViewScaleMatrix()          *
            genInvScreenFlipMatrix()         *
            genInvScreenTranslationMatrix();
}


/**
 * @brief   Writes the current transformation matrix to the output stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &ViewContext::out( std::ostream &os ) const
{
    transform.out( os );
    return os;
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Pans the current perspective across the view plane's x-axis
 *
 * @param   magnitude   The magnitude of the pan
 *
 * @return  void
 */
void ViewContext::panX( float magnitude )
{
    // get Y rotation
    float rotationY = getRotation().getY();

    // determine view plane x translation
    int quadrant = ( ( int ) ( rotationY / ( M_PI_2 ) ) ) % 4;
    float axisRotation = rotationY - ( quadrant * M_PI_2 );

    // determine tangent ratio
    float oppAdjRatio = tan( axisRotation );

    // determine axis-translation signs and magnitudes based on quadrant
    float signX;
    float signZ;
    float translateX;
    float translateZ;

    switch ( quadrant )
    {
        case 0:
            signX = 1;
            signZ = 1;
            translateX = 1;
            translateZ = oppAdjRatio;
            break;

        case 1:
            signX = -1;
            signZ = 1;
            translateX = oppAdjRatio;
            translateZ = 1;
            break;

        case 2:
            signX = -1;
            signZ = -1;
            translateX = 1;
            translateZ = oppAdjRatio;
            break;

        case 3:
            signX = 1;
            signZ = -1;
            translateX = oppAdjRatio;
            translateZ = 1;
            break;

        default:
            throw ViewContextException( "Illegal view quadrant." );
    }

    // normalize translation hypotenuse to magnitude
    float thetaX = atan( translateX / translateZ );
    float thetaZ = atan( translateZ / translateX );
    translateX = signX * magnitude * sin( thetaX );
    translateZ = signZ * magnitude * sin( thetaZ );

    // std::cout << "QUAD:  " << quadrant << std::endl;
    // std::cout << "SCALE: " << magnitude << std::endl;
    // std::cout << "TX:    " << translateX << std::endl;
    // std::cout << "TZ:    " << translateZ << std::endl;
    // std::cout << "HYP:   " << sqrt( pow( translateX, 2 ) + pow( translateZ, 2 ) ) << std::endl;
    // std::cout << std::endl;

    // translate
    translate( translateX, 0, translateZ );
}


/**
 * @brief   Pans the current perspective across the view plane's y-axis
 *
 * @param   magnitude   The magnitude of the pan
 *
 * @return  void
 */
void ViewContext::panY( float magnitude )
{
    // get X rotation
    float rotationX = getRotation().getX();

    // determine view plane x translation
    int quadrant = ( ( int ) ( rotationX / ( M_PI_2 ) ) ) % 4;
    float axisRotation = rotationX - ( quadrant * M_PI_2 );

    // determine tangent ratio
    float oppAdjRatio = tan( axisRotation );

    // determine axis-translation signs and magnitudes based on quadrant
    float signY;
    float translateY;
    float translateN;

    switch ( quadrant )
    {
        case 0:
            signY = 1;
            translateY = 1;
            translateN = oppAdjRatio;
            break;

        case 1:
            signY = -1;
            translateY = oppAdjRatio;
            translateN = 1;
            break;

        case 2:
            signY = 1;
            translateY = 1;
            translateN = oppAdjRatio;
            break;

        case 3:
            signY = 1;
            translateY = oppAdjRatio;
            translateN = 1;
            break;

        default:
            throw ViewContextException( "Illegal view quadrant." );
    }

    // normalize translation hypotenuse to magnitude
    float thetaY = atan( translateY / translateN );
    translateY = signY * magnitude * sin( thetaY );

    Point3D lookTarget = getLookVector();

    lookTarget.setX( -1 * magnitude * lookTarget.getX() );
    lookTarget.setY( 0 );
    lookTarget.setZ( -1 * magnitude * lookTarget.getZ() );

    // std::cout << "QUAD:  " << quadrant << std::endl;
    // std::cout << "SCALE: " << magnitude << std::endl;
    // std::cout << "TX:    " << translateY << std::endl;
    // std::cout << "TZ:    " << translateN << std::endl;
    // std::cout << "HYP:   " << sqrt( pow( translateY, 2 ) + pow( translateN, 2 ) ) << std::endl;
    // std::cout << "LOOK:  " << getLookVector() << std::endl;
    // std::cout << std::endl;

    // translate
    translate( lookTarget.getX(), translateY, lookTarget.getZ() );
}


/**
 * @brief   Generates the view translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view translation matrix
 */
Matrix<float> ViewContext::genViewTranslationMatrix() const
{
    Matrix<float> viewTranslationMatrix = Matrix<float>( 4, 4 );

    viewTranslationMatrix[0][0] = 1;
    viewTranslationMatrix[1][1] = 1;
    viewTranslationMatrix[2][2] = 1;
    viewTranslationMatrix[3][3] = 1;

    viewTranslationMatrix[0][3] = viewTranslationX;
    viewTranslationMatrix[1][3] = viewTranslationY;
    viewTranslationMatrix[2][3] = viewTranslationZ;

    // std::cout << std::endl << "View Translation: " << std::endl;
    // viewTranslationMatrix.out(std::cout);

    return viewTranslationMatrix;
}


/**
 * @brief   Generates the view rotation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view rotation matrix
 */
Matrix<float> ViewContext::genViewRotationMatrix() const
{
    // generate view rotation X
    Matrix<float> viewRotationXMatrix = Matrix<float>( 4, 4 );

    viewRotationXMatrix[0][0] = 1;
    viewRotationXMatrix[3][3] = 1;

    viewRotationXMatrix[1][1] = cos( viewRotationX );
    viewRotationXMatrix[1][2] = -sin( viewRotationX );
    viewRotationXMatrix[2][1] = sin( viewRotationX );
    viewRotationXMatrix[2][2] = cos( viewRotationX );

    // generate view rotation Y
    Matrix<float> viewRotationYMatrix = Matrix<float>( 4, 4 );

    viewRotationYMatrix[1][1] = 1;
    viewRotationYMatrix[3][3] = 1;

    viewRotationYMatrix[0][0] = cos( viewRotationY );
    viewRotationYMatrix[2][0] = -sin( viewRotationY );
    viewRotationYMatrix[0][2] = sin( viewRotationY );
    viewRotationYMatrix[2][2] = cos( viewRotationY );

    // generate combined rotation matrix x -> y
    Matrix<float> viewRotationMatrix =
        viewRotationXMatrix * viewRotationYMatrix;

    // std::cout << std::endl << "View Rotation: " << std::endl;
    // viewRotationMatrix.out(std::cout);

    return viewRotationMatrix;
}


/**
 * @brief   Generates the view scale matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view scale matrix
 */
Matrix<float> ViewContext::genViewScaleMatrix() const
{
    Matrix<float> viewScaleMatrix = Matrix<float>( 4, 4 );

    viewScaleMatrix[0][0] = viewScaleX;
    viewScaleMatrix[1][1] = viewScaleY;
    viewScaleMatrix[2][2] = viewScaleZ;
    viewScaleMatrix[3][3] = 1;

    // std::cout << std::endl << "View Scale: " << std::endl;
    // viewScaleMatrix.out(std::cout);

    return viewScaleMatrix;
}


/**
 * @brief   Generates the inverse view translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view translation matrix
 */
Matrix<float> ViewContext::genInvViewTranslationMatrix() const
{
    Matrix<float> invViewTranslationMatrix = genViewTranslationMatrix();

    invViewTranslationMatrix[0][3] = -1 * invViewTranslationMatrix[0][3];
    invViewTranslationMatrix[1][3] = -1 * invViewTranslationMatrix[1][3];
    invViewTranslationMatrix[2][3] = -1 * invViewTranslationMatrix[2][3];

    // std::cout << std::endl << "Inverse View Translation: " << std::endl;
    // invViewTranslationMatrix.out(std::cout);

    return invViewTranslationMatrix;
}


/**
 * @brief   Generates the inverse view rotation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view rotation matrix
 */
Matrix<float> ViewContext::genInvViewRotationMatrix() const
{
    Matrix<float> invViewRotationMatrix = genViewRotationMatrix();

    invViewRotationMatrix = ~invViewRotationMatrix;

    // std::cout << std::endl << "Inverse View Rotation: " << std::endl;
    // invViewRotationMatrix.out(std::cout);

    return invViewRotationMatrix;
}


/**
 * @brief   Generates the inverse view scale matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view scale matrix
 */
Matrix<float> ViewContext::genInvViewScaleMatrix() const
{
    Matrix<float> invViewScaleMatrix = genViewScaleMatrix();

    invViewScaleMatrix[0][0] = 1 / invViewScaleMatrix[0][0];
    invViewScaleMatrix[1][1] = 1 / invViewScaleMatrix[1][1];
    invViewScaleMatrix[2][2] = 1 / invViewScaleMatrix[2][2];

    // std::cout << std::endl << "Inverse View Scale: " << std::endl;
    // invViewScaleMatrix.out(std::cout);

    return invViewScaleMatrix;
}


/**
 * @brief   Generates the screen translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The screen translation matrix
 */
Matrix<float> ViewContext::genScreenTranslationMatrix() const
{
    Matrix<float> screenTranslationMatrix = Matrix<float>( 4, 4 );

    screenTranslationMatrix[0][0] = 1;
    screenTranslationMatrix[1][1] = 1;
    screenTranslationMatrix[2][2] = 1;
    screenTranslationMatrix[3][3] = 1;

    screenTranslationMatrix[0][3] = ( ( float ) gc->getWindowWidth() ) / 2;
    screenTranslationMatrix[1][3] = ( ( float ) gc->getWindowHeight() ) / 2;

    // std::cout << std::endl << "Screen Translation: " << std::endl;
    // screenTranslationMatrix.out( std::cout);

    return screenTranslationMatrix;
}


/**
 * @brief   Generates the screen flip matrix from internal parameters
 *
 * @param   void
 *
 * @return  The screen flip matrix
 */
Matrix<float> ViewContext::genScreenFlipMatrix() const
{
    Matrix<float> screenFlipMatrix = Matrix<float>( 4, 4 );

    screenFlipMatrix[0][0] = 1;
    screenFlipMatrix[1][1] = -1;
    screenFlipMatrix[2][2] = 1;
    screenFlipMatrix[3][3] = 1;

    // std::cout << std::endl << "Screen Flip: " << std::endl;
    // screenFlipMatrix.out( std::cout);

    return screenFlipMatrix;
}


/**
 * @brief   Generates the inverse screen translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse screen translation matrix
 */
Matrix<float> ViewContext::genInvScreenTranslationMatrix() const
{
    Matrix<float> invScreenTranslationMatrix = genScreenTranslationMatrix();

    invScreenTranslationMatrix[0][3] = -1 * invScreenTranslationMatrix[0][3];
    invScreenTranslationMatrix[1][3] = -1 * invScreenTranslationMatrix[1][3];
    invScreenTranslationMatrix[2][3] = -1 * invScreenTranslationMatrix[2][3];

    // std::cout << std::endl << "Inverse Screen Translation: " << std::endl;
    // invScreenTranslationMatrix.out( std::cout);

    return invScreenTranslationMatrix;
}


/**
 * @brief   Generates the inverse screen flip matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse screen flip matrix
 */
Matrix<float> ViewContext::genInvScreenFlipMatrix() const
{
    Matrix<float> invScreenFlipMatrix = genScreenFlipMatrix();

    invScreenFlipMatrix[0][0] = 1 / invScreenFlipMatrix[0][0];
    invScreenFlipMatrix[1][1] = 1 / invScreenFlipMatrix[1][1];
    invScreenFlipMatrix[2][2] = 1 / invScreenFlipMatrix[2][2];

    // std::cout << std::endl << "Inverse Screen Flip: " << std::endl;
    // invScreenFlipMatrix.out( std::cout);

    return invScreenFlipMatrix;
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Writes a view context's transformation matrix to the output stream
 *
 * @param   &os     The output stream to write to
 * @param   &vc     The view context to write
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const ViewContext &vc )
{
    vc.out( os );
    return os;
}


/* -------------------------------------------------------------------------- */