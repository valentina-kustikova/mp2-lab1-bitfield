#include "foo.hpp"

#include <gtest.h>

TEST(Foo, can_return_name)
{
    Foo foo;

    EXPECT_EQ("Foo", foo.GetName());
}
