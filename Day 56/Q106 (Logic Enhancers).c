/*
 * Write a program to take an array arr[] of integers as input, the task is to find the next greater element for each element of the array in order of their appearance in the array. Next greater element of an element in the array is the nearest element on the right which is greater than the current element. If there does not exist next greater of current element, then next greater element for current element is -1.
 * 
 * N.B:
 * - Print the output for each element in a comma separated fashion.
 * - Do not use Stack, use brute force approach (nested loop) to solve.
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
    int n, values[1000];
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i) if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
    for (int i = 0; i < n; ++i) {
        int next = -1;
        for (int j = i + 1; j < n; ++j) if (values[j] > values[i]) { next = values[j]; break; }
        printf("%s%d", i == 0 ? "" : ", ", next);
    }
    putchar('\n');
    return 0;
}
