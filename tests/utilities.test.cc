#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <chrono>
#include <doctest/doctest.h>
#include <string>
#include <thread>

#include "pillar/utilities/functional.h"
#include "pillar/utilities/singleton.h"
#include "pillar/utilities/timeit.h"

int wait_milliseconds(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return milliseconds;
}

struct Hello : public pillar::SingleTon<Hello>
{
    int hello(int milliseconds) { return wait_milliseconds(milliseconds); }

    void operator()() {}

private:
    Hello() = default;
    friend class SingleTon<Hello>;
};

TEST_CASE("timeit test")
{
    {
        pillar::Timer timer;
        auto ret = wait_milliseconds(100);
        auto elapsed = timer.elapsed();
        CHECK(ret == 100);
        CHECK(elapsed >= 100);
        CHECK(elapsed < (100 + 10));
    }
    {
        auto ret = pillar::timeit(wait_milliseconds, 200);
        CHECK(ret == 200);
    }
    {
        auto& h = Hello::instance();
        auto ret = pillar::timeit(&h, &Hello::hello, 130);
        CHECK(ret == 130);
    }
}

TEST_CASE("singleton test")
{
    auto& h1 = Hello::instance();
    auto& h2 = Hello::instance();

    CHECK(&h1 == &h2);
}

TEST_CASE("has functor test")
{
    constexpr bool ret1 = pillar::has_functor_v<Hello>;
    constexpr bool ret2 = pillar::has_functor_v<std::string>;
    constexpr bool ret3 = pillar::has_functor_v<decltype(wait_milliseconds)>;
    constexpr auto lambda = []() {};
    constexpr bool ret4 = pillar::has_functor_v<decltype(lambda)>;

    CHECK(ret1);
    CHECK(ret2);
    CHECK(!ret3);
    CHECK(ret4);
}