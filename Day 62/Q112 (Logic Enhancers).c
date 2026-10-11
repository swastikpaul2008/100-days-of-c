/*
 * Write a program to take an integer array arr as input. The task is to find the maximum sum of any contiguous subarray using Kadane's algorithm. Print the maximum sum as output. If all elements are negative, print the largest (least negative) element.
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
    int n, value;
    long long current, maximum;
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000 || scanf("%d", &value) != 1) {
        fprintf(stderr, "Expected a non-empty array of at most 1000 integers.\n"); return 1;
    }
    current = maximum = value;
    for (int i = 1; i < n; ++i) {
        if (scanf("%d", &value) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
        current = current > 0 ? current + value : value;
        if (current > maximum) maximum = current;
    }
    printf("%lld\n", maximum);
    return 0;
}
