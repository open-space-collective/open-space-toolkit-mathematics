/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Utility__
#define __OpenSpaceToolkit_Mathematics_Utility__

#include <cmath>
#include <ios>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace mathematics
{
namespace utility
{

using ostk::core::type::String;

/// @brief                      Convert a double to a string
///
///                             Matches the output of the former ostk::core::type::Real::toString:
///                             NaN is printed as "Undefined", infinities as "+Inf" / "-Inf".
///                             With a negative precision, the shortest round-trip representation is used
///                             (integral values get a ".0" suffix, trailing zeros are removed).
///                             With a non-negative precision, fixed notation with that many decimals is used.
///
/// @code{.cpp}
///                             DoubleToString(1.0) ; // "1.0"
///                             DoubleToString(0.5) ; // "0.5"
///                             DoubleToString(0.5, 3) ; // "0.500"
///                             DoubleToString(std::numeric_limits<double>::quiet_NaN()) ; // "Undefined"
/// @endcode
///
/// @param                      [in] aValue A value
/// @param                      [in] aPrecision A precision (number of decimal places, or -1 for automatic)
/// @return                     String
inline String DoubleToString(double aValue, int aPrecision = -1)
{
    if (std::isnan(aValue))
    {
        return "Undefined";
    }

    if (std::isinf(aValue))
    {
        return (aValue > 0.0) ? "+Inf" : "-Inf";
    }

    if (aPrecision < 0)
    {
        double integerPart;

        String string = boost::lexical_cast<std::string>(aValue);

        if (string.find('e') == std::string::npos)
        {
            if (std::modf(aValue, &integerPart) == 0.0)
            {
                string += ".0";
            }
            else
            {
                string.erase(string.find_last_not_of('0') + 1, std::string::npos);  // Remove trailing zeros if any
            }
        }

        return string;
    }

    std::ostringstream stringStream;

    stringStream.precision(aPrecision);

    stringStream << std::fixed << aValue;

    return stringStream.str();
}

}  // namespace utility
}  // namespace mathematics
}  // namespace ostk

#endif
