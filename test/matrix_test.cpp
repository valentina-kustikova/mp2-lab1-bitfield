#include "matrix.hpp"

#include <gtest/gtest.h>

TEST(Matrix, matrix_can_set_zeros)
{
    Matrix m(2, 2);

    m.Zeros();

    EXPECT_EQ(0, m[0][0]);
    EXPECT_EQ(0, m[0][1]);
    EXPECT_EQ(0, m[1][0]);
    EXPECT_EQ(0, m[1][1]);
}

TEST(Matrix, matrix_can_set_ones)
{
    Matrix m(2, 2);

    m.Ones();

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(1, m[0][1]);
    EXPECT_EQ(1, m[1][0]);
    EXPECT_EQ(1, m[1][1]);
}

TEST(Matrix, comparator_returns_true_on_equal_matrices)
{
    Matrix m1(3, 3);
    Matrix m2(3, 3);

    m1.Random(777);
    m2.Random(777);

    EXPECT_TRUE(m1 == m2);
}

TEST(Matrix, comparator_returns_false_on_non_equal_matrices)
{
    Matrix m1(3, 3);
    Matrix m2(3, 3);

    m1.Random(777);
    m2.Random(888);

    EXPECT_FALSE(m1 == m2);
}

TEST(Matrix, copy_ctor_works)
{
    Matrix m1(3, 3);
    m1.Zeros();

    Matrix m2(m1);

    EXPECT_EQ(m1, m2);
}
