/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Object_Eigen__
#define __OpenSpaceToolkit_Mathematics_Object_Eigen__

#include <limits>
#include <sstream>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

/// @brief                      Check if the matrix/vector is defined (not NaN and not Inf)
///
/// @code{.cpp}
///     Vector3d v(1.0, 2.0, 3.0);
///     v.isDefined();  // true
/// @endcode
///
/// @return                     True if all elements are finite and not NaN
bool isDefined() const
{
    return (!this->isNaN()) && (!this->isInf());
}

/// @brief                      Check if any element of the matrix/vector is NaN
///
/// @code{.cpp}
///     Vector3d v(1.0, std::numeric_limits<double>::quiet_NaN(), 3.0);
///     v.isNaN();  // true
/// @endcode
///
/// @return                     True if any element is NaN
bool isNaN() const
{
    for (auto rowIdx = 0; rowIdx < this->rows(); ++rowIdx)
    {
        for (auto colIdx = 0; colIdx < this->cols(); ++colIdx)
        {
            if (std::isnan(this->operator()(rowIdx, colIdx)))
            {
                return true;
            }
        }
    }

    return false;
}

/// @brief                      Check if any element of the matrix/vector is infinite
///
/// @code{.cpp}
///     Vector3d v(1.0, std::numeric_limits<double>::infinity(), 3.0);
///     v.isInf();  // true
/// @endcode
///
/// @return                     True if any element is infinite
bool isInf() const
{
    for (auto rowIdx = 0; rowIdx < this->rows(); ++rowIdx)
    {
        for (auto colIdx = 0; colIdx < this->cols(); ++colIdx)
        {
            if (std::isinf(this->operator()(rowIdx, colIdx)))
            {
                return true;
            }
        }
    }

    return false;
}

/// @brief                      Check if the matrix/vector is near another within a tolerance
///
/// @code{.cpp}
///     Vector3d v1(1.0, 2.0, 3.0);
///     Vector3d v2(1.0, 2.0, 3.0 + 1e-10);
///     v1.isNear(v2, 1e-9);  // true
/// @endcode
///
/// @param                      [in] aMatrix A matrix/vector to compare against
/// @param                      [in] aTolerance A numerical tolerance on the norm of the difference
/// @return                     True if the norm of the difference is within the tolerance
bool isNear(const Derived& aMatrix, const RealScalar aTolerance) const
{
    if (!this->isDefined() || (!aMatrix.isDefined()))
    {
        throw std::runtime_error("Object is undefined.");
    }

    if (this->size() != aMatrix.size())
    {
        throw std::runtime_error("Cannot compare objects of different size.");
    }

    return ((*this) - aMatrix).norm() <= aTolerance;
}

// template <typename OtherDerived>
// inline RealScalar               isNear                                      (   const   MatrixBase<OtherDerived>&
// aMatrix,
//                                                                                 const   RealScalar aTolerance ) const
// {
//     return (this->derived() - aMatrix).norm() <= (aTolerance * aTolerance) ;
// }

/// @brief                      Convert an integer scalar to a string
///
/// @code{.cpp}
///     std::string str = ScalarToString(42, -1);  // "42"
/// @endcode
///
/// @param                      [in] aScalar An integer scalar value
/// @param                      [in] aPrecision A precision (unused for integers)
/// @return                     String representation of the scalar
static std::string ScalarToString(int aScalar, int aPrecision)
{
    (void)aPrecision;

    return std::to_string(aScalar);
}

/// @brief                      Convert a double scalar to a string
///
/// @code{.cpp}
///     std::string str = ScalarToString(3.14, 2);  // "3.14"
/// @endcode
///
/// @param                      [in] aScalar A double scalar value
/// @param                      [in] aPrecision A precision (number of decimal places, or -1 for automatic)
/// @return                     String representation of the scalar
static std::string ScalarToString(double aScalar, int aPrecision)
{
    std::string scalarString;

    double integerPart;

    if ((aPrecision < 0) && (std::modf(aScalar, &integerPart) == 0.0))  // If scalar is integer
    {
        scalarString += std::to_string(aScalar);

        scalarString.erase(scalarString.find_last_not_of('0') + 1, std::string::npos);

        scalarString += "0";
    }
    else
    {
        std::ostringstream stringStream;

        if (aPrecision >= 0)
        {
            stringStream.precision(aPrecision);

            stringStream << std::fixed << aScalar;
        }
        else
        {
            stringStream.precision(15);

            stringStream << aScalar;
        }

        scalarString = stringStream.str();

        // if ((aPrecision < 0) && (scalarString.length() > 2) && (scalarString[scalarString.length() - 2] != '.'))
        // {
        //     scalarString.erase(scalarString.find_last_not_of('0') + 1, std::string::npos) ;
        // }
    }

    return scalarString;
}

