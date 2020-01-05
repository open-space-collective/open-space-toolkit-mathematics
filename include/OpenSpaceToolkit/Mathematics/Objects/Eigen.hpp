////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Objects/Eigen.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Objects_Eigen__
#define __OpenSpaceToolkit_Mathematics_Objects_Eigen__

#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <sstream>
#include <limits>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            isDefined                                   ( ) const
{
    return (!this->isNaN()) && (!this->isInf()) ;
}

bool                            isNaN                                       ( ) const
{

    for (auto rowIdx = 0; rowIdx < this->rows(); ++rowIdx)
    {
        for (auto colIdx = 0; colIdx < this->cols(); ++colIdx)
        {
            if (std::isnan(this->operator()(rowIdx, colIdx)))
            {
                return true ;
            }
        }
    }

    return false ;

}

bool                            isInf                                       ( ) const
{

    for (auto rowIdx = 0; rowIdx < this->rows(); ++rowIdx)
    {
        for (auto colIdx = 0; colIdx < this->cols(); ++colIdx)
        {
            if (std::isinf(this->operator()(rowIdx, colIdx)))
            {
                return true ;
            }
        }
    }

    return false ;

}

bool                            isNear                                      (   const   Derived&                    aMatrix,
                                                                                const   RealScalar                  aTolerance                                  ) const
{

    if (!this->isDefined() || (!aMatrix.isDefined()))
    {
        throw std::runtime_error("Object is undefined.") ;
    }

    if (this->size() != aMatrix.size())
    {
        throw std::runtime_error("Cannot compare objects of different size.") ;
    }

    return ((*this) - aMatrix).norm() <= aTolerance ;

}

// template <typename OtherDerived>
// inline RealScalar               isNear                                      (   const   MatrixBase<OtherDerived>&   aMatrix,
//                                                                                 const   RealScalar                  aTolerance                                  ) const
// {
//     return (this->derived() - aMatrix).norm() <= (aTolerance * aTolerance) ;
// }

static std::string              ScalarToString                              (           int                         aScalar,
                                                                                        int                         aPrecision                                  )
{

    (void) aPrecision ;

    return std::to_string(aScalar) ;

}

static std::string              ScalarToString                              (           double                      aScalar,
                                                                                        int                         aPrecision                                  )
{

    std::string scalarString ;

    double integerPart ;

    if ((aPrecision < 0) && (std::modf(aScalar, &integerPart) == 0.0)) // If scalar is integer
    {

        scalarString += std::to_string(aScalar) ;

        scalarString.erase(scalarString.find_last_not_of('0') + 1, std::string::npos) ;

        scalarString += "0" ;

    }
    else
    {

        std::ostringstream stringStream ;

        if (aPrecision >= 0)
        {

            stringStream.precision(aPrecision) ;

            stringStream << std::fixed << aScalar ;

        }
        else
        {

            stringStream.precision(15) ;

            stringStream << aScalar ;

        }

        scalarString = stringStream.str() ;

        // if ((aPrecision < 0) && (scalarString.length() > 2) && (scalarString[scalarString.length() - 2] != '.'))
        // {
        //     scalarString.erase(scalarString.find_last_not_of('0') + 1, std::string::npos) ;
        // }

    }

    return scalarString ;

}

