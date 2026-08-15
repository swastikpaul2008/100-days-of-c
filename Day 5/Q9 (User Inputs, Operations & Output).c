/*
 * Write a program to calculate simple and compound interest for given principal, rate, and time.
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
    double principal, rate, simple, compound;
    int years;
    if (scanf("%lf %lf %d", &principal, &rate, &years) != 3 ||
        !isfinite(principal) || !isfinite(rate) ||
        principal < 0.0 || rate < 0.0 || years < 0 || years > 10000) {
        fprintf(stderr, "Enter non-negative principal, rate, and years (up to 10000).\n");
        return 1;
    }
    simple = principal * rate * years / 100.0;
    compound = principal;
    for (int year = 0; year < years; ++year) {
        compound *= 1.0 + rate / 100.0;
        if (!isfinite(compound)) {
            fprintf(stderr, "Compound interest result is out of range.\n");
            return 1;
        }
    }
    printf("Simple Interest=%.2f, Compound Interest=%.2f\n", simple, compound - principal);
    return 0;
}
