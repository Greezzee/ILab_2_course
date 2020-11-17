#include <gtest/gtest.h>
#include "../Matrix_Source/Matrix.h"

using namespace matrix;

TEST(ConstructorTest, Empty)
{
    Matrix<int> a{};
    EXPECT_EQ(a.GetRowCount(), 0);
    EXPECT_EQ(a.GetColCount(), 0);
}

TEST(ConstructorTest, Size)
{
    Matrix<int> a{12, 5};
    EXPECT_EQ(a.GetColCount(), 12);
    EXPECT_EQ(a.GetRowCount(), 5);

    for (int i = 0; i < 12; i++)
        for(int j = 0; j < 5; j++)
        EXPECT_EQ(a[i][j], 0);

    Matrix<int> b{19, 20, 4};
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 20; j++)
            EXPECT_EQ(b[i][j], 4);
}

TEST(ConstructorTest, Array)
{
    int a[] = {1, 2, 3, 4, 3, 2, 1, 0, 6, 6, 75634543, -8};
    Matrix<int> b{4, 3, a};

    for (int i = 0; i < b.GetRowCount(); i++) {
        for(int j = 0; j < b.GetColCount(); j++) {
            printf("%d ", b[j][i]);
            EXPECT_EQ(b[j][i], a[j * 3 + i]);
        }
        printf("\n");
    }
}

TEST(ConstructorTest, Vector)
{
    std::vector<std::vector<int>> a = {{5, 3}, {2, 7}, {3, 1}, {8, 5}, {24342, -345345}};
    Matrix<int> b{a};
    EXPECT_EQ(a.size(), b.GetColCount());
    EXPECT_EQ(a[0].size(), b.GetRowCount());
    for (int i = 0; i < b.GetColCount(); i++) {
        for(int j = 0; j < b.GetRowCount(); j++) {
            printf("%d ", b[i][j]);
            EXPECT_EQ(b[i][j], a[i][j]);
        }
        printf("\n");
    }
}

TEST(ConstructorTest, Copy)
{
    std::vector<std::vector<int>> a = {{5, 3}, {2, 7}, {3, 1}, {8, 5}, {24342, -345345}};
    Matrix<int> b{a};
    Matrix<int> c{b};

    EXPECT_EQ(c.GetColCount(), b.GetColCount());
    EXPECT_EQ(c.GetRowCount(), b.GetRowCount());
    for (int i = 0; i < b.GetColCount(); i++)
        for (int j = 0; j < b.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], b[i][j]);

    Matrix<int> d = c;
    EXPECT_EQ(c.GetColCount(), d.GetColCount());
    EXPECT_EQ(c.GetRowCount(), d.GetRowCount());
    for (int i = 0; i < c.GetColCount(); i++)
        for (int j = 0; j < c.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], d[i][j]);

    Matrix<int> e = std::vector<std::vector<int>>{{1, 2}, {3, 4}, {6, 9}};
    d = e;
    EXPECT_EQ(d.GetColCount(), e.GetColCount());
    EXPECT_EQ(d.GetRowCount(), e.GetRowCount());
    for (int i = 0; i < d.GetColCount(); i++)
        for (int j = 0; j < d.GetRowCount(); j++)
            EXPECT_EQ(d[i][j], e[i][j]);
}

TEST(FunctionTest, GetLen)
{
    Matrix<int> e = std::vector<std::vector<int>>{{1, 2, 3, 4, 6}};
    EXPECT_EQ(1, e.GetColCount());
    EXPECT_EQ(5, e.GetRowCount());
}

TEST(FunctionTest, Push)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};
    Matrix<int> e = base;
    EXPECT_EQ(3, e.GetColCount());
    EXPECT_EQ(2, e.GetRowCount());
    e.PushCol(Vector<int>{std::vector<int>{6, -9}});
    EXPECT_EQ(4, e.GetColCount());
    EXPECT_EQ(2, e.GetRowCount());
    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(e[i][j], base[i][j]);
    EXPECT_EQ(e[3][0], 6);
    EXPECT_EQ(e[3][1], -9);

    e.PushRow(Vector<int>{std::vector<int>{1, 1, 1, 1}});
    EXPECT_EQ(4, e.GetColCount());
    EXPECT_EQ(3, e.GetRowCount());

    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(e[i][j], base[i][j]);
    EXPECT_EQ(e[0][2], 1);
    EXPECT_EQ(e[1][2], 1);
    EXPECT_EQ(e[2][2], 1);
    EXPECT_EQ(e[3][2], 1);
}

TEST(FunctionTest, Pop)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};
    Matrix<int> e = base;
    EXPECT_EQ(3, e.GetColCount());
    Vector<int> elem = e.PopCol();
    EXPECT_EQ(2, e.GetColCount());
    EXPECT_EQ(elem, Vector<int>(std::vector<int>{6, -9}));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        EXPECT_EQ(e[i][j], base[i][j]);
    elem = e.PopRow();
    EXPECT_EQ(1, e.GetRowCount());
    EXPECT_EQ(elem, Vector<int>(std::vector<int>{2, 4}));
}

TEST(FunctionTest, Swap)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};
    Matrix<int> e = base;
    EXPECT_EQ(3, e.GetColCount());
    EXPECT_EQ(2, e.GetRowCount());
    e.SwapCol(1, 2);
    EXPECT_EQ(e[1][0], base[2][0]);
    EXPECT_EQ(e[1][1], base[2][1]);
    EXPECT_EQ(e[2][0], base[1][0]);
    EXPECT_EQ(e[2][1], base[1][1]);
    e = base;
    for (int i = 0; i < e.GetRowCount(); i++) {
        for(int j = 0; j < e.GetColCount(); j++) {
            //printf("%d ", e[j][i]);
        }
       // printf("\n");
    }
    e.SwapRow(0, 1);
    for (int i = 0; i < e.GetRowCount(); i++) {
        for(int j = 0; j < e.GetColCount(); j++) {
            //printf("%d ", e[j][i]);
        }
       // printf("\n");
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(e[i][0], base[i][1]);
        EXPECT_EQ(e[i][1], base[i][0]);
    }
}

