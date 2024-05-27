#pragma once
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <utility>

namespace pillar
{
namespace types
{

template <std::int64_t N, std::int64_t D = 1>
struct number
{
    constexpr static std::int64_t numer = N;
    constexpr static std::int64_t denom = D;
};

template <std::int64_t N, std::int64_t D>
constexpr bool is_number(number<N, D>)
{
    return true;
}

template <typename A>
constexpr bool is_number(A)
{
    return false;
}



template <std::int64_t N, std::int64_t D>
auto gcd(number<N, D>) -> number<N / std::gcd(N, D), D / std::gcd(N, D)>;

template <std::int64_t N1, std::int64_t D1, std::int64_t N2, std::int64_t D2>
auto add(number<N1, D1>, number<N2, D2>)
    -> decltype(gcd(std::declval<number<(N1 * D2 + N2 * D1), D1 * D2>>()));

template <std::int64_t N1, std::int64_t D1, std::int64_t N2, std::int64_t D2>
auto mul(number<N1, D1>, number<N2, D2>) -> decltype(gcd(std::declval<number<N1 * N2, D1 * D2>>()));
} // namespace types
} // namespace pillar