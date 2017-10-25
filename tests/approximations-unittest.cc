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
    std::vector<double> F {0, 1, 2, -3, 4};
    EXPECT_DOUBLE_EQ(7, _get_residual(y, 1, 1, -1, F));
}
}
