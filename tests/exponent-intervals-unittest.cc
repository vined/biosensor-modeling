#include "gtest/gtest.h"

#include "../src/exponent-intervals.h"
#include "../src/values-range.h"
#include "../src/values-net.h"

namespace {

TEST(ExponentIntervalsTest, GetUserHMax) {

    EXPECT_DOUBLE_EQ(0.001, get_user_h_max(1000));
    EXPECT_DOUBLE_EQ(0.00000001, get_user_h_max(100000000));
}

TEST(ExponentIntervalsTest, GetQ) {

    // Fails
//    EXPECT_DOUBLE_EQ(1.1405604102244249, get_q(7, 1.0/7.0));
//    EXPECT_DOUBLE_EQ(1.101111740700191, get_q(10));
    EXPECT_NEAR(1.010000193945561, get_q(100, 0.01), 1e-11);
    EXPECT_DOUBLE_EQ(1.001000000797006, get_q(1000, 0.001));
    EXPECT_DOUBLE_EQ(1.000100000000992, get_q(10000, 0.0001));
    EXPECT_DOUBLE_EQ(1.00001, get_q(100000, 0.00001));
}

TEST(ExponentIntervalsTest, GetN) {

    // N_b 10
    EXPECT_EQ(16, get_N(1.1405604102244249, 1.0/7.0));
    // N_b 10 fails (jumps between 25 and 26)
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

    EXPECT_DOUBLE_EQ(0.002, get_I_length(0.007, 0.004));
    EXPECT_DOUBLE_EQ(0.002, get_I_length(0.004, 0.007));
}

TEST(ValuesRangeTest, GetNTheta) {

    // d_e < d_m
    EXPECT_DOUBLE_EQ(400, get_N_theta(2, 2*3, 100));
    EXPECT_DOUBLE_EQ(4000, get_N_theta(2, 2*3, 1000));

    EXPECT_DOUBLE_EQ(50, get_N_theta(4, 5, 100));
    EXPECT_DOUBLE_EQ(500, get_N_theta(4, 5, 1000));

    EXPECT_DOUBLE_EQ(29, get_N_theta(7, 8, 100));
    EXPECT_DOUBLE_EQ(286, get_N_theta(7, 8, 1000));

    // d_e > d_m
    EXPECT_DOUBLE_EQ(400, get_N_theta(2*3, 2, 100));
    EXPECT_DOUBLE_EQ(4000, get_N_theta(2*3, 2, 1000));

    EXPECT_DOUBLE_EQ(50, get_N_theta(5, 4, 100));
    EXPECT_DOUBLE_EQ(500, get_N_theta(5, 4, 1000));

    EXPECT_DOUBLE_EQ(29, get_N_theta(8, 7, 100));
    EXPECT_DOUBLE_EQ(286, get_N_theta(8, 7, 1000));

    // d_e = d_m
    EXPECT_DOUBLE_EQ(0, get_N_theta(2, 2, 100));
    EXPECT_DOUBLE_EQ(0, get_N_theta(2, 2, 1000));
}

TEST(ValuesRangeTest, GetHMax) {

    // d_e < d_m
    EXPECT_DOUBLE_EQ(0.01, get_h_max(2, 2*3, 100));
    EXPECT_DOUBLE_EQ(0.001, get_h_max(2, 2*3, 1000));

    EXPECT_DOUBLE_EQ(0.01, get_h_max(4, 5, 100));
    EXPECT_DOUBLE_EQ(0.001, get_h_max(4, 5, 1000));

    EXPECT_NEAR(0.009852216748768, get_h_max(7, 8, 100), 1e-14);
    EXPECT_NEAR(0.0009990009990009, get_h_max(7, 8, 1000), 1e-14);

    // d_e > d_m
    EXPECT_DOUBLE_EQ(0.01, get_h_max(2*3, 2, 100));
    EXPECT_DOUBLE_EQ(0.001, get_h_max(2*3, 2, 1000));

    EXPECT_DOUBLE_EQ(0.01, get_h_max(5, 4, 100));
    EXPECT_DOUBLE_EQ(0.001, get_h_max(5, 4, 1000));

    EXPECT_NEAR(0.009852216748768, get_h_max(8, 7, 100), 1e-14);
    EXPECT_NEAR(0.0009990009990009, get_h_max(8, 7, 1000), 1e-14);

    // d_e = d_m
    EXPECT_DOUBLE_EQ(0.01, get_h_max(2, 2, 100));
    EXPECT_DOUBLE_EQ(0.001, get_h_max(2, 2, 1000));
}

}
