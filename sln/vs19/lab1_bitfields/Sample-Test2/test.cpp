#include "pch.h"

#include "tbitfield.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TBitField, can_create_bitfield_with_positive_length1)
{
	ASSERT_NO_THROW(TBitField bf(3));
}