/// @brief                      Convert the matrix/vector to a string representation
///
/// @code{.cpp}
///     Vector3d v(1.0, 2.0, 3.0);
///     v.toString();  // "[1.0, 2.0, 3.0]"
/// @endcode
///
/// @param                      [in] aPrecision A precision (number of decimal places, or -1 for automatic)
/// @return                     String representation of the matrix/vector
std::string toString(int aPrecision = -1) const
{
    std::string string;

    string += "[";

    for (auto row = 0; row < this->rows(); ++row)
    {
        if (this->cols() > 1)
        {
            string += "[";
        }

        for (auto col = 0; col < this->cols(); ++col)
        {
            const Scalar& value = this->operator()(row, col);

            if (std::isnan(value))
            {
                string += "NaN";
            }
            else if (std::isinf(value))
            {
                string += "Inf";
            }
            else
            {
                string += ScalarToString(value, aPrecision);
            }

            if (col != (this->cols() - 1))
            {
                string += ", ";
            }
        }

        if (this->cols() > 1)
        {
            string += "]";
        }

        if (row != (this->rows() - 1))
        {
            string += ", ";
        }
    }

    string += "]";

    return string;
}

/// @brief                      Construct a unit vector along the X axis
///
/// @code{.cpp}
///     Vector3d x = Vector3d::X();  // (1.0, 0.0, 0.0)
/// @endcode
///
/// @return                     (1.0, 0.0, 0.0) vector
static Matrix<Scalar, 3, 1> X()
{
    return Matrix<Scalar, 3, 1>(1.0, 0.0, 0.0);
}

/// @brief                      Construct a unit vector along the Y axis
///
/// @code{.cpp}
///     Vector3d y = Vector3d::Y();  // (0.0, 1.0, 0.0)
/// @endcode
///
/// @return                     (0.0, 1.0, 0.0) vector
static Matrix<Scalar, 3, 1> Y()
{
    return Matrix<Scalar, 3, 1>(0.0, 1.0, 0.0);
}

/// @brief                      Construct a unit vector along the Z axis
///
/// @code{.cpp}
///     Vector3d z = Vector3d::Z();  // (0.0, 0.0, 1.0)
/// @endcode
///
/// @return                     (0.0, 0.0, 1.0) vector
static Matrix<Scalar, 3, 1> Z()
{
    return Matrix<Scalar, 3, 1>(0.0, 0.0, 1.0);
}

/// @brief                      Construct an undefined fixed-size matrix/vector (all NaN)
///
/// @code{.cpp}
///     Vector3d v = Vector3d::Undefined();
/// @endcode
///
/// @return                     Undefined matrix/vector
static Derived Undefined()
{
    return Derived::NaN();
}

/// @brief                      Construct an undefined dynamic-size vector of given size (all NaN)
///
/// @code{.cpp}
///     VectorXd v = VectorXd::Undefined(5);
/// @endcode
///
/// @param                      [in] aSize The vector size
/// @return                     Undefined vector
static Matrix<Scalar, Dynamic, 1> Undefined(Index aSize)
{
    return Matrix<Scalar, Dynamic, 1>::NaN(aSize);
}

/// @brief                      Construct an undefined dynamic-size matrix of given dimensions (all NaN)
///
/// @code{.cpp}
///     MatrixXd m = MatrixXd::Undefined(3, 3);
/// @endcode
///
/// @param                      [in] aRowCount The number of rows
/// @param                      [in] aColumnCount The number of columns
/// @return                     Undefined matrix
static Matrix<Scalar, Dynamic, Dynamic> Undefined(Index aRowCount, Index aColumnCount)
{
    return Matrix<Scalar, Dynamic, Dynamic>::NaN(aRowCount, aColumnCount);
}

/// @brief                      Construct a fixed-size matrix/vector filled with NaN values
///
/// @code{.cpp}
///     Vector3d v = Vector3d::NaN();
/// @endcode
///
/// @return                     NaN matrix/vector
static Derived NaN()
{
    return std::numeric_limits<double>::quiet_NaN() * Derived::Ones();
}

