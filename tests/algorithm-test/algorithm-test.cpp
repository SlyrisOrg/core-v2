//
// Created by milerius on 14/02/18
//

//
// Created by milerius on 14/02/18.
//

#include <algorithm>
#include <numeric>
#include <list>
#include <vector>
#include <gtest/gtest.h>
#include <core/algorithm/erase_if.hpp>

TEST(EraseIf, WithVector)
{
    using VecInt = std::vector<int>;
    static_assert(!algo::is_associative_container_v<VecInt>, "");
    VecInt v{1, 2, 32, 17, 81, 27, 7, 9};
    auto copy = v;
    auto functor = [](int nb) { return nb > 10; };
    algo::erase_if(v, functor);
    copy.erase(std::remove_if(begin(copy), end(copy), functor), std::end(copy));
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(copy, v);
}

TEST(EraseIf, WithMap)
{
    using MapInt = std::map<int, int>;
    static_assert(algo::is_associative_container_v<MapInt>, "");
    MapInt map{
        {1, 2},
        {2, 13},
        {3, 37},
        {4, 8},
        {5, 13}
    };
    auto functor = [](auto &&pair) { return pair.second > 10; };
    algo::erase_if(map, functor);
    ASSERT_EQ(map.size(), 2);
}

TEST(EraseIf, WithStdList)
{
    using namespace std::string_literals;
    using ListString = std::list<std::string>;
    static_assert(!algo::is_associative_container_v<ListString>, "");
    ListString list{"i", "love", "cpp", "17"};
    auto copy = list;
    auto functor = [](auto &&str) {
        return str.size() < 3;
    };
    algo::erase_if(list, functor);
    copy.erase(std::remove_if(std::begin(copy), std::end(copy), functor), std::end(copy));
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list, copy);
    ASSERT_EQ("lovecpp"s, std::accumulate(std::begin(list), std::end(list), ""s));
}

TEST(EraseIf, WithStdSet)
{
    using namespace std::string_literals;
    using SetString = std::set<std::string>;
    static_assert(algo::is_associative_container_v<SetString>, "");
    SetString set{"i", "love", "cpp", "17"};
    auto functor = [](auto &&str) {
        return str.size() < 3;
    };
    algo::erase_if(set, functor);
    ASSERT_EQ(set.size(), 2);
    ASSERT_EQ("cpplove"s, std::accumulate(std::begin(set), std::end(set), ""s));
}
