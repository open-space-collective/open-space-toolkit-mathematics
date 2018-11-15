////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Transformation.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_2D_Transformation__
#define __Library_Mathematics_Geometry_2D_Transformation__

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Object.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d2
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::String ;

using library::math::obj::Vector2d ;
using library::math::obj::Vector3d ;
using library::math::obj::Matrix3d ;
using library::math::geom::Angle ;
using library::math::geom::d2::Object ;
using library::math::geom::d2::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Transformation
{

    public:

        enum class Type
        {

            Undefined,
            Identity,
            Translation,
            Rotation,
            Scaling,
            Reflection,
            Shear,
            Affine

        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] aMatrix A transformation matrix

                                Transformation                              (   const   Matrix3d&                   aMatrix                                     ) ;

        bool                    operator ==                                 (   const   Transformation&             aTransformation                             ) const ;

        bool                    operator !=                                 (   const   Transformation&             aTransformation                             ) const ;

        Transformation          operator *                                  (   const   Transformation&             aTransformation                             ) const ;

        Vector3d                operator *                                  (   const   Vector3d&                   aVector                                     ) const ;

        Transformation&         operator *=                                 (   const   Transformation&             aTransformation                             ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Transformation&             aTransformation                             ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isIdentity                                  ( ) const ;

        /// @brief              Returns true if transformation is rigid
        ///
        ///                     A rigid transformation preserves distances and angles.
        ///                     It is either a translation, a rotation, or a reflection.
        ///
        /// @ref                https://en.wikipedia.org/wiki/Rigid_transformation
        ///
        /// @return             True if transformation is rigid

        bool                    isRigid                                     ( ) const ;

        Transformation::Type    getType                                     ( ) const ;

        Matrix3d                getMatrix                                   ( ) const ;

        Transformation          getInverse                                  ( ) const ;

        Point                   applyTo                                     (   const   Point&                      aPoint                                      ) const ;
        
        Vector2d                applyTo                                     (   const   Vector2d&                   aVector                                     ) const ;

        Unique<Object>          applyTo                                     (   const   Unique<Object>&             anObject                                    ) const ; // [TBI]

        /// @brief              Print transformation
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const ;

        static Transformation   Undefined                                   ( ) ;
        
        static Transformation   Identity                                    ( ) ;
        
        static Transformation   Translation                                 (   const   Vector2d&                   aTranslationVector                          ) ;
        
        static Transformation   Rotation                                    (   const   Angle&                      aRotationAngle                              ) ;

        static Transformation   RotationAround                              (   const   Point&                      aPoint,
                                                                                const   Angle&                      aRotationAngle                              ) ;

        static String           StringFromType                              (   const   Transformation::Type&       aType                                       ) ;

        static Transformation::Type TypeOfMatrix                            (   const   Matrix3d&                   aMatrix                                     ) ;

    private:

        Transformation::Type    type_ ;
        Matrix3d                matrix_ ;

                                Transformation                              (   const   Transformation::Type&       aType,
                                                                                const   Matrix3d&                   aMatrix                                     ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////