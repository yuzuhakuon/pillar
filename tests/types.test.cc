#include "pillar/types/list.h"
#include <list>
#include <string>
#include <type_traits>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <string_view>
#include <utility>

#include "pillar/types/number.h"
#include "pillar/types/tag.h"

TEST_CASE("number test")
{
    using num1 = pillar::types::number<1, 9>;
    using num2 = pillar::types::number<2, 9>;

    CHECK(pillar::types::is_number(num1{}));
    CHECK(pillar::types::is_number(num2{}));
    CHECK(!pillar::types::is_number(1));
    CHECK(!pillar::types::is_number(1.0f));
    CHECK(!pillar::types::is_number(1.0));
    CHECK(!pillar::types::is_number(1.0L));
}

TEST_CASE("const str and tag test")
{
    constexpr std::string_view s1 = "hello";
    constexpr std::string_view s2 = "hello";
    constexpr std::string_view s3 = "world";

    constexpr char c = s1[0];

    constexpr bool eq1 = s1 == s2;
    constexpr bool eq2 = s2 == s3;
    CHECK(eq1);
    CHECK(!eq2);

    auto tag = MPP_TAG(tag1);
    using tagType = decltype(tag);

    CHECK(tag.kStr == "tag1");
}

TEST_CASE("list test")
{
    using list1 = pillar::types::list<std::string, int, int>;
    using list2 = pillar::types::list<int>;

    CHECK(pillar::types::is_list_v<list2>);
    CHECK(!pillar::types::is_list_v<int>);
    CHECK(!pillar::types::is_list_v<std::string>);
    CHECK(!pillar::types::is_list_v<std::vector<int>>);

    CHECK(std::is_same_v<decltype(pillar::types::concat(list2{}, list2{})),
                         pillar::types::list<int, int>>);

    CHECK(std::is_same_v<decltype(pillar::types::filter<std::is_integral>(list1{})),
                         pillar::types::list<int, int>>);

    CHECK(std::is_same_v<decltype(pillar::types::find<std::is_integral>(list1{})), int>);
    CHECK(std::is_same_v<decltype(pillar::types::find<std::is_integral>(
                             pillar::types::list<std::string>{})),
                         void>);

    CHECK(std::is_same_v<decltype(pillar::types::head(list1{})), std::string>);
    CHECK(std::is_same_v<decltype(pillar::types::head(pillar::types::list<>{})), void>);

    CHECK(pillar::types::len(list1{}) == 3);
    CHECK(pillar::types::len(list2{}) == 1);
    CHECK(pillar::types::len(pillar::types::list<>{}) == 0);

    CHECK(std::is_same_v<decltype(pillar::types::select<0>(list1{})), std::string>);
    CHECK(std::is_same_v<decltype(pillar::types::select<1>(list1{})), int>);

    CHECK(pillar::types::contains<int>(list1{}));
    CHECK(!pillar::types::contains<char>(list1{}));

    CHECK(std::is_same_v<decltype(pillar::types::set(list1{})),
                         pillar::types::list<std::string, int>>);
}