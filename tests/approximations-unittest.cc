#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../src/approximations.h"

using ::testing::ElementsAreArray;


namespace {

TEST(ApproximationsTest, GetProgressTest) {

    std::vector<double> y_new {1, 2, 3, 4, 5};
    std::vector<double> y_old {0, 1, 2, 3, 3};
    EXPECT_DOUBLE_EQ(2.0, _get_progress(y_new, y_old));
}

TEST(ApproximationsTest, GetResidualTest) {

    std::vector<double> y {1, 2, 3, 4, 5};
    std::vector<double> a {99, 1, 2, 3, 99};
    std::vector<double> b {99, 1, 2, 3, 99};
    std::vector<double> c {99, 1, 2, -3, 99};
    std::vector<double> F {99, 1, 2, -5, 99};
    EXPECT_DOUBLE_EQ(6.2, _get_residual(y, a, b, c, F));
}
}
