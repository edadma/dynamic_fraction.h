/**
 * @file test_fraction.c
 * @brief Unit tests for dynamic_fraction.h library
 */

#define UNITY_INCLUDE_DOUBLE
#define DI_IMPLEMENTATION
#define DF_IMPLEMENTATION
#include "dynamic_fraction.h"
#include "devDeps/unity/unity.h"
#include <stdio.h>
#include <string.h>
#include <float.h>

void setUp(void) {
    // Setup code if needed
}

void tearDown(void) {
    // Cleanup code if needed
}

// Test basic fraction creation
void test_create_fraction(void) {
    df_frac f = df_from_ints(3, 4);
    TEST_ASSERT_NOT_NULL(f);

    double val = df_to_double(f);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.75, val);

    df_release(&f);
    TEST_ASSERT_NULL(f);
}

// Test fraction reduction
void test_fraction_reduction(void) {
    df_frac f = df_from_ints(6, 8);  // Should reduce to 3/4
    TEST_ASSERT_NOT_NULL(f);

    di_int num = df_numerator(f);
    di_int den = df_denominator(f);

    int64_t num_val, den_val;
    TEST_ASSERT_TRUE(di_to_int64(num, &num_val));
    TEST_ASSERT_TRUE(di_to_int64(den, &den_val));

    TEST_ASSERT_EQUAL_INT64(3, num_val);
    TEST_ASSERT_EQUAL_INT64(4, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&f);
}

// Test negative fractions
void test_negative_fractions(void) {
    // Negative numerator
    df_frac f1 = df_from_ints(-3, 4);
    TEST_ASSERT_TRUE(df_is_negative(f1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -0.75, df_to_double(f1));

    // Negative denominator (should move sign to numerator)
    df_frac f2 = df_from_ints(3, -4);
    TEST_ASSERT_TRUE(df_is_negative(f2));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -0.75, df_to_double(f2));

    // Both negative (should be positive)
    df_frac f3 = df_from_ints(-3, -4);
    TEST_ASSERT_TRUE(df_is_positive(f3));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.75, df_to_double(f3));

    df_release(&f1);
    df_release(&f2);
    df_release(&f3);
}

// Test addition
void test_addition(void) {
    df_frac a = df_from_ints(1, 2);  // 1/2
    df_frac b = df_from_ints(1, 3);  // 1/3
    df_frac sum = df_add(a, b); // Should be 5/6

    TEST_ASSERT_NOT_NULL(sum);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 5.0/6.0, df_to_double(sum));

    di_int num = df_numerator(sum);
    di_int den = df_denominator(sum);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(5, num_val);
    TEST_ASSERT_EQUAL_INT64(6, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&a);
    df_release(&b);
    df_release(&sum);
}

// Test subtraction
void test_subtraction(void) {
    df_frac a = df_from_ints(3, 4);  // 3/4
    df_frac b = df_from_ints(1, 2);  // 1/2
    df_frac diff = df_sub(a, b); // Should be 1/4

    TEST_ASSERT_NOT_NULL(diff);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.25, df_to_double(diff));

    di_int num = df_numerator(diff);
    di_int den = df_denominator(diff);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(1, num_val);
    TEST_ASSERT_EQUAL_INT64(4, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&a);
    df_release(&b);
    df_release(&diff);
}

// Test multiplication
void test_multiplication(void) {
    df_frac a = df_from_ints(2, 3);  // 2/3
    df_frac b = df_from_ints(3, 5);  // 3/5
    df_frac prod = df_mul(a, b); // Should be 6/15 = 2/5

    TEST_ASSERT_NOT_NULL(prod);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0/5.0, df_to_double(prod));

    di_int num = df_numerator(prod);
    di_int den = df_denominator(prod);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(2, num_val);
    TEST_ASSERT_EQUAL_INT64(5, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&a);
    df_release(&b);
    df_release(&prod);
}

// Test division
void test_division(void) {
    df_frac a = df_from_ints(2, 3);  // 2/3
    df_frac b = df_from_ints(4, 5);  // 4/5
    df_frac quot = df_div(a, b); // Should be (2/3) / (4/5) = 10/12 = 5/6

    TEST_ASSERT_NOT_NULL(quot);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 5.0/6.0, df_to_double(quot));

    di_int num = df_numerator(quot);
    di_int den = df_denominator(quot);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(5, num_val);
    TEST_ASSERT_EQUAL_INT64(6, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&a);
    df_release(&b);
    df_release(&quot);
}