std::string                     toString                                    (           int                         aPrecision                                  =   -1 ) const
{

    std::string string ;

    string += "[" ;

    for (auto row = 0; row < this->rows(); ++row)
    {

        if (this->cols() > 1)
        {
            string += "[" ;
        }

        for (auto col = 0; col < this->cols(); ++col)
        {

            const Scalar& value = this->operator()(row, col) ;

            if (std::isnan(value))
            {
                string += "NaN" ;
            }
            else if (std::isinf(value))
            {
                string += "Inf" ;
            }
            else
            {
                string += ScalarToString(value, aPrecision) ;
            }

            if (col != (this->cols() - 1))
            {
                string += ", " ;
            }

        }

        if (this->cols() > 1)
        {
            string += "]" ;
        }

        if (row != (this->rows() - 1))
        {
            string += ", " ;
        }

    }

    string += "]" ;

    return string ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Matrix<Scalar, 3, 1>     X                                           ( )
{
    return Matrix<Scalar, 3, 1>(1.0, 0.0, 0.0) ;
}

static Matrix<Scalar, 3, 1>     Y                                           ( )
{
    return Matrix<Scalar, 3, 1>(0.0, 1.0, 0.0) ;
}

static Matrix<Scalar, 3, 1>     Z                                           ( )
{
    return Matrix<Scalar, 3, 1>(0.0, 0.0, 1.0) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Derived                  Undefined                                   ( )
{
    return Derived::NaN() ;
}

static Matrix<Scalar, Dynamic, 1> Undefined                                 (           Index                       aSize                                       )
{
    return Matrix<Scalar, Dynamic, 1>::NaN(aSize) ;
}

static Matrix<Scalar, Dynamic, Dynamic> Undefined                           (           Index                       aRowCount,
                                                                                        Index                       aColumnCount                                )
{
    return Matrix<Scalar, Dynamic, Dynamic>::NaN(aRowCount, aColumnCount) ;
}

static Derived                  NaN                                         ( )
{
    return std::numeric_limits<double>::quiet_NaN() * Derived::Ones() ;
}

static Matrix<Scalar, Dynamic, 1> NaN                                       (           Index                       aSize                                       )
{

    Matrix<Scalar, Dynamic, 1> matrix(aSize) ;

    for (auto idx = 0; idx < aSize; idx++)
    {
        matrix(idx, 0) = std::numeric_limits<double>::quiet_NaN() ;
    }

    return matrix ;

}

static Matrix<Scalar, Dynamic, Dynamic> NaN                                 (           Index                       aRowCount,
                                                                                        Index                       aColumnCount                                )
{

    Matrix<Scalar, Dynamic, Dynamic> matrix(aRowCount, aColumnCount) ;

    for (auto rowIdx = 0; rowIdx < aRowCount; rowIdx++)
    {
        for (auto colIdx = 0; colIdx < aColumnCount; colIdx++)
        {
            matrix(rowIdx, colIdx) = std::numeric_limits<double>::quiet_NaN() ;
        }
    }

    return matrix ;

}

static Derived                  Inf                                         ( )
{
    return std::numeric_limits<double>::infinity() * Derived::Ones() ;
}

static Matrix<Scalar, Dynamic, 1> Inf                                       (           Index                       aSize                                       )
{

    Matrix<Scalar, Dynamic, 1> matrix(aSize) ;

    for (auto idx = 0; idx < aSize; idx++)
    {
        matrix(idx, 0) = std::numeric_limits<double>::infinity() ;
    }

    return matrix ;

}

static Matrix<Scalar, Dynamic, Dynamic> Inf                                 (           Index                       aRowCount,
                                                                                        Index                       aColumnCount                                )
{

    Matrix<Scalar, Dynamic, Dynamic> matrix(aRowCount, aColumnCount) ;

    for (auto rowIdx = 0; rowIdx < aRowCount; rowIdx++)
    {
        for (auto colIdx = 0; colIdx < aColumnCount; colIdx++)
        {
            matrix(rowIdx, colIdx) = std::numeric_limits<double>::infinity() ;
        }
    }

    return matrix ;

}

static Matrix<Scalar, Dynamic, 1> Parse                                     (   const   std::string&                aString                                     )
{

    if ((aString.length() < 3) || ((aString.at(0) != '[') || (aString.at(aString.length() - 1) != ']')))
    {
        throw std::runtime_error("Cannot parse [" + aString + "] to vector.") ;
    }

    std::string stringWithoutBrackets = aString.substr(1, aString.size() - 2) ;

    Index elementCount = 0 ;

    {

        std::istringstream stringStream(stringWithoutBrackets) ;

        std::string token ;

        while (getline(stringStream, token, ','))
        {
            elementCount++ ;
        }

    }

    Matrix<Scalar, Dynamic, 1> components(elementCount) ;

    {

        std::istringstream stringStream(stringWithoutBrackets) ;

        std::string token ;
        Index elementIndex = 0 ;

        while (getline(stringStream, token, ','))
        {

            components(elementIndex) = atof(token.data()) ;

            elementIndex++ ;

        }

    }

    return components ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
