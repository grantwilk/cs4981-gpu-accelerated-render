/* --------------------------------- Header --------------------------------- */


/**
 * @file    viewcontext.cpp
 * @brief   View context for view transformations
 */


/* -------------------------------- Includes -------------------------------- */


# include <cmath>

# include "viewcontext.h"


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
void ViewContext::translate( double x, double y, double z )
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
void ViewContext::rotate( double x, double y )
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
void ViewContext::scale( double x, double y, double z )
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
void ViewContext::pan( double x, double y )
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
void ViewContext::setTranslation( double x, double y, double z )
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
void ViewContext::setRotation( double x, double y )
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
void ViewContext::setScale( double x, double y, double z )
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
Vector3<double> ViewContext::getTranslation() const
{
    return Vector3<double>(
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
Vector2<double> ViewContext::getRotation() const
{
    return Vector2<double>(
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
Vector3<double> ViewContext::getScale() const
{
    return Vector3<double>(
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
void ViewContext::panX( double magnitude )
{
    // get Y rotation
    double rotationY = getRotation().getY();

    // determine view plane x translation
    int quadrant = ( ( int ) ( rotationY / ( M_PI_2 ) ) ) % 4;
    double axisRotation = rotationY - ( quadrant * M_PI_2 );

    // determine tangent ratio
    double oppAdjRatio = tan( axisRotation );

    // determine axis-translation signs and magnitudes based on quadrant
    double signX;
    double signZ;
    double translateX;
    double translateZ;

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
    double thetaX = atan( translateX / translateZ );
    double thetaZ = atan( translateZ / translateX );
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
void ViewContext::panY( double magnitude )
{
    // get X rotation
    double rotationX = getRotation().getX();

    // determine view plane x translation
    int quadrant = ( ( int ) ( rotationX / ( M_PI_2 ) ) ) % 4;
    double axisRotation = rotationX - ( quadrant * M_PI_2 );

    // determine tangent ratio
    double oppAdjRatio = tan( axisRotation );

    // determine axis-translation signs and magnitudes based on quadrant
    double signY;
    double translateY;
    double translateN;

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
    double thetaY = atan( translateY / translateN );
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
Matrix<double> ViewContext::genViewTranslationMatrix() const
{
    Matrix<double> viewTranslationMatrix = Matrix<double>( 4, 4 );

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
Matrix<double> ViewContext::genViewRotationMatrix() const
{
    // generate view rotation X
    Matrix<double> viewRotationXMatrix = Matrix<double>( 4, 4 );

    viewRotationXMatrix[0][0] = 1;
    viewRotationXMatrix[3][3] = 1;

    viewRotationXMatrix[1][1] = cos( viewRotationX );
    viewRotationXMatrix[1][2] = -sin( viewRotationX );
    viewRotationXMatrix[2][1] = sin( viewRotationX );
    viewRotationXMatrix[2][2] = cos( viewRotationX );

    // generate view rotation Y
    Matrix<double> viewRotationYMatrix = Matrix<double>( 4, 4 );

    viewRotationYMatrix[1][1] = 1;
    viewRotationYMatrix[3][3] = 1;

    viewRotationYMatrix[0][0] = cos( viewRotationY );
    viewRotationYMatrix[2][0] = -sin( viewRotationY );
    viewRotationYMatrix[0][2] = sin( viewRotationY );
    viewRotationYMatrix[2][2] = cos( viewRotationY );

    // generate combined rotation matrix x -> y
    Matrix<double> viewRotationMatrix =
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
Matrix<double> ViewContext::genViewScaleMatrix() const
{
    Matrix<double> viewScaleMatrix = Matrix<double>( 4, 4 );

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
Matrix<double> ViewContext::genInvViewTranslationMatrix() const
{
    Matrix<double> invViewTranslationMatrix = genViewTranslationMatrix();

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
Matrix<double> ViewContext::genInvViewRotationMatrix() const
{
    Matrix<double> invViewRotationMatrix = genViewRotationMatrix();

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
Matrix<double> ViewContext::genInvViewScaleMatrix() const
{
    Matrix<double> invViewScaleMatrix = genViewScaleMatrix();

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
Matrix<double> ViewContext::genScreenTranslationMatrix() const
{
    Matrix<double> screenTranslationMatrix = Matrix<double>( 4, 4 );

    screenTranslationMatrix[0][0] = 1;
    screenTranslationMatrix[1][1] = 1;
    screenTranslationMatrix[2][2] = 1;
    screenTranslationMatrix[3][3] = 1;

    screenTranslationMatrix[0][3] = ( ( double ) gc->getWindowWidth() ) / 2;
    screenTranslationMatrix[1][3] = ( ( double ) gc->getWindowHeight() ) / 2;

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
Matrix<double> ViewContext::genScreenFlipMatrix() const
{
    Matrix<double> screenFlipMatrix = Matrix<double>( 4, 4 );

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
Matrix<double> ViewContext::genInvScreenTranslationMatrix() const
{
    Matrix<double> invScreenTranslationMatrix = genScreenTranslationMatrix();

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
Matrix<double> ViewContext::genInvScreenFlipMatrix() const
{
    Matrix<double> invScreenFlipMatrix = genScreenFlipMatrix();

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