// Test comparison functions
void test_comparison(void) {
    df_frac a = df_from_ints(1, 2);
    df_frac b = df_from_ints(2, 3);
    df_frac c = df_from_ints(3, 6);  // Equal to 1/2

    TEST_ASSERT_TRUE(df_lt(a, b));   // 1/2 < 2/3
    TEST_ASSERT_FALSE(df_gt(a, b));  // 1/2 not > 2/3
    TEST_ASSERT_TRUE(df_eq(a, c));   // 1/2 == 3/6
    TEST_ASSERT_FALSE(df_ne(a, c));  // 1/2 not != 3/6
    TEST_ASSERT_TRUE(df_le(a, b));   // 1/2 <= 2/3
    TEST_ASSERT_TRUE(df_le(a, c));   // 1/2 <= 3/6
    TEST_ASSERT_FALSE(df_ge(a, b));  // 1/2 not >= 2/3
    TEST_ASSERT_TRUE(df_ge(a, c));   // 1/2 >= 3/6

    df_release(&a);
    df_release(&b);
    df_release(&c);
}

// Test special values
void test_special_values(void) {
    df_frac zero = df_zero();
    df_frac one = df_one();
    df_frac neg_one = df_neg_one();

    TEST_ASSERT_TRUE(df_is_zero(zero));
    TEST_ASSERT_FALSE(df_is_zero(one));

    TEST_ASSERT_TRUE(df_is_one(one));
    TEST_ASSERT_FALSE(df_is_one(zero));

    TEST_ASSERT_TRUE(df_is_negative(neg_one));
    TEST_ASSERT_FALSE(df_is_positive(neg_one));

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, df_to_double(zero));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, df_to_double(one));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -1.0, df_to_double(neg_one));

    df_release(&zero);
    df_release(&one);
    df_release(&neg_one);
}

// Test reciprocal
void test_reciprocal(void) {
    df_frac f = df_from_ints(2, 3);
    df_frac recip = df_reciprocal(f);  // Should be 3/2

    TEST_ASSERT_NOT_NULL(recip);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.5, df_to_double(recip));

    di_int num = df_numerator(recip);
    di_int den = df_denominator(recip);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(3, num_val);
    TEST_ASSERT_EQUAL_INT64(2, den_val);

    di_release(&num);
    di_release(&den);
    df_release(&f);
    df_release(&recip);
}

// Test negate and absolute value
void test_negate_abs(void) {
    df_frac pos = df_from_ints(3, 4);
    df_frac neg = df_negate(pos);
    df_frac abs_neg = df_abs(neg);

    TEST_ASSERT_TRUE(df_is_positive(pos));
    TEST_ASSERT_TRUE(df_is_negative(neg));
    TEST_ASSERT_TRUE(df_is_positive(abs_neg));

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.75, df_to_double(pos));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -0.75, df_to_double(neg));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.75, df_to_double(abs_neg));

    df_release(&pos);
    df_release(&neg);
    df_release(&abs_neg);
}

// Test from/to string
void test_string_conversion(void) {
    // Test fraction string
    df_frac f1 = df_from_ints(3, 4);
    char* str1 = df_to_string(f1);
    TEST_ASSERT_NOT_NULL(str1);
    TEST_ASSERT_EQUAL_STRING("3/4", str1);

    df_frac f1_parsed = df_from_string(str1);
    TEST_ASSERT_NOT_NULL(f1_parsed);
    TEST_ASSERT_TRUE(df_eq(f1, f1_parsed));

    // Test integer string
    df_frac f2 = df_from_ints(5, 1);
    char* str2 = df_to_string(f2);
    TEST_ASSERT_NOT_NULL(str2);
    TEST_ASSERT_EQUAL_STRING("5", str2);

    df_frac f2_parsed = df_from_string("5");
    TEST_ASSERT_NOT_NULL(f2_parsed);
    TEST_ASSERT_TRUE(df_eq(f2, f2_parsed));

    // Test negative fraction
    df_frac f3 = df_from_ints(-2, 3);
    char* str3 = df_to_string(f3);
    TEST_ASSERT_NOT_NULL(str3);
    TEST_ASSERT_EQUAL_STRING("-2/3", str3);

    df_frac f3_parsed = df_from_string(str3);
    TEST_ASSERT_NOT_NULL(f3_parsed);
    TEST_ASSERT_TRUE(df_eq(f3, f3_parsed));

    free(str1);
    free(str2);
    free(str3);
    df_release(&f1);
    df_release(&f1_parsed);
    df_release(&f2);
    df_release(&f2_parsed);
    df_release(&f3);
    df_release(&f3_parsed);
}

