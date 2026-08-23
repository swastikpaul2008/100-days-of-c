/*
 * Write a program to implement a basic calculator using switch-case for +, -, *, /, %.
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
    long long a, b;
    long long result;
    char operation;
    if (!read_long_long(&a) || !read_long_long(&b) || scanf(" %c", &operation) != 1) {
        fprintf(stderr, "Expected two integers and an operator.\n");
        return 1;
    }
    switch (operation) {
        case '+':
            if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
                fprintf(stderr, "Result out of range.\n"); return 1;
            }
            result = a + b;
            break;
        case '-':
            if ((b < 0 && a > LLONG_MAX + b) || (b > 0 && a < LLONG_MIN + b)) {
                fprintf(stderr, "Result out of range.\n"); return 1;
            }
            result = a - b;
            break;
        case '*':
            if (a == 0 || b == 0) result = 0;
            else if ((a == -1 && b == LLONG_MIN) || (b == -1 && a == LLONG_MIN) ||
                     (a > 0 && b > 0 && a > LLONG_MAX / b) ||
                     (a > 0 && b < 0 && b < LLONG_MIN / a) ||
                     (a < 0 && b > 0 && a < LLONG_MIN / b) ||
                     (a < 0 && b < 0 && a < LLONG_MAX / b)) {
                fprintf(stderr, "Result out of range.\n"); return 1;
            } else result = a * b;
            break;
        case '/':
            if (b == 0) { fprintf(stderr, "Division by zero.\n"); return 1; }
            if (a == LLONG_MIN && b == -1) { fprintf(stderr, "Result out of range.\n"); return 1; }
            printf("%lld\n", a / b); return 0;
        case '%':
            if (b == 0) { fprintf(stderr, "Remainder by zero.\n"); return 1; }
            if (a == LLONG_MIN && b == -1) { puts("0"); break; }
            printf("%lld\n", a % b); return 0;
        default: fprintf(stderr, "Unsupported operator.\n"); return 1;
    }
    printf("%lld\n", result);
    return 0;
}
