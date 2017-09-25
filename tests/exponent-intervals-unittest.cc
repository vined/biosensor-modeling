#include "../src/exponent-intervals.h"
#include "gtest/gtest.h"

namespace {

TEST(ExponentValuesNetGeneratorTest, GetHMax) {

    EXPECT_FLOAT_EQ(0.001, get_h_max(1000));
    EXPECT_FLOAT_EQ(0.00000001, get_h_max(100000000));
}

TEST(ExponentValuesNetGeneratorTest, GetQ) {

    EXPECT_FLOAT_EQ(1.010000193945561, get_q(100));
    EXPECT_FLOAT_EQ(1.001000000797006, get_q(1000));
    EXPECT_FLOAT_EQ(1.000100000000992, get_q(10000));
}

TEST(ExponentValuesNetGeneratorTest, GetN) {

    // N_b 100
    EXPECT_EQ(464, get_N(1.010000193945561, 0.01));
    // N_b 1000
    EXPECT_EQ(6913, get_N(1.001000000797006, 0.001));
    // N_b 10000
    EXPECT_EQ(92110, get_N(1.000100000000992, 0.0001));
}

}
