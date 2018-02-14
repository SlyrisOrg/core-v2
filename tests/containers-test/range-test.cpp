//
// Created by milerius on 14/02/18.
//

#include <gtest/gtest.h>
#include <core/containers/range/erase_if.hpp>

class TestingVectorFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        static_assert(!ctr::range::is_associative_container_v<VecInt>, "");
    }

    void TearDown() override
    {
    }

public:
    using VecInt = std::vector<int>;
    VecInt v{1, 2, 32, 17, 81, 27, 7, 9};
};

class TestingMapFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        static_assert(ctr::range::is_associative_container_v<MapInt>, "");
    }

    void TearDown() override
    {
    }

public:
    using MapInt = std::map<int, int>;
    MapInt map{
        {1, 2},
        {2, 13},
        {3, 37},
        {4, 8},
        {5, 13}
    };
};

TEST_F(TestingVectorFixture, erase_if)
{
    auto copy = v;
    auto functor = [](int nb) { return nb > 10; };
    ctr::range::erase_if(v, functor);
    copy.erase(std::remove_if(begin(copy), end(copy), functor));
    ASSERT_EQ(copy, v);
}

TEST_F(TestingMapFixture, erase_if)
{
    auto copy = map;
    auto functor = [](int nb) { return nb > 10; };

    auto erase_if_functor = [&func = functor, &container = copy]() {
        for (auto it = std::begin(container); it != std::end(container);) {
            if (func(it->second)) {
                it = container.erase(it);
            } else {
                ++it;
            }
        }
    };

    ctr::range::erase_if(map, functor);
    erase_if_functor();
    ASSERT_EQ(map.size(), copy.size());
}
