/*
 * Write a program to print all factors of a given number.
 */
#ifdef __MINGW32__
#ifndef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif
#endif
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_long_long(const char *text, long long *value) {
    char *end;
    long long parsed;
    errno = 0;
    parsed = strtoll(text, &end, 10);
    if (errno == ERANGE || end == text || *end != '\0') return 0;
    *value = parsed;
    return 1;
}

static int read_long_long(long long *value) {
    char token[128];
    return scanf("%127s", token) == 1 && parse_long_long(token, value);
}

static int read_unsigned_long_long(unsigned long long *value) {
    char token[128];
    char *end;
    unsigned long long parsed;
    if (scanf("%127s", token) != 1 || token[0] == '-') return 0;
    errno = 0;
    parsed = strtoull(token, &end, 10);
    if (errno == ERANGE || end == token || *end != '\0') return 0;
    *value = parsed;
    return 1;
}

int main(void) {
    unsigned long long number;
    unsigned long long small[100000], large[100000];
    size_t small_count = 0, large_count = 0;
    if (!read_unsigned_long_long(&number) || number == 0ULL || number > 1000000000000ULL) {
        fprintf(stderr, "Enter a positive integer up to 1000000000000.\n");
        return 1;
    }
    for (unsigned long long divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0ULL) {
            if (small_count == sizeof(small) / sizeof(small[0])) {
                fprintf(stderr, "Too many factors to display.\n"); return 1;
            }
            small[small_count++] = divisor;
            if (divisor != number / divisor) large[large_count++] = number / divisor;
        }
    }
    for (size_t i = 0; i < small_count; ++i) printf("%s%llu", i == 0 ? "" : " ", small[i]);
    while (large_count > 0) printf(" %llu", large[--large_count]);
    putchar('\n');
    return 0;
}
