#include <gtest/gtest.h>
#include "lib/number.h"


TEST(FromInt, Positive42) {
    int2025_t result1 = from_int(42);
    int2025_t result2 = from_int(42);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, Positive1000) {
    int2025_t result1 = from_int(1000);
    int2025_t result2 = from_int(1000);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, PositiveINT32_MAX) {
    int2025_t result1 = from_int(2147483647);
    int2025_t result2 = from_int(2147483647);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, NegativeMinus42) {
    int2025_t result1 = from_int(-42);
    int2025_t result2 = from_int(-42);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, NegativeMinus1000) {
    int2025_t result1 = from_int(-1000);
    int2025_t result2 = from_int(-1000);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, NegativeINT32_MIN) {
    int2025_t result1 = from_int(-2147483648);
    int2025_t result2 = from_int(-2147483648);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, Zero) {
    int2025_t result1 = from_int(0);
    int2025_t result2 = from_int(0);
    EXPECT_TRUE(result1 == result2);
}

TEST(FromInt, DifferentValuesMismatch) {
    int2025_t result1 = from_int(42);
    int2025_t result2 = from_int(43);
    EXPECT_TRUE(result1 != result2);
}

TEST(FromInt, PositiveVsNegativeMismatch) {
    int2025_t result1 = from_int(-42);
    int2025_t result2 = from_int(42);
    EXPECT_TRUE(result1 != result2);
}


TEST(FromString, Positive42) {
    int2025_t result1 = from_string("42");
    int2025_t result2 = from_string("42");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, Positive1000) {
    int2025_t result1 = from_string("1000");
    int2025_t result2 = from_string("1000");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, PositiveINT32_MAX) {
    int2025_t result1 = from_string("2147483647");
    int2025_t result2 = from_string("2147483647");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, NegativeMinus42) {
    int2025_t result1 = from_string("-42");
    int2025_t result2 = from_string("-42");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, NegativeMinus1000) {
    int2025_t result1 = from_string("-1000");
    int2025_t result2 = from_string("-1000");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, NegativeINT32_MIN) {
    int2025_t result1 = from_string("-2147483648");
    int2025_t result2 = from_string("-2147483648");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, ZeroPositive) {
    int2025_t result1 = from_string("0");
    int2025_t result2 = from_string("0");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, ZeroNegativeEqualsPositive) {
    int2025_t result1 = from_string("-0");
    int2025_t result2 = from_string("0");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, LargeNumber20Digits) {
    int2025_t result1 = from_string("12345678901234567890");
    int2025_t result2 = from_string("12345678901234567890");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, LargeNumberNegative20Digits) {
    int2025_t result1 = from_string("-12345678901234567890");
    int2025_t result2 = from_string("-12345678901234567890");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, VeryLargeNumber600Digits) {
    int2025_t result1 = from_string("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    int2025_t result2 = from_string("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_TRUE(result1 == result2);
}

TEST(FromString, WithLeadingZeros) {
    int2025_t with_zeros = from_string("000042");
    int2025_t normal = from_string("42");
    EXPECT_TRUE(with_zeros == normal);
}

TEST(FromString, WithPlusSign) {
    int2025_t with_plus = from_string("+42");
    int2025_t without_plus = from_string("42");
    EXPECT_TRUE(with_plus == without_plus);
}