#include "../src/exponent-values-net-generator.h"
#include "gtest/gtest.h"

namespace {

TEST(ExponentValuesNetGeneratorTest, GetHMax) {

  EXPECT_FLOAT_EQ(0.001, _get_h_max(1000));
  EXPECT_FLOAT_EQ(0.00000001, _get_h_max(100000000));

//  EXPECT_NEAR (expected, actual, absolute_range)
}

TEST(ExponentValuesNetGeneratorTest, getN) {

  EXPECT_EQ(464, _get_N(100));
  EXPECT_EQ(6913, _get_N(1000));
  EXPECT_EQ(92110, _get_N(10000));
}

}
