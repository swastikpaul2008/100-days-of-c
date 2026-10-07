/*
 * Write a Program to take an integer array nums. Print an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i]. The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
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
    int n, values[1000];
    long long prefix[1001], suffix = 1;
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i) if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
    prefix[0] = 1;
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] * values[i];
    for (int i = n - 1; i >= 0; --i) {
        long long result = prefix[i] * suffix;
        printf("%s%lld", i == 0 ? "" : " ", result);
        suffix *= values[i];
    }
    putchar('\n');
    return 0;
}
