// Copyright © Loft Orbital Solutions Inc.

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Composite__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Composite__

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace geom
{
namespace d3
{
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique ;
using ostk::core::types::Index ;
using ostk::core::types::Size ;
using ostk::core::ctnr::Array ;

using ostk::math::geom::d3::Object ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Composite object

class Composite : public Object
{

    public:

        typedef                 Array<Unique<Object>>::ConstIterator            ConstIterator ;

        /// @brief              Constructor
        ///
        /// @param              [in] anObject An object

        explicit                Composite                                   (   const   Object&                     anObject                                    ) ;

        /// @brief              Constructor
        ///
        /// @param              [in] anObjectUPtr A unique pointer to object

        explicit                Composite                                   (   const   Unique<Object>&             anObjectUPtr                                ) ;

        /// @brief              Constructor
        ///
        /// @param              [in] anObjectArray An array of unique pointers to object

        explicit                Composite                                   (           Array<Unique<Object>>&&     anObjectArray                               ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] aComposite A composite

                                Composite                                   (   const   Composite&                  aComposite                                  ) ;

        /// @brief              Clone composite
        ///
        /// @return             Pointer to cloned composite

        virtual Composite*      clone                                       ( ) const override ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aComposite A composite
        /// @return             Reference to composite

        Composite&              operator =                                  (   const   Composite&                  aComposite                                  ) ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aComposite A composite object
        /// @return             True if composites are equal

        bool                    operator ==                                 (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aComposite A composite object
        /// @return             True if composites are not equal

        bool                    operator !=                                 (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Addition operator (composite concatenation)
        ///
        ///                     Concatenate (merge) composite with another composite.
        ///
        /// @param              [in] aComposite A composite
        /// @return             Concatenated composite

        Composite               operator +                                  (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Addition assignment operator (composite concatenation)
        ///
        ///                     Concatenate (merge) composite with another composite.
        ///
        /// @param              [in] aComposite A composite
        /// @return             Reference to concatenated composite

        Composite&              operator +=                                 (   const   Composite&                  aComposite                                  ) ;

        /// @brief              Check if composite is defined
        ///
        /// @code
        ///                     Composite(...).isDefined() ;
        /// @endcode
        ///
        /// @return             True if composite is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if composite is empty
        ///
        /// @code
        ///                     Composite(...).isEmpty() ;
        /// @endcode
        ///
        /// @return             True if composite is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Returns true if composite can be converted to underlying object
        ///
        ///                     Only valid if the composite only contains one object.
        ///
        /// @return             True if composite can be converted to underlying object

        template <class Type>
        bool                    is                                          ( ) const
        {

            if (!this->isDefined())
            {
                throw ostk::core::error::runtime::Undefined("Composite") ;
            }

            return (objects_.getSize() == 1) && (dynamic_cast<const Type*>(objects_.accessFirst().get()) != nullptr) ;

        }

        /// @brief              Access composite as its underlying object
        ///
        ///                     Only valid if the composite only contains one object.
        ///
        /// @return             Reference to underlying object

        template <class Type>
        const Type&             as                                          ( ) const
        {

            if (!this->isDefined())
            {
                throw ostk::core::error::runtime::Undefined("Composite") ;
            }

            if (objects_.getSize() != 1)
            {
                throw ostk::core::error::RuntimeError("Cannot convert composite: it is complex.") ;
            }

            const Type* objectPtr = dynamic_cast<const Type*>(objects_.accessFirst().get()) ;

            if (objectPtr == nullptr)
            {
                throw ostk::core::error::RuntimeError("Cannot convert composite: wrong type.") ;
            }

            return *objectPtr ;

        }

        /// @brief              Check if composite intersects object
        ///
        /// @param              [in] anObject An object
        /// @return             True if composite intersects object

        bool                    intersects                                  (   const   Object&                     anObject                                    ) const ;

        /// @brief              Check if composite intersects composite
        ///
        /// @param              [in] aComposite A composite
        /// @return             True if composite intersects composite

        bool                    intersects                                  (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Check if composite contains object
        ///
        /// @param              [in] anObject An object
        /// @return             True if composite contains object

        bool                    contains                                    (   const   Object&                     anObject                                    ) const ;

        /// @brief              Check if composite contains composite
        ///
        /// @param              [in] aComposite A composite
        /// @return             True if composite contains composite

        bool                    contains                                    (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Access object at index
        ///
        /// @param              [in] anIndex An object index
        /// @return             Reference to object

        const Object&           accessObjectAt                              (   const   Index&                      anIndex                                     ) const ;

        /// @brief              Access objects in composite
        ///
        /// @return             Reference to objects in composite

        const Array<Unique<Object>>& accessObjects                          ( ) const ;

        /// @brief              Get number of objects in composite
        ///
        /// @return             Number of objects in composite

        Size                    getObjectCount                              ( ) const ;

        /// @brief              Compute intersection of composite with object
        ///
        /// @param              [in] anObject An object
        /// @return             Intersection of composite with object

        Intersection            intersectionWith                            (   const   Object&                     anObject                                    ) const ;

        /// @brief              Compute intersection of composite with composite
        ///
        /// @param              [in] aComposite A composite
        /// @return             Intersection of composite with composite

        Intersection            intersectionWith                            (   const   Composite&                  aComposite                                  ) const ;

        /// @brief              Get const iterator to begin
        ///
        /// @return             Const iterator to begin

        Composite::ConstIterator begin                                      ( ) const ;

        /// @brief              Get const iterator to end
        ///
        /// @return             Const iterator to end

        Composite::ConstIterator end                                        ( ) const ;

        /// @brief              Print composite
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to composite
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined composite
        ///
        /// @code
        ///                     Composite composite = Composite::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined composite

        static Composite        Undefined                                   ( ) ;

        /// @brief              Constructs an empty composite
        ///
        /// @code
        ///                     Composite composite = Composite::Empty() ;
        /// @endcode
        ///
        /// @return             Empty composite

        static Composite        Empty                                       ( ) ;

    private:

        bool                    defined_ ;
        Array<Unique<Object>>   objects_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
