/*
 * Find the second largest element in an array.
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
    int n, values[1000], largest, second, found_second = 0;
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000) { fprintf(stderr, "Array must contain 2 to 1000 values.\n"); return 1; }
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array input.\n"); return 1; }
    largest = second = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (values[i] > largest) {
            if (i > 0) { second = largest; found_second = 1; }
            largest = values[i];
        } else if (values[i] > second && values[i] < largest) {
            second = values[i];
            found_second = 1;
        }
    }
    if (!found_second) { fprintf(stderr, "No distinct second-largest value.\n"); return 1; }
    printf("%d\n", second);
    return 0;
}
