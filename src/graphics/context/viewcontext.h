/* --------------------------------- Header --------------------------------- */


/**
 * @file    viewcontext.h
 * @brief   View context for view transformations
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_CONTEXT_VIEWCONTEXT_H
# define GRAPHICS_CONTEXT_VIEWCONTEXT_H


/* -------------------------------- Includes -------------------------------- */


# include "matrix.h"
# include "point3d.h"
# include "gcontext.h"


/* --------------------------------- Class ---------------------------------- */


class ViewContextException : public std::runtime_error
{
public:
    explicit ViewContextException( const std::string& msg ):
    std::runtime_error( ( std::string( "ViewContext Exception: " ) + msg ).c_str() )
    {}
};


class ViewContext
{
    /* =============================== PUBLIC =============================== */

public:

    /* ----------------------------- Attributes ----------------------------- */


    constexpr static const double DEFAULT_VIEW_TRANSLATION_X = 0;
    constexpr static const double DEFAULT_VIEW_TRANSLATION_Y = 0;
    constexpr static const double DEFAULT_VIEW_TRANSLATION_Z = 0;
    constexpr static const double DEFAULT_VIEW_ROTATION_X = 0;
    constexpr static const double DEFAULT_VIEW_ROTATION_Y = 0;
    constexpr static const double DEFAULT_VIEW_SCALE_X = 100;
    constexpr static const double DEFAULT_VIEW_SCALE_Y = 100;
    constexpr static const double DEFAULT_VIEW_SCALE_Z = 100;


    /* --------------------- Constructors / Destructors --------------------- */


    explicit ViewContext( GraphicsContext *gc );
    ~ViewContext();


    /* ------------------------------ Functions ----------------------------- */


    Point3D modelToDevice( const Point3D &p );
    Point3D deviceToModel( const Point3D &p );

    Point3D getLookVector();

    void translate( double x, double y, double z );
    void rotate( double x, double y );
    void scale( double x, double y, double z );

    void pan( double x, double y );

    void setTranslation( double x, double y, double z );
    void setRotation( double x, double y );
    void setScale( double x, double y, double z );

    Vector3<double> getTranslation() const;
    Vector2<double> getRotation() const;
    Vector3<double> getScale() const;

    void resetTranslation();
    void resetRotation();
    void resetScale();
    void resetView();

    void update();

    std::ostream &out( std::ostream &os ) const;


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Matrix<double> transform = Matrix<double>( 4, 4 );
    Matrix<double> invTransform = Matrix<double>( 4, 4 );

    double viewTranslationX = DEFAULT_VIEW_TRANSLATION_X;
    double viewTranslationY = DEFAULT_VIEW_TRANSLATION_Y;
    double viewTranslationZ = DEFAULT_VIEW_TRANSLATION_Z;
    double viewRotationX = DEFAULT_VIEW_ROTATION_X;
    double viewRotationY = DEFAULT_VIEW_ROTATION_Y;
    double viewScaleX = DEFAULT_VIEW_SCALE_X;
    double viewScaleY = DEFAULT_VIEW_SCALE_Y;
    double viewScaleZ = DEFAULT_VIEW_SCALE_Z;

    GraphicsContext *gc;


    /* ------------------------------ Functions ----------------------------- */


    void panX( double magnitude );
    void panY( double magnitude );

    Matrix<double> genViewTranslationMatrix() const;
    Matrix<double> genViewRotationMatrix() const;
    Matrix<double> genViewScaleMatrix() const;

    Matrix<double> genInvViewTranslationMatrix() const;
    Matrix<double> genInvViewRotationMatrix() const;
    Matrix<double> genInvViewScaleMatrix() const;

    Matrix<double> genScreenTranslationMatrix() const;
    Matrix<double> genScreenFlipMatrix() const;

    Matrix<double> genInvScreenTranslationMatrix() const;
    Matrix<double> genInvScreenFlipMatrix() const;


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const ViewContext &vc );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_CONTEXT_VIEWCONTEXT_H


/* -------------------------------------------------------------------------- */