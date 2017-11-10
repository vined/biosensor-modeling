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
    EXPECT_DOUBLE_EQ(6.2, getResidual(y, a, b, c, F));
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
}
