/*
 * Write a Program to take a positive integer n as input, and find the pivot integer x such that the sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively. Print the pivot integer x. If no such integer exists, print -1. Assume that it is guaranteed that there will be at most one pivot integer for the given input.
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
    unsigned long long n, left = 1, right, answer = 0;
    if (!read_unsigned_long_long(&n) || n == 0ULL || n > 1000000000ULL) {
        fprintf(stderr, "Enter n from 1 to 1000000000.\n"); return 1;
    }
    right = n;
    while (left <= right) {
        unsigned long long middle = left + (right - left) / 2ULL;
        unsigned long long square = middle * middle;
        unsigned long long total = n * (n + 1ULL) / 2ULL;
        if (square == total) { answer = middle; break; }
        if (square < total) left = middle + 1ULL; else right = middle - 1ULL;
    }
    printf("%lld\n", answer == 0ULL ? -1LL : (long long)answer);
    return 0;
}