// Test from double
void test_from_double(void) {
    // Simple fraction
    df_frac f1 = df_from_double(0.5, 1000);
    TEST_ASSERT_NOT_NULL(f1);

    di_int num = df_numerator(f1);
    di_int den = df_denominator(f1);
    int64_t num_val, den_val;
    di_to_int64(num, &num_val);
    di_to_int64(den, &den_val);

    TEST_ASSERT_EQUAL_INT64(1, num_val);
    TEST_ASSERT_EQUAL_INT64(2, den_val);

    // More complex fraction
    df_frac f2 = df_from_double(0.333333, 1000);
    TEST_ASSERT_NOT_NULL(f2);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.0/3.0, df_to_double(f2));

    // Pi approximation
    df_frac f3 = df_from_double(3.14159265, 1000);
    TEST_ASSERT_NOT_NULL(f3);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 3.14159265, df_to_double(f3));

    di_release(&num);
    di_release(&den);
    df_release(&f1);
    df_release(&f2);
    df_release(&f3);
}

// Test is_integer
void test_is_integer(void) {
    df_frac int_frac = df_from_ints(10, 2);  // 5/1 after reduction
    df_frac non_int = df_from_ints(3, 2);

    TEST_ASSERT_TRUE(df_is_integer(int_frac));
    TEST_ASSERT_FALSE(df_is_integer(non_int));

    int64_t val;
    TEST_ASSERT_TRUE(df_to_int64(int_frac, &val));
    TEST_ASSERT_EQUAL_INT64(5, val);

    TEST_ASSERT_FALSE(df_to_int64(non_int, &val));

    df_release(&int_frac);
    df_release(&non_int);
}

// Test reference counting
void test_reference_counting(void) {
    df_frac f1 = df_from_ints(3, 4);
    TEST_ASSERT_NOT_NULL(f1);

    df_frac f2 = df_retain(f1);
    TEST_ASSERT_EQUAL_PTR(f1, f2);

    df_release(&f1);
    TEST_ASSERT_NULL(f1);
    TEST_ASSERT_NOT_NULL(f2);  // f2 should still be valid

    df_release(&f2);
    TEST_ASSERT_NULL(f2);
}

// Test copy
void test_copy(void) {
    df_frac f1 = df_from_ints(7, 8);
    df_frac f2 = df_copy(f1);

    TEST_ASSERT_NOT_NULL(f2);
    TEST_ASSERT_NOT_EQUAL(f1, f2);  // Different pointers
    TEST_ASSERT_TRUE(df_eq(f1, f2)); // Same value

    df_release(&f1);
    TEST_ASSERT_NULL(f1);
    TEST_ASSERT_NOT_NULL(f2);  // f2 should still be valid

    df_release(&f2);
}

// Test df_from_di
void test_from_di(void) {
    di_int num = di_from_int64(15);
    di_int den = di_from_int64(10);
    df_frac f = df_from_di(num, den);  // Should reduce to 3/2

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.5, df_to_double(f));

    di_int result_num = df_numerator(f);
    di_int result_den = df_denominator(f);
    int64_t num_val, den_val;
    di_to_int64(result_num, &num_val);
    di_to_int64(result_den, &den_val);

    TEST_ASSERT_EQUAL_INT64(3, num_val);
    TEST_ASSERT_EQUAL_INT64(2, den_val);

    di_release(&num);
    di_release(&den);
    di_release(&result_num);
    di_release(&result_den);
    df_release(&f);
}

