#pragma once
#include <chrono>
#include <iostream>
#include <ostream>
#include <string_view>
#include <type_traits>

namespace pillar
{
struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start{std::chrono::steady_clock::now()};
    std::string_view prefix = "Timer elapsed ";
    std::ostream& os = std::cout;

    ~Timer()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = end - start;
        float ms = duration.count() * 1000.0f;
        os << prefix << ms << "ms\n";
    }

    float elapsed()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = end - start;
        float ms = duration.count() * 1000.0f;
        return ms;
    }
};

template <typename T, typename... Args>
static inline auto timeit(T&& func, Args&&... args)
{
    static_assert(std::is_invocable_v<T, Args...>, "Function is not invocable");

    auto timer = Timer();
    if constexpr (std::is_same_v<decltype(func(std::forward<Args>(args)...)), void>)
    {
        func(std::forward<Args>(args)...);
    }
    else
    {
        auto ret = func(std::forward<Args>(args)...);
        return ret;
    }
}

template <typename T, typename U, typename... Args>
auto timeit(T* self, U (T::*func)(Args...), Args&&... args)
{
    static_assert(std::is_invocable_v<U (T::*)(Args...), T*, Args...>, "Function is not invocable");

    auto timer = Timer();
    if constexpr (std::is_same_v<decltype((self->*func)(std::forward<Args>(args)...)), void>)
    {
        (self->*func)(std::forward<Args>(args)...);
    }
    else
    {
        auto ret = (self->*func)(std::forward<Args>(args)...);
        return ret;
    }
}

template <typename T, typename U, typename... Args>
auto timeit(T* self, U (T::*func)(Args...) const, Args&&... args)
{
    static_assert(std::is_invocable_v<U (T::*)(Args...), T*, Args...>, "Function is not invocable");

    auto timer = Timer();
    if constexpr (std::is_same_v<decltype((self->*func)(std::forward<Args>(args)...)), void>)
    {
        (self->*func)(std::forward<Args>(args)...);
    }
    else
    {
        auto ret = (self->*func)(std::forward<Args>(args)...);
        return ret;
    }
}
} // namespace pillar