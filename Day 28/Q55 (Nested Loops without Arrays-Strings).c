/*
 * Write a program to print all the prime numbers from 1 to n.
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
    int n;
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000000) {
        fprintf(stderr, "Enter n from 2 to 1000000.\n");
        return 1;
    }
    for (int value = 2; value <= n; ++value) {
        int prime = 1;
        for (int divisor = 2; divisor <= value / divisor; ++divisor)
            if (value % divisor == 0) { prime = 0; break; }
        if (prime) printf("%s%d", value == 2 ? "" : " ", value);
    }
    putchar('\n');
    return 0;
}