// Test df_from_int
void test_from_int(void) {
    df_frac f = df_from_int(42);

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_TRUE(df_is_integer(f));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 42.0, df_to_double(f));

    int64_t val;
    TEST_ASSERT_TRUE(df_to_int64(f, &val));
    TEST_ASSERT_EQUAL_INT64(42, val);

    df_release(&f);
}

// Test df_cmp
void test_cmp(void) {
    df_frac a = df_from_ints(1, 2);
    df_frac b = df_from_ints(2, 3);
    df_frac c = df_from_ints(3, 6);  // Equal to 1/2

    TEST_ASSERT_TRUE(df_cmp(a, b) < 0);  // 1/2 < 2/3
    TEST_ASSERT_TRUE(df_cmp(b, a) > 0);  // 2/3 > 1/2
    TEST_ASSERT_EQUAL_INT(0, df_cmp(a, c));  // 1/2 == 3/6

    df_release(&a);
    df_release(&b);
    df_release(&c);
}

// Test df_pow
void test_pow(void) {
    df_frac base = df_from_ints(2, 3);

    // Test positive exponent
    df_frac pow2 = df_pow(base, 2);  // (2/3)^2 = 4/9
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 4.0/9.0, df_to_double(pow2));

    // Test zero exponent
    df_frac pow0 = df_pow(base, 0);  // (2/3)^0 = 1
    TEST_ASSERT_TRUE(df_is_one(pow0));

    // Test negative exponent
    df_frac pow_neg = df_pow(base, -1);  // (2/3)^-1 = 3/2
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.5, df_to_double(pow_neg));

    df_release(&base);
    df_release(&pow2);
    df_release(&pow0);
    df_release(&pow_neg);
}

// Test rounding functions
void test_rounding(void) {
    df_frac f1 = df_from_ints(7, 3);  // 2.333...
    df_frac f2 = df_from_ints(-7, 3); // -2.333...
    df_frac f3 = df_from_ints(5, 2);  // 2.5

    // Test floor
    df_frac floor1 = df_floor(f1);
    df_frac floor2 = df_floor(f2);
    df_frac floor3 = df_floor(f3);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, df_to_double(floor1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -3.0, df_to_double(floor2));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, df_to_double(floor3));

    // Test ceil
    df_frac ceil1 = df_ceil(f1);
    df_frac ceil2 = df_ceil(f2);
    df_frac ceil3 = df_ceil(f3);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.0, df_to_double(ceil1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -2.0, df_to_double(ceil2));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3.0, df_to_double(ceil3));

    // Test truncate
    df_frac trunc1 = df_trunc(f1);
    df_frac trunc2 = df_trunc(f2);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, df_to_double(trunc1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -2.0, df_to_double(trunc2));

    // Test round
    df_frac round1 = df_round(f1);
    df_frac round2 = df_round(f2);
    df_frac round3 = df_round(f3);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, df_to_double(round1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -2.0, df_to_double(round2));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 2.0, df_to_double(round3));  // .5 rounds to even

    df_release(&f1);
    df_release(&f2);
    df_release(&f3);
    df_release(&floor1);
    df_release(&floor2);
    df_release(&floor3);
    df_release(&ceil1);
    df_release(&ceil2);
    df_release(&ceil3);
    df_release(&trunc1);
    df_release(&trunc2);
    df_release(&round1);
    df_release(&round2);
    df_release(&round3);
}

// Test df_sign
void test_sign(void) {
    df_frac pos = df_from_ints(3, 4);
    df_frac neg = df_from_ints(-3, 4);
    df_frac zero = df_zero();

    TEST_ASSERT_EQUAL_INT(1, df_sign(pos));
    TEST_ASSERT_EQUAL_INT(-1, df_sign(neg));
    TEST_ASSERT_EQUAL_INT(0, df_sign(zero));

    df_release(&pos);
    df_release(&neg);
    df_release(&zero);
}

// Test df_min and df_max
void test_min_max(void) {
    df_frac a = df_from_ints(1, 2);
    df_frac b = df_from_ints(2, 3);

    df_frac min_val = df_min(a, b);
    df_frac max_val = df_max(a, b);

    TEST_ASSERT_TRUE(df_eq(min_val, a));
    TEST_ASSERT_TRUE(df_eq(max_val, b));

    df_release(&a);
    df_release(&b);
    df_release(&min_val);
    df_release(&max_val);
}


