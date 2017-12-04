#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../src/approximations-utils.h"

using ::testing::ElementsAreArray;


namespace {

TEST(ApproximationsUtilsTest, GetProgressTest) {

    std::vector<double> y_new {1, 2, 3, 4, 5};
    std::vector<double> y_old {0, 1, 2, 3, 3};
    EXPECT_DOUBLE_EQ(2.0, getProgress(y_new, y_old));
}

TEST(ApproximationsUtilsTest, GetResidualTest) {

    std::vector<double> y {1, 2, 3, 4, 5};
    std::vector<double> a {99, 1, 2, 3, 99};
    std::vector<double> b {99, 1, 2, 3, 99};
    std::vector<double> c {99, 1, 2, -3, 99};
    std::vector<double> F {99, 1, 2, -5, 99};
    EXPECT_DOUBLE_EQ(6.0005, getResidual(y, a, b, c, F));
}

TEST(ApproximationsTest, GetAllowdErrorTest) {

    std::vector<double> y {1, 2, 5, 4, 3};
    EXPECT_DOUBLE_EQ(0.0005, getAllowedError(y, 0.0001));
}

TEST(ApproximationsUtilsTest, GetMidValTest) {

    std::vector<double> y {1, 2, 3, 4, 5};
    EXPECT_DOUBLE_EQ(3.5, getMidVal(y, 3, false));
    EXPECT_DOUBLE_EQ(4.5, getMidVal(y, 3, true));
}

TEST(ApproximationsUtilsTest, GetZeroVector) {

    std::vector<double> z = getZeroVector(4);
    EXPECT_THAT(z, testing::ElementsAreArray({0, 0, 0, 0}));
}

TEST(ApproximationsUtilsTest, Slice) {

    std::vector<double> vec {1, 2, 3, 4, 5, 6};

    std::vector<double> z1 = slice(2, 4, vec);
    EXPECT_THAT(z1, testing::ElementsAreArray({3, 4, 5}));

    std::vector<double> z2 = slice(0, 5, vec);
    EXPECT_THAT(z2, testing::ElementsAreArray({1, 2, 3, 4, 5, 6}));
}

TEST(ApproximationsUtilsTest, NegateVector) {

    std::vector<double> vec {1, 2, 3, 4};
    std::vector<double> z = negateVector(vec);
    EXPECT_THAT(z, testing::ElementsAreArray({-1, -2, -3, -4}));
}

TEST(ApproximationsUtilsTest, GetNextFromHalfValues) {

    std::vector<double> prev {1, 2, 3, 4};
    std::vector<double> y {1.5, 3, 3.5, 4};
    std::vector<double> next = getNextFromHalfValues(prev, y);
    EXPECT_THAT(next, testing::ElementsAreArray({2, 4, 4, 4}));
}

TEST(ApproximationsUtilsTest, Get_a) {

    std::vector<double> D {0.0, 0.0, 0.0, 0.4, 0.4, 0.4};
    std::vector<double> x {0.0, 0.05, 0.1, 0.18, 0.3, 0.8};
    std::vector<double> a = get_a(D, x);

    std::vector<double> expected = {0.0, 0.0, 25.0, 10.752688172};

    ASSERT_EQ(a.size(), expected.size());
    for (unsigned i = 0; i < a.size(); i++) {
        EXPECT_NEAR(a[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, Get_b) {

    std::vector<double> D {0.0, 0.0, 0.0, 0.4, 0.4, 0.4};
    std::vector<double> x {0.0, 0.05, 0.1, 0.18, 0.3, 0.8};
    std::vector<double> b = get_b(D, x);

    std::vector<double> expected = {0.0, 38.461538462, 33.333333333, 2.580645161};

    ASSERT_EQ(b.size(), expected.size());
    for (unsigned i = 0; i < b.size(); i++) {
        EXPECT_NEAR(b[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, Get_c) {

    std::vector<double> a {0.0, 0.01, 0.04, 0.14};
    std::vector<double> b {0.1, 0.02, 0.3, 0.05};
    std::vector<double> c = get_c(0.002, 0.00013, a, b);

    EXPECT_THAT(c, testing::ElementsAreArray({1000.10013, 1000.03013, 1000.34013, 1000.19013}));
}

TEST(ApproximationsUtilsTest, SolveTridiagonalMatrix) {

    std::vector<double> a {0.0, 3.4, 3.6, 7.0, -6.0};
    std::vector<double> b {3.0, 2.3, -5.0, -0.9, 7.1};
    std::vector<double> c {2.1, -1.0, 1.9, 8.0, 0.0};
    std::vector<double> d {2.7, -0.5, 2.6, 0.6, 2.7};
    std::vector<double> actual = solveTridiagonalMatrix(a, b, c, d);

    std::vector<double> expected = {-4.0, 7.0, 3.0, -4.0, -3.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, SolveTridiagonalMatrix10) {

    std::vector<double> a {0.0, 3.4, 3.6, 7.0, 0.0};
    std::vector<double> b {0.0, -1.0, 1.9, 8.0, 0.0};
    std::vector<double> c {1.0, 2.3, -5.0, -0.9, 1.0};
    std::vector<double> d {1.0, -0.5, 2.6, 0.6, 0.0};
    std::vector<double> actual = solveTridiagonalMatrix(a, c, b, d);

    std::vector<double> expected = {1.0, -1.3134582623509368, 0.87904599659284499, 6.1703577512776837, 0.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, SolveTridiagonalMatrix01) {

    std::vector<double> a {0.0, 3.4, 3.6, 7.0, 0.0};
    std::vector<double> b {0.0, -1.0, 1.9, 8.0, 0.0};
    std::vector<double> c {1.0, 2.3, -5.0, -0.9, 1.0};
    std::vector<double> d {0.0, -0.5, 2.6, 0.6, 1.0};
    std::vector<double> actual = solveTridiagonalMatrix(a, c, b, d);

    std::vector<double> expected = {0.0, -0.6865417376490629, -1.0790459965928449, -0.17035775127768296, 1.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, SolveTridiagonalMatrix00) {

    std::vector<double> a {0.0, 3.4, 3.6, 7.0, 0.0};
    std::vector<double> b {0.0, -1.0, 1.9, 8.0, 0.0};
    std::vector<double> c {1.0, 2.3, -5.0, -0.9, 1.0};
    std::vector<double> d {0.0, -0.5, 2.6, 0.6, 0.0};
    std::vector<double> actual = solveTridiagonalMatrix(a, c, b, d);

    std::vector<double> expected = {0.0, -0.039182282793866915, 0.4098807495741057, 2.5212947189097106, 0.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, solveCustomisedTridiagonalThomasMatrix10) {

    std::vector<double> a {3.4, 3.6, 7.0};
    std::vector<double> b {-1.0, 1.9, 8.0};
    std::vector<double> c {2.3, -5.0, -0.9};
    std::vector<double> d {-0.5, 2.6, 0.6};
//    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix3(a, b, c, negateVector(d), 1.0, 0.0);
    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix2(a, b, c, d, 1.0, 0.0);

    std::vector<double> expected = {1.0, -1.3134582623509368, 0.87904599659284499, 6.1703577512776837, 0.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, solveCustomisedTridiagonalThomasMatrix01) {

    std::vector<double> a {3.4, 3.6, 7.0};
    std::vector<double> b {-1.0, 1.9, 8.0};
    std::vector<double> c {2.3, -5.0, -0.9};
    std::vector<double> d {-0.5, 2.6, 0.6};
    //    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix(a, b, c, negateVector(d), 0.0, 0.0, 1.0, 0.0);
    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix2(a, b, c, d, 0.0, 1.0);

    std::vector<double> expected = {0.0, -0.6865417376490629, -1.0790459965928449, -0.17035775127768296, 1.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}

TEST(ApproximationsUtilsTest, solveCustomisedTridiagonalThomasMatrix00) {

    std::vector<double> a {3.4, 3.6, 7.0};
    std::vector<double> b {-1.0, 1.9, 8.0};
    std::vector<double> c {2.3, -5.0, -0.9};
    std::vector<double> d {-0.5, 2.6, 0.6};
    //    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix(a, b, c, negateVector(d), 0.0, 0.0, 1.0, 0.0);
    std::vector<double> actual = solveCustomisedTridiagonalThomasMatrix2(a, b, c, d, 0.0, 0.0);

    std::vector<double> expected = {0.0, -0.039182282793866915, 0.4098807495741057, 2.5212947189097106, 0.0};

    ASSERT_EQ(actual.size(), expected.size());
    for (unsigned i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], 1e-8);
    }
}
}
