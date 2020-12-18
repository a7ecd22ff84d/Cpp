#ifndef __IS_OPTIONAL_H
#define __IS_OPTIONAL_H

#include <optional>
#include <type_traits>

namespace Types
{
template<typename T>
struct isOptional : std::false_type
{
};

template<typename T>
struct isOptional<std::optional<T>> : std::true_type
{
};

template<class T>
inline constexpr bool isOptional_v = isOptional<T>::value;

} // namespace Types

#endif // __IS_OPTIONAL_H
