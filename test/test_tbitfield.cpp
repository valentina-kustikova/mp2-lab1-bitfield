#include "tbitfield.h"

#include <gtest.h>

TEST(TBitField, can_create_bitfield_with_positive_length)
{
    ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, DISABLED_cant_create_bitfield_with_negative_length)
{
    ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, can_get_length)
{
    TBitField bf(3);

    EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
    TBitField bf(100);

    for (int i = 0; i < bf.GetLength(); i++)
    {
        EXPECT_EQ(0, bf.GetBit(i));
    }
}

TEST(TBitField, can_set_bit)
{
    TBitField bf(10);

    bf.SetBit(3);

    EXPECT_NE(0, bf.GetBit(3));
}

TEST(TBitField, can_clear_bit)
{
    TBitField bf(10);

    int bitIdx = 3;

    bf.SetBit(bitIdx);
    EXPECT_NE(0, bf.GetBit(bitIdx));

    bf.ClrBit(bitIdx);
    EXPECT_EQ(0, bf.GetBit(bitIdx));
}
