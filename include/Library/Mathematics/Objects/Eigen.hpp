////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Objects/Eigen.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Objects_Eigen__
#define __Library_Mathematics_Objects_Eigen__

#include <Library/Core/Types/String.hpp>

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

std::string                     toString                                    (           uint                        aPrecision                                  =   15 ) const
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

            if (std::isnan(this->operator()(row, col)))
            {
                string += "NaN" ;
            }
            else if (std::isinf(this->operator()(row, col)))
            {
                string += "Inf" ;
            }
            else
            {
                string += std::to_string(this->operator()(row, col)) ;
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