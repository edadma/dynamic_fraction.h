# dynamic_fraction.h

[![Version](https://img.shields.io/badge/version-v1.0.0-blue.svg)](https://github.com/edadma/dynamic_fraction.h/releases)
[![Language](https://img.shields.io/badge/language-C11-blue.svg)](https://en.cppreference.com/w/c/11)
[![License](https://img.shields.io/badge/license-MIT%20OR%20Unlicense-green.svg)](#license)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows%20%7C%20macOS%20%7C%20MCU-lightgrey.svg)](#platform-support)
[![Documentation](https://img.shields.io/badge/docs-GitHub%20Pages-brightgreen.svg)](https://edadma.github.io/dynamic_fraction.h/)

A single-header C library implementing arbitrary precision rational numbers (fractions) with reference counting, built on top of dynamic_int.h for seamless arbitrary precision arithmetic.

## Features

- **Single Header**: Easy integration - just include `dynamic_fraction.h`
- **Arbitrary Precision**: Handle fractions with arbitrarily large numerators and denominators
- **Reference Counting**: Automatic memory management with copy-on-write semantics
- **Always Reduced**: Fractions are automatically kept in lowest terms
- **Comprehensive API**: Full set of arithmetic, comparison, and conversion functions
- **Built on dynamic_int.h**: Leverages proven arbitrary precision integer library
- **Fail-Fast Error Handling**: Assertions on invalid inputs and allocation failures for immediate bug detection
- **Mathematical Correctness**: Proper sign normalization and fraction reduction

## Quick Start

```c
#define DF_IMPLEMENTATION
#include "dynamic_fraction.h"

int main() {
    // Create fractions
    df_frac a = df_from_ints(3, 4);    // 3/4
    df_frac b = df_from_ints(1, 2);    // 1/2

    // Arithmetic operations
    df_frac sum = df_add(a, b);        // 5/4
    df_frac product = df_mul(a, b);    // 3/8

    // Convert to string
    char* str = df_to_string(sum);
    printf("Result: %s\n", str);       // "5/4"
    free(str);

    // Clean up (reference counting)
    df_release(&a);
    df_release(&b);
    df_release(&sum);
    df_release(&product);

    return 0;
}
```

## Documentation

Full API documentation is available at: https://[your-repo].github.io/dynamic_fraction.h/

## Configuration

Customize the library by defining these macros before including:

```c
#define DF_MALLOC malloc         // Custom allocator
#define DF_FREE free             // Custom deallocator
#define DF_ASSERT assert         // Custom assert macro

#define DF_IMPLEMENTATION
#include "dynamic_fraction.h"
```

## Building

### With CMake

```bash
mkdir build && cd build
cmake ..
make
./tests  # Run unit tests
```

### Manual Compilation

```bash
gcc -std=c11 -Wall -Wextra main.c -o example
```

## API Overview

### Creation and Memory Management

- `df_from_ints()`, `df_from_int()` - Create from integers
- `df_from_di()` - Create from dynamic integers
- `df_from_double()` - Create from floating point (with precision limit)
- `df_from_string()` - Create from string representation ("3/4", "5", "-2/3")
- `df_zero()`, `df_one()`, `df_neg_one()` - Create common constants
- `df_retain()` - Increment reference count
- `df_release()` - Decrement reference count and free if needed

### Arithmetic Operations

- `df_add()`, `df_sub()`, `df_mul()`, `df_div()` - Basic arithmetic
- `df_negate()`, `df_abs()`, `df_reciprocal()` - Unary operations
- `df_pow()` - Exponentiation with integer exponents

### Comparison Functions

- `df_cmp()`, `df_eq()`, `df_ne()`, `df_lt()`, `df_le()`, `df_gt()`, `df_ge()` - Comparisons
- `df_min()`, `df_max()` - Min/max operations

### Rounding and Truncation

- `df_floor()`, `df_ceil()`, `df_trunc()` - Rounding operations
- `df_round()` - Round to nearest integer (banker's rounding for ties)

### Type Conversion and Testing

- `df_to_double()`, `df_to_int64()` - Convert to native types
- `df_to_string()` - Convert to string representation
- `df_is_zero()`, `df_is_one()`, `df_is_integer()` - Type predicates
- `df_is_positive()`, `df_is_negative()` - Sign testing
- `df_fits_int32()`, `df_fits_int64()`, `df_fits_double()` - Range checking

### Advanced Functions

- `df_numerator()`, `df_denominator()` - Extract components
- `df_whole_part()`, `df_fractional_part()` - Split into integer and fractional parts
- `df_sign()` - Get sign (-1, 0, 1)
- `df_hash()` - Hash function for use in hash tables

## Memory Management

The library uses reference counting for automatic memory management:

```c
df_frac a = df_from_ints(3, 4);  // ref_count = 1
df_frac b = df_retain(a);        // ref_count = 2
df_release(&a);                  // ref_count = 1, a = NULL
df_release(&b);                  // ref_count = 0, memory freed, b = NULL
```

## Dependencies

- **dynamic_int.h**: For arbitrary precision integer arithmetic (included in `devDeps/`)
- **C11 or later**: Standard library functions

## License

This project is dual-licensed under:
- MIT License
- The Unlicense

Choose whichever license works best for your project.

## Platform Support

This library supports:
- **Linux**: Full support with GCC and Clang
- **Windows**: Compatible with MSVC and MinGW
- **macOS**: Native Clang support
- **MCU**: Designed for microcontroller environments

## Version History

### v1.0.0 (September 2025)
- **Complete rational arithmetic**: Full arbitrary precision fraction operations
- **Comprehensive test suite**: 26 unit tests covering all functions with 0 failures
- **Advanced mathematical functions**: Floor, ceil, truncate, round, power operations
- **String conversion**: Full parsing and generation of fraction strings
- **Reference counting**: Robust automatic memory management
- **Documentation**: Complete Doxygen API documentation with examples
- **Dual licensing**: MIT OR Unlicense for maximum compatibility
- **GitHub Actions**: Automated documentation generation and deployment

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.