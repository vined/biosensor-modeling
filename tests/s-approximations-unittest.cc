#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../src/s-approximations.h"

using ::testing::ElementsAreArray;


namespace {

    TEST(ApproximationsUtilsTest, GetProgressTest) {

    std::vector<double> y_new {1, 2, 3, 4, 5};
    std::vector<double> y_old {0, 1, 2, 3, 3};
    EXPECT_DOUBLE_EQ(2.0, getProgress(y_new, y_old));
}

}
