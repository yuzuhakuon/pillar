#pragma once
#include <type_traits>
#include <utility>
#include <string_view>
#include <string>

namespace pillar
{
namespace types
{
template <char... C>
struct Tag
{
    static constexpr char const kChars[sizeof...(C) + 1] = {C..., '\0'};
    static constexpr std::string_view const kStr{kChars};
    static const std::string str() { return std::string(kStr.data(), kStr.size()); }

    template <char... Q>
    constexpr bool operator==(const Tag<Q...>& other) const
    {
        return kStr == other.kStr;
    }
    template <char... Q>
    constexpr bool operator!=(const Tag<Q...>& other) const
    {
        return !(*this == other);
    }
};

template <char... C>
constexpr auto is_tag(Tag<C...>) -> std::true_type;

template <typename A>
constexpr auto is_tag(A) -> std::false_type;

template <char... C>
using symbol = Tag<C...>;

constexpr auto make_tag(std::string_view s) {}

namespace internal
{
template <typename S, std::size_t... I>
constexpr auto tag_build_impl(S, std::index_sequence<I...>) -> Tag<S().tag[I]...>
{
    return {};
}

template <typename S>
constexpr auto tag_build(S)
{
    return tag_build_impl(S(), std::make_index_sequence<S().tag.size()>{});
}

#define MPP_TAG(s)                                                                                 \
    (                                                                                              \
        []                                                                                         \
        {                                                                                          \
            struct S                                                                               \
            {                                                                                      \
                const std::string_view tag{#s};                                             \
            };                                                                                     \
            return ::pillar::types::internal::tag_build(S());                                         \
        }())

#define MPP_TAG_TYPE(s)                                                                            \
    decltype(                                                                                              \
        []                                                                                         \
        {                                                                                          \
            struct S                                                                               \
            {                                                                                      \
                const std::string_view tag{#s};                                             \
            };                                                                                     \
            return ::pillar::types::internal::tag_build(S());                                         \
        }())

} // namespace internal
} // namespace types
} // namespace pillar