#define DF_IMPLEMENTATION
#define DI_IMPLEMENTATION
#include "dynamic_fraction.h"
#include <stdio.h>

int main(void) {
    printf("Dynamic Fraction Library Example\n");
    printf("================================\n\n");

    // Create some fractions
    df_frac a = df_from_ints(3, 4);     // 3/4
    df_frac b = df_from_ints(2, 3);     // 2/3
    df_frac c = df_from_ints(5, 6);     // 5/6

    char *str_a = df_to_string(a);
    char *str_b = df_to_string(b);
    char *str_c = df_to_string(c);
    printf("a = %s\n", str_a);
    printf("b = %s\n", str_b);
    printf("c = %s\n", str_c);
    printf("\n");

    // Arithmetic operations
    df_frac sum = df_add(a, b);
    char *str_sum = df_to_string(sum);
    printf("a + b = %s = %f\n", str_sum, df_to_double(sum));

    df_frac diff = df_sub(c, a);
    char *str_diff = df_to_string(diff);
    printf("c - a = %s = %f\n", str_diff, df_to_double(diff));

    df_frac prod = df_mul(a, b);
    char *str_prod = df_to_string(prod);
    printf("a * b = %s = %f\n", str_prod, df_to_double(prod));

    df_frac quot = df_div(c, b);
    char *str_quot = df_to_string(quot);
    printf("c / b = %s = %f\n", str_quot, df_to_double(quot));
    printf("\n");

    // Comparisons
    printf("Comparisons:\n");
    printf("a %s b\n", df_lt(a, b) ? "<" : df_gt(a, b) ? ">" : "=");
    printf("a %s c\n", df_lt(a, c) ? "<" : df_gt(a, c) ? ">" : "=");
    printf("b %s c\n", df_lt(b, c) ? "<" : df_gt(b, c) ? ">" : "=");
    printf("\n");

    // Clean up strings
    free(str_a);
    free(str_b);
    free(str_c);
    free(str_sum);
    free(str_diff);
    free(str_prod);
    free(str_quot);

    df_release(&a);
    df_release(&b);
    df_release(&c);
    df_release(&sum);
    df_release(&diff);
    df_release(&prod);
    df_release(&quot);

    printf("Example completed successfully!\n");
    return 0;
}