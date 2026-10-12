/*
 * Write a program to take an integer array arr and an integer k as inputs. The task is to find the kth smallest element in the array. Print the kth smallest element as output.
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

static int compare_ints(const void *left, const void *right) {
    int a = *(const int *)left;
    int b = *(const int *)right;
    return (a > b) - (a < b);
}
int main(void) {
    int n, k, values[1000];
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i) if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
    if (scanf("%d", &k) != 1 || k < 1 || k > n) { fprintf(stderr, "k must be from 1 to array size.\n"); return 1; }
    qsort(values, (size_t)n, sizeof(values[0]), compare_ints);
    printf("%d\n", values[k - 1]);
    return 0;
}
