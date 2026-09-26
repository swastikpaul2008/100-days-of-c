/*
 * Check if two strings are anagrams of each other.
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
    char first[1002], second[1002];
    int counts[256] = {0};
    if (fgets(first, sizeof(first), stdin) == NULL || fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Expected two strings.\n"); return 1;
    }
    for (size_t i = 0; first[i] != '\0' && first[i] != '\n'; ++i)
        if (!isspace((unsigned char)first[i])) ++counts[(unsigned char)tolower((unsigned char)first[i])];
    for (size_t i = 0; second[i] != '\0' && second[i] != '\n'; ++i)
        if (!isspace((unsigned char)second[i])) --counts[(unsigned char)tolower((unsigned char)second[i])];
    for (int i = 0; i < 256; ++i)
        if (counts[i] != 0) { puts("Not anagrams"); return 0; }
    puts("Anagrams");
    return 0;
}