/// @brief                      Construct a dynamic-size vector filled with NaN values
///
/// @code{.cpp}
///     VectorXd v = VectorXd::NaN(5);
/// @endcode
///
/// @param                      [in] aSize The vector size
/// @return                     NaN vector
static Matrix<Scalar, Dynamic, 1> NaN(Index aSize)
{
    Matrix<Scalar, Dynamic, 1> matrix(aSize);

    for (auto idx = 0; idx < aSize; idx++)
    {
        matrix(idx, 0) = std::numeric_limits<double>::quiet_NaN();
    }

    return matrix;
}

/// @brief                      Construct a dynamic-size matrix filled with NaN values
///
/// @code{.cpp}
///     MatrixXd m = MatrixXd::NaN(3, 3);
/// @endcode
///
/// @param                      [in] aRowCount The number of rows
/// @param                      [in] aColumnCount The number of columns
/// @return                     NaN matrix
static Matrix<Scalar, Dynamic, Dynamic> NaN(Index aRowCount, Index aColumnCount)
{
    Matrix<Scalar, Dynamic, Dynamic> matrix(aRowCount, aColumnCount);

    for (auto rowIdx = 0; rowIdx < aRowCount; rowIdx++)
    {
        for (auto colIdx = 0; colIdx < aColumnCount; colIdx++)
        {
            matrix(rowIdx, colIdx) = std::numeric_limits<double>::quiet_NaN();
        }
    }

    return matrix;
}

/// @brief                      Construct a fixed-size matrix/vector filled with infinity values
///
/// @code{.cpp}
///     Vector3d v = Vector3d::Inf();
/// @endcode
///
/// @return                     Infinity matrix/vector
static Derived Inf()
{
    return std::numeric_limits<double>::infinity() * Derived::Ones();
}

/// @brief                      Construct a dynamic-size vector filled with infinity values
///
/// @code{.cpp}
///     VectorXd v = VectorXd::Inf(5);
/// @endcode
///
/// @param                      [in] aSize The vector size
/// @return                     Infinity vector
static Matrix<Scalar, Dynamic, 1> Inf(Index aSize)
{
    Matrix<Scalar, Dynamic, 1> matrix(aSize);

    for (auto idx = 0; idx < aSize; idx++)
    {
        matrix(idx, 0) = std::numeric_limits<double>::infinity();
    }

    return matrix;
}

/// @brief                      Construct a dynamic-size matrix filled with infinity values
///
/// @code{.cpp}
///     MatrixXd m = MatrixXd::Inf(3, 3);
/// @endcode
///
/// @param                      [in] aRowCount The number of rows
/// @param                      [in] aColumnCount The number of columns
/// @return                     Infinity matrix
static Matrix<Scalar, Dynamic, Dynamic> Inf(Index aRowCount, Index aColumnCount)
{
    Matrix<Scalar, Dynamic, Dynamic> matrix(aRowCount, aColumnCount);

    for (auto rowIdx = 0; rowIdx < aRowCount; rowIdx++)
    {
        for (auto colIdx = 0; colIdx < aColumnCount; colIdx++)
        {
            matrix(rowIdx, colIdx) = std::numeric_limits<double>::infinity();
        }
    }

    return matrix;
}

/// @brief                      Parse a string representation into a dynamic-size vector
///
/// @code{.cpp}
///     auto vector = VectorXd::Parse("[1.0, 2.0, 3.0]");
/// @endcode
///
/// @param                      [in] aString A string in the format "[x, y, z, ...]"
/// @return                     Parsed vector
static Matrix<Scalar, Dynamic, 1> Parse(const std::string& aString)
{
    if ((aString.length() < 3) || ((aString.at(0) != '[') || (aString.at(aString.length() - 1) != ']')))
    {
        throw std::runtime_error("Cannot parse [" + aString + "] to vector.");
    }

    std::string stringWithoutBrackets = aString.substr(1, aString.size() - 2);

    Index elementCount = 0;

    {
        std::istringstream stringStream(stringWithoutBrackets);

        std::string token;

        while (getline(stringStream, token, ','))
        {
            elementCount++;
        }
    }

    Matrix<Scalar, Dynamic, 1> components(elementCount);

    {
        std::istringstream stringStream(stringWithoutBrackets);

        std::string token;
        Index elementIndex = 0;

        while (getline(stringStream, token, ','))
        {
            components(elementIndex) = atof(token.data());

            elementIndex++;
        }
    }

    return components;
}

#endif
