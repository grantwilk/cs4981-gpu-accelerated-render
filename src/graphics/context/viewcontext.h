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


    constexpr static const float DEFAULT_VIEW_TRANSLATION_X = 0;
    constexpr static const float DEFAULT_VIEW_TRANSLATION_Y = 0;
    constexpr static const float DEFAULT_VIEW_TRANSLATION_Z = 0;
    constexpr static const float DEFAULT_VIEW_ROTATION_X = 0;
    constexpr static const float DEFAULT_VIEW_ROTATION_Y = 0;
    constexpr static const float DEFAULT_VIEW_SCALE_X = 100;
    constexpr static const float DEFAULT_VIEW_SCALE_Y = 100;
    constexpr static const float DEFAULT_VIEW_SCALE_Z = 100;

    static float * d_viewTransform;
    static Matrix<float> transform;
    static Matrix<float> invTransform;


    /* --------------------- Constructors / Destructors --------------------- */


    explicit ViewContext( GraphicsContext *gc );
    ~ViewContext();


    /* ------------------------------ Functions ----------------------------- */


    Point3D modelToDevice( const Point3D &p );
    Point3D deviceToModel( const Point3D &p );

    Point3D getLookVector();

    void translate( float x, float y, float z );
    void rotate( float x, float y );
    void scale( float x, float y, float z );

    void pan( float x, float y );

    void setTranslation( float x, float y, float z );
    void setRotation( float x, float y );
    void setScale( float x, float y, float z );

    Vector3<float> getTranslation() const;
    Vector2<float> getRotation() const;
    Vector3<float> getScale() const;

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

    float viewTranslationX = DEFAULT_VIEW_TRANSLATION_X;
    float viewTranslationY = DEFAULT_VIEW_TRANSLATION_Y;
    float viewTranslationZ = DEFAULT_VIEW_TRANSLATION_Z;
    float viewRotationX = DEFAULT_VIEW_ROTATION_X;
    float viewRotationY = DEFAULT_VIEW_ROTATION_Y;
    float viewScaleX = DEFAULT_VIEW_SCALE_X;
    float viewScaleY = DEFAULT_VIEW_SCALE_Y;
    float viewScaleZ = DEFAULT_VIEW_SCALE_Z;

    GraphicsContext *gc;


    /* ------------------------------ Functions ----------------------------- */


    void panX( float magnitude );
    void panY( float magnitude );

    Matrix<float> genViewTranslationMatrix() const;
    Matrix<float> genViewRotationMatrix() const;
    Matrix<float> genViewScaleMatrix() const;

    Matrix<float> genInvViewTranslationMatrix() const;
    Matrix<float> genInvViewRotationMatrix() const;
    Matrix<float> genInvViewScaleMatrix() const;

    Matrix<float> genScreenTranslationMatrix() const;
    Matrix<float> genScreenFlipMatrix() const;

    Matrix<float> genInvScreenTranslationMatrix() const;
    Matrix<float> genInvScreenFlipMatrix() const;


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const ViewContext &vc );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_CONTEXT_VIEWCONTEXT_H


/* -------------------------------------------------------------------------- */