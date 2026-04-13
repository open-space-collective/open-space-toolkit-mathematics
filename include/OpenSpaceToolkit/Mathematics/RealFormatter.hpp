/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_RealFormatter__
#define __OpenSpaceToolkit_Mathematics_RealFormatter__

#include <fmt/format.h>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

// Add fmt formatter for ostk::core::type::Real
template <>
struct fmt::formatter<ostk::core::type::Real> : fmt::formatter<double>
{
    auto format(const ostk::core::type::Real& real, format_context& ctx) const
    {
        return fmt::formatter<double>::format(static_cast<double>(real), ctx);
    }
};

#endif
