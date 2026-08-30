/*
 * Write a program to find the 1’s complement of a binary number and print it.
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
    char binary[1002];
    size_t length;
    if (scanf("%1001s", binary) != 1) {
        fprintf(stderr, "Expected a binary string.\n");
        return 1;
    }
    length = strlen(binary);
    if (length == 0 || length > 1000) { fprintf(stderr, "Binary string is too long.\n"); return 1; }
    for (size_t i = 0; i < length; ++i) {
        if (binary[i] != '0' && binary[i] != '1') {
            fprintf(stderr, "Input must contain only 0 and 1.\n");
            return 1;
        }
        binary[i] = binary[i] == '0' ? '1' : '0';
    }
    puts(binary);
    return 0;
}
