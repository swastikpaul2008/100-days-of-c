/*
 * Write a program to take an integer array as input. Only one element will be repeated. Print the repeated element. Try to find the result in one single iteration.
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
    int n, values[1000], repeated = 0, found = 0;
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000) { fprintf(stderr, "Array size must be from 2 to 1000.\n"); return 1; }
    for (int i = 0; i < n; ++i) if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
    for (int i = 0; i < n && !found; ++i)
        for (int j = i + 1; j < n; ++j)
            if (values[i] == values[j]) { repeated = values[i]; found = 1; break; }
    if (!found) { fprintf(stderr, "No repeated element found.\n"); return 1; }
    printf("%d\n", repeated);
    return 0;
}
