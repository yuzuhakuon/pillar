#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace pillar
{
namespace types
{
template <typename... Args>
struct list
{
};

template <typename T>
struct is_list : std::false_type
{
};
template <typename... Arg>
struct is_list<list<Arg...>> : std::true_type
{
};

template <typename T>
constexpr auto is_list2(T)
{
    return false;
}

template <typename... Arg>
constexpr auto is_list2(list<Arg...>)
{
    return true;
}

template <typename T>
constexpr bool is_list_v = is_list<T>::value;

template <typename... As, typename... Bs>
constexpr auto concat(list<As...>, list<Bs...>) -> list<As..., Bs...>;

template <template <typename> class Pred, typename... Args>
auto filter(list<Args...>) -> list<Args...>;

template <template <typename> class Pred, typename Head, typename... Tail>
auto filter(list<Head, Tail...>)
    -> decltype(concat(std::conditional_t<Pred<Head>::value, list<Head>, list<>>{},
                       filter<Pred>(list<Tail...>{})));

template <template <typename> class Pred, typename... Args>
auto find(list<Args...>) -> void;

template <template <typename> class Pred, typename Head, typename... Tail>
auto find(list<Head, Tail...>) ->
    typename std::conditional<Pred<Head>::value, Head, decltype(find<Pred>(list<Tail...>{}))>::type;

template <template <typename> class Fun, typename... Items>
auto map(list<Items...>) -> list<typename Fun<Items>::type...>;

template <typename... Args>
constexpr auto head(list<Args...>) -> void;

template <typename H, typename... T>
constexpr auto head(list<H, T...>) -> H;

template <typename... Args>
constexpr std::size_t len(list<Args...>)
{
    return 0;
}

template <typename H, typename... T>
constexpr std::size_t len(list<H, T...>)
{
    return len(list<T...>{}) + 1;
}

template <std::size_t I, typename T>
struct IndexedType
{
    static constexpr std::size_t kIndex = I;
    using type = T;
};

namespace internal
{
template <typename... Args, std::size_t... Is>
auto enumerate_impl(list<Args...>, std::index_sequence<Is...>) -> list<IndexedType<Is, Args>...>;

}

template <typename... Args>
auto enumerate(list<Args...> a)
    -> decltype(internal::enumerate_impl(a, std::index_sequence_for<Args...>{}));

template <std::size_t Ip, typename... Args>
auto select(list<Args...>) -> typename std::tuple_element<Ip, std::tuple<Args...>>::type;

template <typename T, typename... Args>
constexpr bool contains(list<Args...> a)
{
    using type = typename std::disjunction<std::is_same<T, Args>...>::type;
    return type::value;
}

template <typename... Args>
auto set(list<Args...>) -> list<Args...>;

template <typename Head, typename... Tail>
auto set(list<Head, Tail...>)
    -> decltype(concat(std::conditional_t<contains<Head>(list<Tail...>{}), list<>, list<Head>>{},
                       set(list<Tail...>{})));
} // namespace types
} // namespace pillar