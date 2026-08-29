/*
 * Write a program to find the LCM of two numbers.
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
    long long left, right;
    unsigned long long a, b, x, y;
    if (!read_long_long(&left) || !read_long_long(&right)) {
        fprintf(stderr, "Expected two integers.\n");
        return 1;
    }
    a = left < 0 ? 0ULL - (unsigned long long)left : (unsigned long long)left;
    b = right < 0 ? 0ULL - (unsigned long long)right : (unsigned long long)right;
    if (a == 0ULL || b == 0ULL) { puts("0"); return 0; }
    x = a;
    y = b;
    while (y != 0ULL) { unsigned long long r = x % y; x = y; y = r; }
    if (x == 0ULL) { puts("0"); return 0; }
    if (a / x > ULLONG_MAX / b) {
        fprintf(stderr, "LCM exceeds the supported range.\n");
        return 1;
    }
    printf("%llu\n", (a / x) * b);
    return 0;
}
