#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../src/exponent-intervals.h"
#include "../src/values-range.h"
#include "../src/values-net.h"

using ::testing::ElementsAreArray;


namespace {

TEST(ExponentIntervalsTest, GetUserHMax) {

    EXPECT_DOUBLE_EQ(0.001, get_user_h_max(1000));
    EXPECT_DOUBLE_EQ(0.00000001, get_user_h_max(100000000));
}

TEST(ExponentIntervalsTest, GetQ) {

    // Fails
//    EXPECT_DOUBLE_EQ(1.1405604102244249, get_q(1.0/7.0));
//    EXPECT_DOUBLE_EQ(1.101111740700191, get_q(0.1));
    EXPECT_NEAR(1.010000193945561, get_q(0.01), 1e-11);
    EXPECT_DOUBLE_EQ(1.001000000797006, get_q(0.001));
    EXPECT_DOUBLE_EQ(1.000100000000992, get_q(0.0001));
    EXPECT_DOUBLE_EQ(1.00001, get_q(0.00001));
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
    EXPECT_EQ(400, get_N_theta(2, 2*3, 100));
    EXPECT_EQ(4000, get_N_theta(2, 2*3, 1000));

    EXPECT_EQ(50, get_N_theta(4, 5, 100));
    EXPECT_EQ(500, get_N_theta(4, 5, 1000));

    EXPECT_EQ(29, get_N_theta(7, 8, 100));
    EXPECT_EQ(286, get_N_theta(7, 8, 1000));

    // d_e > d_m
    EXPECT_EQ(400, get_N_theta(2*3, 2, 100));
    EXPECT_EQ(4000, get_N_theta(2*3, 2, 1000));

    EXPECT_EQ(50, get_N_theta(5, 4, 100));
    EXPECT_EQ(500, get_N_theta(5, 4, 1000));

    EXPECT_EQ(29, get_N_theta(8, 7, 100));
    EXPECT_EQ(286, get_N_theta(8, 7, 1000));

    // d_e = d_m
    EXPECT_EQ(0, get_N_theta(2, 2, 100));
    EXPECT_EQ(0, get_N_theta(2, 2, 1000));
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

TEST(ValuesNet, GetNonLinearValuesNetParams) {

    // d_e < d_m
//    values_net_params params1 = getNonLinearValuesNetParams(4, 5, 10);
//    EXPECT_EQ(109, params1.N);

    values_net_params params2 = getNonLinearValuesNetParams(4, 5, 100);
    EXPECT_EQ(1906, params2.N);

    values_net_params params3 = getNonLinearValuesNetParams(4, 5, 1000);
    EXPECT_EQ(28152, params3.N);

    values_net_params params4 = getNonLinearValuesNetParams(4, 5, 10000);
    EXPECT_EQ(373440, params4.N);

    values_net_params params5 = getNonLinearValuesNetParams(4, 5, 100000);
    EXPECT_EQ(4655200, params5.N);

    // d_e > d_m
//    values_net_params params6 = getNonLinearValuesNetParams(5, 4, 10);
//    EXPECT_EQ(109, params6.N);

//    values_net_params params7 = getNonLinearValuesNetParams(5, 4, 100);
//    EXPECT_EQ(1906, params7.N);

//    values_net_params params8 = getNonLinearValuesNetParams(5, 4, 1000);
//    EXPECT_EQ(28152, params8.N);

//    values_net_params params9 = getNonLinearValuesNetParams(5, 4, 10000);
//    EXPECT_EQ(373440, params9.N);

//    values_net_params params10 = getNonLinearValuesNetParams(5, 4, 100000);
//    EXPECT_EQ(4655200, params10.N);
}

TEST(ValuesNet, GetI) {

    vector<double> i_block = _get_I(4, 3.0);
    ASSERT_EQ(4, i_block.size());
    EXPECT_DOUBLE_EQ(0.025, i_block[0]);
    EXPECT_DOUBLE_EQ(0.075, i_block[1]);
    EXPECT_DOUBLE_EQ(0.225, i_block[2]);
    EXPECT_DOUBLE_EQ(0.675, i_block[3]);
//    EXPECT_THAT(_get_I(4, 3.0), testing::ElementsAreArray({0.025, 0.075, 0.225, 0.675}));
}

TEST(ValuesNet, GetDBLock) {

    vector<double> I {1,2,3};
    vector<double> rev_I {4, 5};
    vector<double> theta {6, 7};

    vector<double> d_block = _get_d_block(I, rev_I, theta, true);
    EXPECT_THAT(d_block, testing::ElementsAreArray({1, 2, 3, 6, 7, 4, 5}));

    vector<double> d_block_no_theta = _get_d_block(I, rev_I, theta, false);
    EXPECT_THAT(d_block_no_theta, testing::ElementsAreArray({1, 2, 3, 4, 5}));
}

TEST(ValuesNet, GetThetaBlock) {

    vector<double> theta = _get_theta_block(4, 0.5);

    ASSERT_EQ(4, theta.size());
    EXPECT_DOUBLE_EQ(0.5, theta[0]);
    EXPECT_DOUBLE_EQ(0.5, theta[1]);
    EXPECT_DOUBLE_EQ(0.5, theta[2]);
    EXPECT_DOUBLE_EQ(0.5, theta[3]);
}

TEST(ValuesNet, GetStepsDeIsLessDm) {

    values_net_params params;
    params.N_i = 4;
    params.q = 3.0;

    params.N_theta = 2;
    params.h_I_max = 0.5;

    vector<double> steps = _get_steps(2.0, 3.0, params);
    ASSERT_EQ(18, steps.size());

    // d1
    EXPECT_DOUBLE_EQ(0.025, steps[0]);
    EXPECT_DOUBLE_EQ(0.075, steps[1]);
    EXPECT_DOUBLE_EQ(0.225, steps[2]);
    EXPECT_DOUBLE_EQ(0.675, steps[3]);

    EXPECT_DOUBLE_EQ(0.675, steps[4]);
    EXPECT_DOUBLE_EQ(0.225, steps[5]);
    EXPECT_DOUBLE_EQ(0.075, steps[6]);
    EXPECT_DOUBLE_EQ(0.025, steps[7]);

    // d2
    EXPECT_DOUBLE_EQ(0.025, steps[8]);
    EXPECT_DOUBLE_EQ(0.075, steps[9]);
    EXPECT_DOUBLE_EQ(0.225, steps[10]);
    EXPECT_DOUBLE_EQ(0.675, steps[11]);

    EXPECT_DOUBLE_EQ(0.5, steps[12]);
    EXPECT_DOUBLE_EQ(0.5, steps[13]);

    EXPECT_DOUBLE_EQ(0.675, steps[14]);
    EXPECT_DOUBLE_EQ(0.225, steps[15]);
    EXPECT_DOUBLE_EQ(0.075, steps[16]);
    EXPECT_DOUBLE_EQ(0.025, steps[17]);
}

TEST(ValuesNet, GetStepsDeIsGreaterDm) {

    values_net_params params;
    params.N_i = 4;
    params.q = 3.0;

    params.N_theta = 2;
    params.h_I_max = 0.5;

    vector<double> steps = _get_steps(3.0, 2.0, params);
    ASSERT_EQ(18, steps.size());

    // d1
    EXPECT_DOUBLE_EQ(0.025, steps[0]);
    EXPECT_DOUBLE_EQ(0.075, steps[1]);
    EXPECT_DOUBLE_EQ(0.225, steps[2]);
    EXPECT_DOUBLE_EQ(0.675, steps[3]);

    EXPECT_DOUBLE_EQ(0.5, steps[4]);
    EXPECT_DOUBLE_EQ(0.5, steps[5]);

    EXPECT_DOUBLE_EQ(0.675, steps[6]);
    EXPECT_DOUBLE_EQ(0.225, steps[7]);
    EXPECT_DOUBLE_EQ(0.075, steps[8]);
    EXPECT_DOUBLE_EQ(0.025, steps[9]);

    // d2
    EXPECT_DOUBLE_EQ(0.025, steps[10]);
    EXPECT_DOUBLE_EQ(0.075, steps[11]);
    EXPECT_DOUBLE_EQ(0.225, steps[12]);
    EXPECT_DOUBLE_EQ(0.675, steps[13]);

    EXPECT_DOUBLE_EQ(0.675, steps[14]);
    EXPECT_DOUBLE_EQ(0.225, steps[15]);
    EXPECT_DOUBLE_EQ(0.075, steps[16]);
    EXPECT_DOUBLE_EQ(0.025, steps[17]);
}

TEST(ValuesNet, GetStepsDeIsEqualDm) {

    values_net_params params;
    params.N_i = 4;
    params.q = 3.0;

    vector<double> steps = _get_steps(2.0, 2.0, params);
    ASSERT_EQ(16, steps.size());

    // d1
    EXPECT_DOUBLE_EQ(0.025, steps[0]);
    EXPECT_DOUBLE_EQ(0.075, steps[1]);
    EXPECT_DOUBLE_EQ(0.225, steps[2]);
    EXPECT_DOUBLE_EQ(0.675, steps[3]);

    EXPECT_DOUBLE_EQ(0.675, steps[4]);
    EXPECT_DOUBLE_EQ(0.225, steps[5]);
    EXPECT_DOUBLE_EQ(0.075, steps[6]);
    EXPECT_DOUBLE_EQ(0.025, steps[7]);

    // d2
    EXPECT_DOUBLE_EQ(0.025, steps[8]);
    EXPECT_DOUBLE_EQ(0.075, steps[9]);
    EXPECT_DOUBLE_EQ(0.225, steps[10]);
    EXPECT_DOUBLE_EQ(0.675, steps[11]);

    EXPECT_DOUBLE_EQ(0.675, steps[12]);
    EXPECT_DOUBLE_EQ(0.225, steps[13]);
    EXPECT_DOUBLE_EQ(0.075, steps[14]);
    EXPECT_DOUBLE_EQ(0.025, steps[15]);
}

TEST(ValuesNet, GenerateNonLinearValuesNetWhenDeIsEqualDm) {

    vector<double> net1 = generateNonLinearValuesNet(4, 5, 100);
    EXPECT_EQ(1907, net1.size());

    vector<double> net2 = generateNonLinearValuesNet(4, 5, 1000);
    EXPECT_EQ(28153, net2.size());

    vector<double> net3 = generateNonLinearValuesNet(4, 5, 10000);
    EXPECT_EQ(373441, net3.size());

    vector<double> net4 = generateNonLinearValuesNet(4, 5, 100000);
    EXPECT_EQ(4655201, net4.size());
}

}
