# Memory Allocator Test

This project tests a custom memory allocator against the system's memory allocator using a simple test program.

## Getting Started

To get started, you need to have `gcc` installed on your system. The Makefile provides commands to compile and run the tests with both the system's memory allocator and the custom memory allocator.

## Makefile Commands

### Build and Run with System Memory Allocator

```
make memtest_sys
./memtest_sys

# Build and run with custom memory allocator
make memtest_user
./memtest_user

# Clean up
make clean
```

### Files

memtest.c: The test program that tests memory allocation and deallocation. Provided by Prof. Bruce

my_mem.c: The custom memory allocator implementation.

my_mem.h: The header file for the custom memory allocator.

Makefile: The Makefile with commands to build and run the tests.
