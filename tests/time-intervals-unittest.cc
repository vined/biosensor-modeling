#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../src/time-intervals.h"

using ::testing::ElementsAreArray;


namespace {

TEST(TimeIntervalsTest, GetTimeInterval) {

    vector<double> timeIntervals = getTimeIntervals(1000, 1000000, -16);
    // 36 is log2(tau/tau_min) whole number
    EXPECT_EQ(1+36+1000000, timeIntervals.size());
    EXPECT_EQ(0, timeIntervals[0]);
    EXPECT_DOUBLE_EQ(1000.0, timeIntervals[timeIntervals.size()-1]);
}
}