TEST(FunctionTest, Slice)
{
    std::vector<std::vector<int>> base = {{1, 5, 8, 12}, {2, 6, 3, 2}, {3, 6, 3, 1}, {4, 9, 6, 0}, {5, 6, 3, 2}};

    Matrix<int> a{base};

    a = a.Slice(1, 4, 1, 3);

    EXPECT_EQ(a.GetColCount(), 3);
    EXPECT_EQ(a.GetRowCount(), 2);

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], base[i + 1][j + 1]);
}

TEST(FunctionTest, Connect)
{
    std::vector<std::vector<int>> base1 = {{1, 2}, {3, 4}, {5, 7}};
    std::vector<std::vector<int>> base2 = {{7, 9}};
    std::vector<std::vector<int>> base3 = {{7, 9}, {6, 0}, {2, 9}, {1, 1}};

    Matrix<int> a = base1;
    Matrix<int> b = base2;

    a.ConnectRight(b);

    EXPECT_EQ(a.GetColCount(), 4);
    EXPECT_EQ(a.GetRowCount(), 2);

    b = base3;
    a.ConnectDown(b);

    EXPECT_EQ(a.GetColCount(), 4);
    EXPECT_EQ(a.GetRowCount(), 4);
}

TEST(OperatorsTest, Equal)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};

    Matrix<int> a, b;

    a = base;
    b = a;

    EXPECT_EQ(a.GetColCount(), b.GetColCount());
    EXPECT_EQ(a.GetRowCount(), b.GetRowCount());

    for (int i = 0; i < a.GetColCount(); i++)
        EXPECT_EQ(a[i], b[i]);

    std::vector<std::vector<int>> base2 = {{-1, 6}, {9, 0}, {6, -33456}};
    Matrix<int> c = base2;

    b = a = c;

    for (int i = 0; i < a.GetColCount(); i++)
        for(int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], base2[i][j]);
}

TEST(OperatorsTest, SquareBrackets)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};
    Matrix<int> a = base;

    a[1] = std::vector<int>{5, 7};

    for (int i = 0; i < a.GetColCount(); i++)
        if (i != 1) {
            EXPECT_EQ(a[i][0], base[i][0]);
            EXPECT_EQ(a[i][1], base[i][1]);
        }
        else {
            EXPECT_EQ(a[i][0], 5);
            EXPECT_EQ(a[i][1], 7);
        }
}

TEST(OperatorsTest, UnaryMinus)
{
    std::vector<std::vector<int>> base = {{1, 2}, {3, 4}, {6, -9}};
    Matrix<int> a = base;
    a = -a;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], -base[i][j]);
}

TEST(OperatorsTest, Oper_Eq)
{
    std::vector<std::vector<int>> base1 = {{1, 2}, {3, 4}, {6, -9}};
    std::vector<std::vector<int>> base2 = {{8, 5}, {-3, 479}, {6000, -8639}};

    Matrix<int> a = base1, b = base2;

    a += b;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], base1[i][j] + base2[i][j]);

    a -= b;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], base1[i][j]);

    a *= -4;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], -4 * base1[i][j]);

    a /= 2;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(a[i][j], -2 * base1[i][j]);
}

TEST(OperatorsTest, BinaryOpers)
{
    std::vector<std::vector<int>> base1 = {{1, 2}, {3, 4}, {6, -9}};
    std::vector<std::vector<int>> base2 = {{8, 5}, {-3, 479}, {6000, -8639}};

    Matrix<int> a = base1, b = base2;

    Matrix<int> c = a + b;

    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], base1[i][j] + base2[i][j]);

    c = a - b;
    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], base1[i][j] - base2[i][j]);

    c = b * 4;
    for (int i = 0; i < b.GetColCount(); i++)
        for (int j = 0; j < b.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], 4 * base2[i][j]);

    c = -2 * a;
    for (int i = 0; i < a.GetColCount(); i++)
        for (int j = 0; j < a.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], -2 * base1[i][j]);

    c = b / 2;
    for (int i = 0; i < b.GetColCount(); i++)
        for (int j = 0; j < b.GetRowCount(); j++)
            EXPECT_EQ(c[i][j], base2[i][j] / 2);

    c = b = a;

    EXPECT_TRUE(c == b);

    c[2][1] = 999999;

    EXPECT_TRUE(c != b);
}

TEST(FunctionTest, Determinant)
{
    std::vector<std::vector<int>> base1 = {{1, 1}, {1, 1}};
    Matrix<int> a(base1);
    EXPECT_EQ(a.Determinant(), 0);
    printf("OK\n");
}

TEST(OperatorsTest, MatrixProduct)
{
    std::vector<std::vector<int>> base1 = {{1, -2, 2, 2}, {4, 2, 9, -1}, {6, 1, 0, 2}};
    std::vector<std::vector<int>> base2 = {{1, 2, 8}, {1, 2, -1}};
    std::vector<std::vector<int>> answer = {{57, 10, 20, 16}, {3, 1, 20, -2}};
    Matrix<int> a(base1), b(base2), ans(answer);
    auto c = a * b;
    EXPECT_EQ(c, ans);
}