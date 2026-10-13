/*
 * Write a program to take a string s as input. The task is to find the length of the longest substring without repeating characters. Print the length as output.
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
    char text[1002];
    size_t last[256], start = 0, best = 0;
    if (fgets(text, sizeof(text), stdin) == NULL) { fprintf(stderr, "Expected a string.\n"); return 1; }
    for (int i = 0; i < 256; ++i) last[i] = SIZE_MAX;
    for (size_t i = 0; text[i] != '\0' && text[i] != '\n'; ++i) {
        unsigned char ch = (unsigned char)text[i];
        if (last[ch] != SIZE_MAX && last[ch] >= start) start = last[ch] + 1;
        last[ch] = i;
        if (i - start + 1 > best) best = i - start + 1;
    }
    printf("%zu\n", best);
    return 0;
}
