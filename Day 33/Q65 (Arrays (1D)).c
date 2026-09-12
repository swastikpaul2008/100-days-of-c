/*
 * Search in a sorted array using binary search.
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
    int n, values[1000], target, left = 0, right, found = -1;
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &values[i]) != 1 || (i > 0 && values[i] < values[i - 1])) {
            fprintf(stderr, "Expected a sorted integer array.\n"); return 1;
        }
    }
    if (scanf("%d", &target) != 1) { fprintf(stderr, "Expected search value.\n"); return 1; }
    right = n - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (values[middle] == target) { found = middle; break; }
        if (values[middle] < target) left = middle + 1; else right = middle - 1;
    }
    if (found < 0) puts("-1"); else printf("Found at index %d\n", found);
    return 0;
}
