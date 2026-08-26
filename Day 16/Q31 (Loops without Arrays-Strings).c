/*
 * Write a program to take a number as input and print its equivalent binary representation.
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
    char bits[sizeof(number) * CHAR_BIT + 1];
    size_t length = 0;
    if (!read_unsigned_long_long(&number)) {
        fprintf(stderr, "Expected a non-negative integer.\n");
        return 1;
    }
    do {
        bits[length++] = (char)('0' + number % 2ULL);
        number /= 2ULL;
    } while (number != 0ULL);
    while (length > 0) putchar(bits[--length]);
    putchar('\n');
    return 0;
}
