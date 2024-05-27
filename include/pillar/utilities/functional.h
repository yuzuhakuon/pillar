#pragma once
#include <type_traits>

namespace pillar
{
template <class T>
struct remove_cvref
{
    using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

namespace internal
{
struct always_functor
{
    constexpr void operator()();
};

struct never_functor
{
};

template <typename T>
struct is_functor_impl : always_functor, std::conditional_t<std::is_class_v<T>, T, never_functor>
{
};

template <typename, typename = void>
struct has_functor : std::true_type
{
};

template <typename T>
struct has_functor<T, std::void_t<decltype(&is_functor_impl<T>::operator())>> : std::false_type
{
};
} // namespace internal

template <typename T>
constexpr bool has_functor_v = internal::has_functor<T>::value;
} // namespace pillar
