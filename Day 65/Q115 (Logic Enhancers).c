/*
 * Write a program to take two strings s and t as inputs (assume all characters are lowercase). The task is to determine if s and t are valid anagrams, meaning they contain the same characters with the same frequencies. Print "Anagram" if they are, otherwise "Not Anagram".
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
    int counts[26] = {0};
    if (fgets(first, sizeof(first), stdin) == NULL || fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Expected two strings.\n"); return 1;
    }
    for (size_t i = 0; first[i] != '\0' && first[i] != '\n'; ++i) {
        if (first[i] < 'a' || first[i] > 'z') { fprintf(stderr, "Use lowercase letters only.\n"); return 1; }
        ++counts[first[i] - 'a'];
    }
    for (size_t i = 0; second[i] != '\0' && second[i] != '\n'; ++i) {
        if (second[i] < 'a' || second[i] > 'z') { fprintf(stderr, "Use lowercase letters only.\n"); return 1; }
        --counts[second[i] - 'a'];
    }
    for (int i = 0; i < 26; ++i) if (counts[i] != 0) { puts("Not Anagram"); return 0; }
    puts("Anagram");
    return 0;
}
