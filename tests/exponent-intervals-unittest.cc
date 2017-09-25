#include "../src/exponent-intervals.h"
#include "../src/values-range.h"
#include "../src/values-net.h"
#include "gtest/gtest.h"

namespace {

TEST(ExponentIntervalsTest, GetUserHMax) {

    EXPECT_FLOAT_EQ(0.001, get_user_h_max(1000));
    EXPECT_FLOAT_EQ(0.00000001, get_user_h_max(100000000));
}

TEST(ExponentIntervalsTest, GetQ) {

//    EXPECT_FLOAT_EQ(1.101111740700191, get_q(10));
    EXPECT_FLOAT_EQ(1.010000193945561, get_q(100, 0.01));
    EXPECT_FLOAT_EQ(1.001000000797006, get_q(1000, 0.001));
    EXPECT_FLOAT_EQ(1.000100000000992, get_q(10000, 0.0001));
    EXPECT_FLOAT_EQ(1.00001, get_q(100000, 0.00001));
}

TEST(ExponentIntervalsTest, GetN) {

    // N_b 10
//    EXPECT_EQ(26, get_N(1.101111740700191, 0.1));
    // N_b 100
    EXPECT_EQ(464, get_N(1.010000193945561, 0.01));
    // N_b 1000
    EXPECT_EQ(6913, get_N(1.001000000797006, 0.001));
    // N_b 10000
    EXPECT_EQ(92110, get_N(1.000100000000992, 0.0001));
    // N_b 100000
    EXPECT_EQ(138163, get_N(1.0001, 0.00001));
}


TEST(ValuesRangeTest, GetILength) {

    EXPECT_FLOAT_EQ(0.002, get_I_length(0.007, 0.004));
    EXPECT_FLOAT_EQ(0.002, get_I_length(0.004, 0.007));
}

}