// Test df_hash
void test_hash(void) {
    df_frac a = df_from_ints(3, 4);
    df_frac b = df_from_ints(3, 4);
    df_frac c = df_from_ints(6, 8);  // Same value as a, b
    df_frac d = df_from_ints(1, 2);  // Different value

    uint64_t hash_a = df_hash(a);
    uint64_t hash_b = df_hash(b);
    uint64_t hash_c = df_hash(c);
    uint64_t hash_d = df_hash(d);

    TEST_ASSERT_EQUAL_UINT64(hash_a, hash_b);
    TEST_ASSERT_EQUAL_UINT64(hash_a, hash_c);  // Equal values should have equal hashes
    TEST_ASSERT_NOT_EQUAL(hash_a, hash_d);     // Different values should (likely) have different hashes

    df_release(&a);
    df_release(&b);
    df_release(&c);
    df_release(&d);
}

// Test fits functions
void test_fits(void) {
    df_frac small = df_from_int(100);
    df_frac large = df_from_string("9223372036854775807");  // INT64_MAX
    df_frac fraction = df_from_ints(3, 2);

    TEST_ASSERT_TRUE(df_fits_int32(small));
    TEST_ASSERT_TRUE(df_fits_int64(small));
    TEST_ASSERT_TRUE(df_fits_double(small));

    if (large) {
        TEST_ASSERT_FALSE(df_fits_int32(large));
        TEST_ASSERT_TRUE(df_fits_int64(large));
        // Skip df_fits_double test for very large integers as it may cause precision issues
        df_release(&large);
    }

    TEST_ASSERT_FALSE(df_fits_int32(fraction));  // Not an integer
    TEST_ASSERT_FALSE(df_fits_int64(fraction));  // Not an integer
    TEST_ASSERT_TRUE(df_fits_double(fraction));

    df_release(&small);
    df_release(&fraction);
}

// Test part extraction functions
void test_parts(void) {
    df_frac f = df_from_ints(7, 3);  // 2 + 1/3

    di_int whole = df_whole_part(f);
    df_frac frac_part = df_fractional_part(f);

    int64_t whole_val;
    TEST_ASSERT_TRUE(di_to_int64(whole, &whole_val));
    TEST_ASSERT_EQUAL_INT64(2, whole_val);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0/3.0, df_to_double(frac_part));

    // Test negative fraction
    df_frac neg_f = df_from_ints(-7, 3);  // -2 - 1/3
    di_int neg_whole = df_whole_part(neg_f);
    df_frac neg_frac_part = df_fractional_part(neg_f);

    int64_t neg_whole_val;
    TEST_ASSERT_TRUE(di_to_int64(neg_whole, &neg_whole_val));
    TEST_ASSERT_EQUAL_INT64(-2, neg_whole_val);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, -1.0/3.0, df_to_double(neg_frac_part));

    di_release(&whole);
    di_release(&neg_whole);
    df_release(&f);
    df_release(&frac_part);
    df_release(&neg_f);
    df_release(&neg_frac_part);
}

int main(void) {
    UNITY_BEGIN();

    // Basic tests
    RUN_TEST(test_create_fraction);
    RUN_TEST(test_fraction_reduction);
    RUN_TEST(test_negative_fractions);

    // Arithmetic tests
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_division);

    // Comparison tests
    RUN_TEST(test_comparison);

    // Special value tests
    RUN_TEST(test_special_values);
    RUN_TEST(test_reciprocal);
    RUN_TEST(test_negate_abs);

    // Conversion tests
    RUN_TEST(test_string_conversion);
    RUN_TEST(test_from_double);
    RUN_TEST(test_is_integer);

    // Memory management tests
    RUN_TEST(test_reference_counting);
    RUN_TEST(test_copy);

    // Additional function tests
    RUN_TEST(test_from_di);
    RUN_TEST(test_from_int);
    RUN_TEST(test_cmp);
    RUN_TEST(test_pow);
    RUN_TEST(test_rounding);
    RUN_TEST(test_sign);
    RUN_TEST(test_min_max);
    RUN_TEST(test_hash);
    RUN_TEST(test_fits);
    RUN_TEST(test_parts);

    return UNITY_END();
}