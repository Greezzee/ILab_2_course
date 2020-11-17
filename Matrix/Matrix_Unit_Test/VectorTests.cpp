#include <gtest/gtest.h>
#include "../Matrix_Source/Vector.h"

using namespace matrix;

TEST(ConstructorTest, Empty)
{
    Vector<int> a{};
    EXPECT_EQ(a.GetLen(), 0);
}

TEST(ConstructorTest, Size)
{
    Vector<int> a{12};
    EXPECT_EQ(a.GetLen(), 12);

    for (int i = 0; i < 12; i++)
        EXPECT_EQ(a[i], 0);

    Vector<int> b{19, 4};
    for (int i = 0; i < 19; i++)
        EXPECT_EQ(b[i], 4);
}

TEST(ConstructorTest, Array)
{
    int a[] = {1, 2, 3, 4, 3, 2, 1, 0, 6, 6, 75634543};
    Vector<int> b{sizeof(a) / sizeof(*a), a};

    for (int i = 0; i < b.GetLen(); i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(ConstructorTest, Vector)
{
    std::vector<int> a = {5, 3, 2, 7, 3, 1, 8, 5, 24342, -345345};
    Vector<int> b{a};
    EXPECT_EQ(a.size(), b.GetLen());
    for (int i = 0; i < b.GetLen(); i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST(ConstructorTest, Copy)
{
    std::vector<int> a = {5, 3, 2, 7, 3, 1, 8, 5, 24342, -345345};
    Vector<int> b{a};
    Vector<int> c{b};

    EXPECT_EQ(c.GetLen(), b.GetLen());
    for (int i = 0; i < b.GetLen(); i++)
        EXPECT_EQ(c[i], b[i]);

    Vector<int> d = c;
    EXPECT_EQ(d.GetLen(), b.GetLen());
    for (int i = 0; i < b.GetLen(); i++)
        EXPECT_EQ(d[i], b[i]);

    Vector<int> e = std::vector<int>{1, 2, 3, 4, 6};
    d = e;
    EXPECT_EQ(d.GetLen(), e.GetLen());
    for (int i = 0; i < e.GetLen(); i++)
        EXPECT_EQ(d[i], e[i]);
}

TEST(FunctionsTest, GetLen)
{
    Vector<int> e = std::vector<int>{1, 2, 3, 4, 6};
    EXPECT_EQ(5, e.GetLen());
}

TEST(FunctionTest, Push)
{
    std::vector<int> base = {1, 2, 3, 4, 6};
    Vector<int> e = base;
    EXPECT_EQ(5, e.GetLen());
    e.Push(14);
    EXPECT_EQ(6, e.GetLen());
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(e[i], base[i]);
    EXPECT_EQ(e[5], 14);
}

TEST(FunctionTest, Pop)
{
    std::vector<int> base = {1, 2, 3, 4, 6};
    Vector<int> e = base;
    EXPECT_EQ(5, e.GetLen());
    int elem = e.Pop();
    EXPECT_EQ(4, e.GetLen());
    EXPECT_EQ(elem, 6);
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(e[i], base[i]);
}

TEST(FunctionTest, Swap)
{
    std::vector<int> base = {1, 2, 3, 4, 6};
    Vector<int> e = base;
    EXPECT_EQ(5, e.GetLen());
    e.Swap(1, 3);
    EXPECT_EQ(e[1], base[3]);
    EXPECT_EQ(e[3], base[1]);
}

TEST(FunctionTest, Slice)
{
    std::vector<int> base = {1, 2, 3, 4, 6};
    Vector<int> e = base;
    EXPECT_EQ(5, e.GetLen());
    Vector<int> sl = e.Slice(1, 3);
    EXPECT_EQ(2, sl.GetLen());
    EXPECT_EQ(sl[0], base[1]);
    EXPECT_EQ(sl[1], base[2]);
}

TEST(FunctionTest, Connect)
{
    std::vector<int> base1 = {1, 2, 3, 4, 6};
    std::vector<int> base2 = {-6, 0, 4};
    Vector<int> a = base1, b = base2;
    a.Connect(b);
    EXPECT_EQ(a.GetLen(), 8);
    for(int i = 0; i < 5; i++)
        EXPECT_EQ(a[i], base1[i]);
    for(int i = 5; i < 8; i++)
        EXPECT_EQ(a[i], base2[i - 5]);
}

TEST(OperatorsTest, Equal)
{
    std::vector<int> base = {1, 2, 3, 4, 6};

    Vector<int> a, b;

    a = base;
    b = a;

    EXPECT_EQ(a.GetLen(), b.GetLen());

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], b[i]);

    std::vector<int> base2 = {-1, 6, 9, 0, 6};
    Vector<int> c = base2;

    b = a = c;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], base2[i]);
}

TEST(OperatorsTest, SquareBrackets)
{
    std::vector<int> base = {1, 2, 3, 4, 6};
    Vector<int> a = base;

    a[3] = 8;

    for (int i = 0; i < a.GetLen(); i++)
        if (i != 3)
            EXPECT_EQ(a[i], base[i]);
        else
            EXPECT_EQ(a[i], 8);
}

TEST(OperatorsTest, UnaryMinus)
{
    std::vector<int> base = {1, -2, 3, 4, -6};
    Vector<int> a = base;
    a = -a;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], -base[i]);
}

TEST(OperatorsTest, Oper_Eq)
{
    std::vector<int> base1 = {1, 2, 3, 4, 6};
    std::vector<int> base2 = {8, 5, 7, 0, -13};

    Vector<int> a = base1, b = base2;

    a += b;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], base1[i] + base2[i]);

    a -= b;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], base1[i]);

    a *= -4;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], -4 * base1[i]);

    a /= 2;

    for (int i = 0; i < a.GetLen(); i++)
        EXPECT_EQ(a[i], -2 * base1[i]);
}

TEST(OperatorsTest, BinaryOpers)
{
    std::vector<int> base1 = {1, 2, 3, 4, 6};
    std::vector<int> base2 = {8, 5, 7, 0, -13};

    Vector<int> a = base1, b = base2;

    Vector<int> c = a + b;
    for (int i = 0; i < c.GetLen(); i++)
        EXPECT_EQ(c[i], base1[i] + base2[i]);

    c = a - b;
    for (int i = 0; i < c.GetLen(); i++)
        EXPECT_EQ(c[i], base1[i] - base2[i]);

    c = b * 4;
    for (int i = 0; i < c.GetLen(); i++)
        EXPECT_EQ(c[i], base2[i] * 4);

    c = -2 * a;
    for (int i = 0; i < c.GetLen(); i++)
        EXPECT_EQ(c[i], -2 * base1[i]);

    c = b / 2;
    for (int i = 0; i < c.GetLen(); i++)
        EXPECT_EQ(c[i], base2[i] / 2);

    c = b = a;

    EXPECT_TRUE(c == b);

    c[2] = 999999;

    EXPECT_TRUE(c != b);
}

TEST(FunctionTest, DotProduct)
{
    std::vector<int> base1 = {1, 6, 8, 5, 2};
    std::vector<int> base2 = {5, -6, 1, 0, -7};
    Vector<int> a(base1), b(base2);

    EXPECT_EQ(matrix::DotProduct(a, b), -37);
}